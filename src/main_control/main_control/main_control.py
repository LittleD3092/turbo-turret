import sys

from controller_input_srv.srv import Controller
from turret_srv.srv import Turret
from target_recognize_srv.srv import TargetRecognize
import rclpy
from rclpy.node import Node
import numpy as np
import time

USE_TURRET = True

class ControllerInputClient(Node):
    def __init__(self):
        super().__init__('main_control')
        self.cli = self.create_client(Controller, 'controller_input')
        while not self.cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().info('controller service not available, waiting again...')
        self.req = Controller.Request()

        # for remembering state
        self.currentState = Controller.Response()
        self.lastState = Controller.Response()

    def send_request(self, title = ''):
        self.req.title = title
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()
    
    def refresh(self):
        self.lastState = self.currentState
        self.currentState = self.send_request('get')

    def press(self, button):
        return getattr(self.currentState, button)
    
    def pressed(self, button):
        return getattr(self.currentState, button) and not getattr(self.lastState, button)
    
    def released(self, button):
        return not getattr(self.currentState, button) and getattr(self.lastState, button)
    
    def value(self, axis):
        return getattr(self.currentState, axis)
    
    def getTuple(self, axis):
        # For dpad
        return getattr(self.currentState, axis)
    
class TurretClient(Node):
    def __init__(self):
        super().__init__('main_control')
        self.cli = self.create_client(Turret, 'turret')
        while not self.cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().info('turret service not available, waiting again...')
        self.req = Turret.Request()

    def send_request(self, title = 'ping', direction = '', position = 0):
        self.req.title = title
        self.req.direction = direction
        self.req.position = position
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class TargetRecognizeClient(Node):
    def __init__(self):
        super().__init__('main_control')
        self.cli = self.create_client(TargetRecognize, 'target_recognize')
        while not self.cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().info('target recognize service not available, waiting again...')
        self.req = TargetRecognize.Request()

    def send_request(self, title = 'ping'):
        self.req.title = title
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class AngleCalculator:
    def __init__(self, img_pixel_height, img_pixel_width, 
                 focal_length = 4.4, sensor_width = 3.8359, sensor_height = 2.288):
        self.img_pixel_height = img_pixel_height
        self.img_pixel_width = img_pixel_width
        self.focal_length = focal_length
        self.sensor_width = sensor_width
        self.sensor_height = sensor_height

        self.focal_pixel = (focal_length * img_pixel_width / sensor_width +
                            focal_length * img_pixel_height / sensor_height) / 2
        
        # camera matrix for robot_XYZ to image_XY
        self.K = np.array([[self.focal_pixel, 0,                img_pixel_width / 2],
                           [0,                self.focal_pixel, img_pixel_height / 2],
                           [0,                0,                1]])
        
        # camera matrix for image_XY to robot_XYZ
        self.K_inv = np.linalg.inv(self.K)

    # Precondition: img_x and img_y are in pixel, indicate the point in the image
    # Postcondition: return the coordinate of the point with respect to robot (in XYZ tuple)
    def calculate_robot_coor(self, img_x, img_y):
        r = self.K_inv.dot(np.array([img_x, img_y, 1]))
        return r

    # Preconditions: img_x and img_y are in pixel, indicate the point in the image
    # Postcondition: return the yaw and pitch angle of the point with respect to the front axis of the robot (in degree)
    def calculate_angle(self, img_x, img_y):
        r = self.calculate_robot_coor(img_x, img_y)
        yaw = -np.arctan2(r[0], r[2]) * 180 / np.pi
        pitch = np.arctan2(r[1], r[2]) * 180 / np.pi
        return (yaw, pitch)


def main(args=None):
    rclpy.init(args=args)

    # Initialize controller input client and ping server
    controller_input_client = ControllerInputClient()
    response = controller_input_client.send_request('ping')
    controller_input_client.get_logger().info(
        'Result of controller input ping: %s' % response.title)
    
    # Initialize turret client and ping server
    if USE_TURRET:
        turret_client = TurretClient()
        response = turret_client.send_request('ping')
        turret_client.get_logger().info(
            'Result of turret client ping: %s' % response.title)
    
    # Initialize target recognize client and ping server
    target_recognize_client = TargetRecognizeClient()
    response = target_recognize_client.send_request('ping')
    target_recognize_client.get_logger().info(
        'Result of target recognize ping: %s' % response.title)
    
    # Initialize angle calculator
    sample_response = target_recognize_client.send_request('detect')
    angle_calculator = AngleCalculator(img_pixel_height = sample_response.img_resolution_height,
                                       img_pixel_width = sample_response.img_resolution_width)

    # Main loop
    running = True
    shootFlag = False
    previousOutputTime = 0
    while running:
        # test input and print on console
        controller_input_client.refresh()
        if controller_input_client.value('left_stick_x') or controller_input_client.value('left_stick_y') or controller_input_client.value('right_stick_x') or controller_input_client.value('right_stick_y'):
            print("left_stick: ", (controller_input_client.value('left_stick_x'), controller_input_client.value('left_stick_y')))
            print("right_stick: ", (controller_input_client.value('right_stick_x'), controller_input_client.value('right_stick_y')))
            
        # mapping control
        if USE_TURRET:
            # left right
            if controller_input_client.value('right_stick_x') == 1:
                turret_client.send_request('run', 'CW')
            elif controller_input_client.value('right_stick_x') == -1:
                turret_client.send_request('run', 'CCW')

            # up down
            if controller_input_client.value('right_stick_y') == 1:
                turret_client.send_request('run', 'lower')
            elif controller_input_client.value('right_stick_y') == -1:
                turret_client.send_request('run', 'rise')

            # no input for turret
            if (
                controller_input_client.value('right_stick_x') == 0 and 
                controller_input_client.value('right_stick_y') == 0 and 
                time.time() - previousOutputTime > 0.5
            ):
                previousOutputTime = time.time()
                turret_client.send_request('stop')

        # aim on left trigger pressed
        if controller_input_client.value("left_trigger") == 1:
            response = target_recognize_client.send_request('detect')
            result = response.result_array
            result = np.reshape(result, (response.result_array_height, response.result_array_width))

            # calculate middle points
            result_middle_point = []
            for [x1, y1, x2, y2] in result:
                result_middle_point.append([(x1 + x2) / 2, (y1 + y2) / 2])
            print('Detected target(s): ', result)

            # remove duplicate targets
            for i in range(len(result_middle_point)):
                for j in range(i + 1, len(result_middle_point)):
                    if np.linalg.norm(result_middle_point[i]) - np.linalg.norm(result_middle_point[j]) < 30:
                        result_middle_point[j] = [-1, -1]

            # calculate angles
            result_angles = []
            for [x, y] in result_middle_point:
                if x == -1 and y == -1:
                    continue
                yaw, pitch = angle_calculator.calculate_angle(x, y)
                result_angles.append([yaw, pitch])
            print('Target(s) angle(s): ', result_angles)

            if USE_TURRET:
                # move turret to the target
                print("moving...")
                for [yaw, pitch] in result_angles:
                    print("send request to turret: ", 'to'+str(int(yaw*3200/360)))
                    turret_client.send_request('to', 'left-right', int(yaw * 3200 / 360))
                    print("send request to turret: ", 'to'+str(int(pitch)))
                    turret_client.send_request('to', 'up-down', int(pitch))
                print("moved turret to the target")
        # shoot on right trigger pressed
        if controller_input_client.value("right_trigger") == 1:
            print("shooting...")
            turret_client.send_request('fire')
            print("shot")

        # left stick
        leftStickX = controller_input_client.value('left_stick_x')
        leftStickY = controller_input_client.value('left_stick_y')
        if leftStickX == 0 and leftStickY == -1:
            turret_client.send_request('move', 'forward')
        elif leftStickX == 0 and leftStickY == 1:
            turret_client.send_request('move', 'backward')
        elif leftStickX == -1 and leftStickY == -1:
            turret_client.send_request('move', 'front left')
        elif leftStickX == 1 and leftStickY == -1:
            turret_client.send_request('move', 'front right')
        elif leftStickX == -1 and leftStickY == 1:
            turret_client.send_request('move', 'back left')
        elif leftStickX == 1 and leftStickY == 1:
            turret_client.send_request('move', 'back right')
        elif leftStickX == -1 and leftStickY == 0:
            turret_client.send_request('turn', 'left')
        elif leftStickX == 1 and leftStickY == 0:
            turret_client.send_request('turn', 'right')

    print("ending...")
    controller_input_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
