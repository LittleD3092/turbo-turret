from controller_input_srv.srv import Controller

import rclpy
from rclpy.node import Node

import pygame

class ControllerInputService(Node):
    def __init__(self):
        super().__init__('controller_input')
        self.srv = self.create_service(Controller, 'controller_input', self.callback)
        self.state = Controller.Request()

    def callback(self, request, response):
        if request.title == 'ping':
            response.title = 'pong'
        elif request.title == 'get':
            response = self.state
            response.title = 'controller state'
        else:
            response.title = 'unknown command'
        
        self.get_logger().info('Incoming request: %s' % request.title)
        return response

def main(args=None):
    # ROS2 init
    rclpy.init(args=args)
    controller_input = ControllerInputService()

    # Pygame init
    pygame.init()
    pygame.joystick.init()
    screen = pygame.display.set_mode((1280, 720))
    clock = pygame.time.Clock()
    running = True
    joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
    if len(joysticks) == 0:
        print("No joysticks found")

    # Main loop
    while running:
        # Handle pygame events
        for event in pygame.event.get():
            # close signal
            if event.type == pygame.QUIT:
                running = False
            
            # keydown signal
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        # joystick reading
        # axis
        controller_input.state.left_stick_x = round(pygame.joystick.Joystick(0).get_axis(0))
        controller_input.state.left_stick_y = round(pygame.joystick.Joystick(0).get_axis(1))
        controller_input.state.left_trigger = round(pygame.joystick.Joystick(0).get_axis(2))
        controller_input.state.right_stick_x = round(pygame.joystick.Joystick(0).get_axis(3))
        controller_input.state.right_stick_y = round(pygame.joystick.Joystick(0).get_axis(4))
        controller_input.state.right_trigger = round(pygame.joystick.Joystick(0).get_axis(5))

        # hat
        controller_input.dpad[0], controller_input.dpad[1] = pygame.joystick.Joystick(0).get_hat(0)

        # button
        controller_input.state.a = pygame.joystick.Joystick(0).get_button(0)
        controller_input.state.b = pygame.joystick.Joystick(0).get_button(1)
        controller_input.state.x = pygame.joystick.Joystick(0).get_button(2)
        controller_input.state.y = pygame.joystick.Joystick(0).get_button(3)
        controller_input.state.left_bumper = pygame.joystick.Joystick(0).get_button(4)
        controller_input.state.right_bumper = pygame.joystick.Joystick(0).get_button(5)
        controller_input.state.share = pygame.joystick.Joystick(0).get_button(6)
        controller_input.state.options = pygame.joystick.Joystick(0).get_button(7)
        controller_input.state.left_stick_press = pygame.joystick.Joystick(0).get_button(9)
        controller_input.state.right_stick_press = pygame.joystick.Joystick(0).get_button(10)

        # Screen wipe
        screen.fill("black")

        # Draw joystick state
        pygame.draw.circle(screen, "red", (int(640 + controller_input.state.left_stick_x * 100), int(360 + controller_input.state.left_stick_y * 100)), 10)
        pygame.display.flip()

        # Handle spinning
        rclpy.spin_once(controller_input)
        clock.tick(60)

    # Shutdown
    rclpy.shutdown()
    pygame.quit()


if __name__ == '__main__':
    main()
