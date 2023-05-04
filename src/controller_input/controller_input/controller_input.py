from controller_input_srv.srv import Controller

import rclpy
from rclpy.node import Node

import pygame

class ControllerInputService(Node):
    def __init__(self):
        super().__init__('controller_input')
        self.srv = self.create_service(Controller, 'controller_input', self.callback)
        self.state = Controller.Response()

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

class Color:
    def __init__(self, hex_color):
        self.red = int(hex_color[1:3], 16)
        self.green = int(hex_color[3:5], 16)
        self.blue = int(hex_color[5:7], 16)

    def getRGBtuple(self):
        return (self.red, self.green, self.blue)

COLORS = {
    'red': Color('#D52941').getRGBtuple(),
    'dim_red': Color('#990D35').getRGBtuple(),
    'blue': Color('#2E86AB').getRGBtuple(),
    'dim_blue': Color('#1A4B61').getRGBtuple(),
    'green': Color('#7FB069').getRGBtuple(),
    'dim_green': Color('#457135').getRGBtuple(),
    'yellow': Color('#E7A94B').getRGBtuple(),
    'dim_yellow': Color('#B47618').getRGBtuple(),

    'grey': Color('#474747').getRGBtuple(),
}

def main(args=None):
    # ROS2 init
    rclpy.init(args=args)
    controller_input = ControllerInputService()

    # Pygame init
    pygame.init()
    pygame.joystick.init()
    screen = pygame.display.set_mode((1280, 800), pygame.FULLSCREEN)
    clock = pygame.time.Clock()
    running = True
    joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]
    if len(joysticks) == 0:
        print("No joysticks found")
        running = False

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
        controller_input.state.dpad[0], controller_input.state.dpad[1] = pygame.joystick.Joystick(0).get_hat(0)

        # button
        controller_input.state.a = bool(pygame.joystick.Joystick(0).get_button(0))
        controller_input.state.b = bool(pygame.joystick.Joystick(0).get_button(1))
        controller_input.state.x = bool(pygame.joystick.Joystick(0).get_button(2))
        controller_input.state.y = bool(pygame.joystick.Joystick(0).get_button(3))
        controller_input.state.left_bumper = bool(pygame.joystick.Joystick(0).get_button(4))
        controller_input.state.right_bumper = bool(pygame.joystick.Joystick(0).get_button(5))
        controller_input.state.share = bool(pygame.joystick.Joystick(0).get_button(6))
        controller_input.state.options = bool(pygame.joystick.Joystick(0).get_button(7))
        controller_input.state.left_stick_press = bool(pygame.joystick.Joystick(0).get_button(9))
        controller_input.state.right_stick_press = bool(pygame.joystick.Joystick(0).get_button(10))

        # exit if option button is pressed
        if controller_input.state.options:
            running = False

        # Screen wipe
        screen.fill("black")

        # Draw Status bar
        pygame.draw.rect(screen, COLORS['grey'], (0, 800-54, 1280, 800))

        # Draw ABXY state on left bottom
        pygame.draw.circle(screen, COLORS['dim_green' if controller_input.state.a else 'green'], (50, 800-27), 25)
        pygame.draw.circle(screen, COLORS['dim_red' if controller_input.state.b else 'red'], (50 + 75, 800-27), 25)
        pygame.draw.circle(screen, COLORS['dim_blue' if controller_input.state.x else 'blue'], (50 + 75 * 2, 800-27), 25)
        pygame.draw.circle(screen, COLORS['dim_yellow' if controller_input.state.y else 'yellow'], (50 + 75 * 3, 800-27), 25)
        
        # Update screen
        pygame.display.flip()

        # Handle spinning
        rclpy.spin_once(controller_input, timeout_sec=0.01)
        clock.tick(60)

    # Shutdown
    rclpy.shutdown()
    pygame.quit()


if __name__ == '__main__':
    main()
