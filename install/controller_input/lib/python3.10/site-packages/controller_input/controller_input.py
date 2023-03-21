from controller_input_srv.srv import Controller

import rclpy
from rclpy.node import Node

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
    rclpy.init(args=args)
    controller_input = ControllerInputService()
    rclpy.spin(controller_input)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
