import sys

from controller_input_srv.srv import Controller
from turret_srv.srv import Turret
import rclpy
from rclpy.node import Node

class ControllerInputClient(Node):
    def __init__(self):
        super().__init__('main_control')
        self.cli = self.create_client(Controller, 'controller_input')
        while not self.cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().info('controller service not available, waiting again...')
        self.req = Controller.Request()

    def send_request(self, title = ''):
        self.req.title = title
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()
    
class TurretClient(Node):
    def __init__(self):
        super().__init__('main_control')
        self.cli = self.create_client(Turret, 'turret')
        while not self.cli.wait_for_service(timeout_sec=5.0):
            self.get_logger().info('turret service not available, waiting again...')
        self.req = Turret.Request()

    def send_request(self, title = '', direction = '', position = 0):
        self.req.title = title
        self.req.direction = direction
        self.req.position = position
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

def main(args=None):
    rclpy.init(args=args)

    controller_input_client = ControllerInputClient()

    response = controller_input_client.send_request('ping')
    controller_input_client.get_logger().info(
        'Result of ping: %s' % response.title)
    
    turret_client = TurretClient()
    response = turret_client.send_request('ping')
    turret_client.get_logger().info(
        'Result of ping: %s' % response.title)
    
    running = True
    while running:
        # test input and print on console
        response = controller_input_client.send_request('get')
        if (response.left_stick_x != 0 or response.left_stick_y != 0 or 
            response.left_trigger != -1 or response.right_stick_x != 0 or 
            response.right_stick_y != 0 or response.right_trigger != -1):
            controller_input_client.get_logger().info(
                'Left stick x: %s' % response.left_stick_x)
            controller_input_client.get_logger().info(
                'Left stick y: %s' % response.left_stick_y)
            controller_input_client.get_logger().info(
                'Left trigger: %s' % response.left_trigger)
            controller_input_client.get_logger().info(
                'Right stick x: %s' % response.right_stick_x)
            controller_input_client.get_logger().info(
                'Right stick y: %s' % response.right_stick_y)
            controller_input_client.get_logger().info(
                'Right trigger: %s' % response.right_trigger)
            controller_input_client.get_logger().info(
                '----------------------------------------')
            
        # mapping control
        if response.right_stick_x == 1:
            turret_client.send_request('run', 'CW')
        elif response.right_stick_x == -1:
            turret_client.send_request('run', 'CCW')
        
        if response.right_stick_y == 1:
            turret_client.send_request('run', 'lower')
        elif response.right_stick_y == -1:
            turret_client.send_request('run', 'rise')

        if response.right_stick_x == 0 and response.right_stick_y == 0:
            turret_client.send_request('stop')


    controller_input_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
