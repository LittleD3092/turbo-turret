from controller_input_srv.srv import Controller

import rclpy
from rclpy.node import Node

import pygame

class ControllerInputService(Node):
    def __init__(self):
        super().__init__('controller_input')
        self.srv = self.create_service(Controller, 'controller_input', self.callback)

    def callback(self, request, response):
        if request.title == 'ping':
            response.title = 'pong'
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

    # Main loop
    while running:
        # Handle pygame events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        # Screen wipe
        screen.fill("purple")
        pygame.display.flip()

        # Handle spinning
        rclpy.spin_once(controller_input)
        clock.tick(60)

    # Shutdown
    rclpy.shutdown()
    pygame.quit()


if __name__ == '__main__':
    main()
