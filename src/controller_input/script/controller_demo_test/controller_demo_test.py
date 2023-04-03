#!/usr/bin/env python3

import sys
sys.path.append("/home/deck/mambaforge/lib/python3.10/site-packages")

try:
    import pygame
except:
    print("pygame module cannot import.")
    print("sys.path:", sys.path)
    input("Press enter to continue...")
    exit()

pygame.joystick.init()
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]

class Player(object):
    def __init__(self):
        self.player = pygame.rect.Rect((640, 360, 50, 50))
        self.color = "white"

    def move(self, x_speed, y_speed):
        self.player.move_ip((x_speed, y_speed))

    def change_color(self, color):
        self.color = color

    def draw(self, game_screen):
        pygame.draw.rect(game_screen, self.color, self.player)

pygame.init()

player = Player()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((1280, 720))
running = True

while running:
    for event in pygame.event.get():
        # close signal
        if event.type == pygame.QUIT:
            running = False

        # keydown signal
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False

        # joystick button down signal
        if event.type == pygame.JOYBUTTONDOWN:
            # option button
            if pygame.joystick.Joystick(0).get_button(7):
                running = False

            # ABXY
            if pygame.joystick.Joystick(0).get_button(0):
                player.change_color("green")
            elif pygame.joystick.Joystick(0).get_button(1):
                player.change_color("red")
            elif pygame.joystick.Joystick(0).get_button(2):
                player.change_color("blue")
            elif pygame.joystick.Joystick(0).get_button(3):
                player.change_color("yellow")
            elif pygame.joystick.Joystick(0).get_button(6):
                player.change_color("white")

    # speed update
    # left stick x
    x_speed = round(pygame.joystick.Joystick(0).get_axis(0))
    # left stick y
    y_speed = round(pygame.joystick.Joystick(0).get_axis(1))
    player.move(x_speed, y_speed)

    screen.fill("black")
    player.draw(screen)
    pygame.display.update()

    clock.tick(60)
