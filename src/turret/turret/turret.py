import os
import time

# Print the message, with the name of the file
# Precondition: printMsg is a string you want to print
# Postcondition: print the message, with the name 
#                of this script
def printByMe(printMsg = ''):
    print(os.path.basename(__file__) + ': ' + printMsg)

# Arduino
import serial
try:    
    ser = serial.Serial('/dev/ttyACM0', 9600)
except: 
    printByMe('Arduino is not connected.')
    exit()


# ROS2
import rclpy
from rclpy.node import Node
from turret_srv.srv import Turret as TurretSrv


# Class Turret for ros service
class Turret(Node):
    # Constructor, create ros service
    # Precondition: None
    # Postcondition: create ros service with name 'turret'
    def __init__(self):
        super().__init__('turret')
        self.srv = self.create_service(TurretSrv, 'turret', self.turret_callback)
        self.state = 'stop'

        self.lastTimeServoMove = 0

    def turret_callback(self, request, response):
        # case 1: ping
        if request.title == 'ping':
            response.title = 'pong'
        
        # case 2: run
        if request.title == 'run' and self.state == 'stop':
            if request.direction == 'CW':
                ser.write(b'runCW\n')
            elif request.direction == 'CCW':
                ser.write(b'runCCW\n')
            elif request.direction == 'lower':
                ser.write(b'lower\n')
            elif request.direction == 'rise':
                ser.write(b'rise\n')
            response.title = 'OK'
            self.state = 'run'
        
        # case 3: stop
        if request.title == 'stop' and self.state == 'run':
            ser.write(b'stop\n')
            response.title = 'OK'
            self.state = 'stop'
        
        # case 4: to
        if request.title == 'to' and self.state == 'stop':
            ser.write(b'to')
            ser.write(b'+' if request.position >= 0 else b'-')
            ser.write(str(abs(request.position)).encode())
            ser.write(b'\n')
            # wait until the turret is at the position
            while True:
                respond = ser.readline().strip()
                if respond == b'done':
                    break
                time.sleep(0.1)
            response.title = 'OK'
            
        return response

def main(args = None):
    print('turret.py launched.')

    # Test serial port
    while True:
        ser.write(b'ping\n')
        respond = b''
        while ser.in_waiting != 0:
            respond = ser.readline().strip()
        if respond == b'pong':
            printByMe('Arduino is connected.')
            break
        printByMe('Arduino is not connected. Try again in 5 seconds.')
        time.sleep(5)

    # run ROS2
    rclpy.init(args = args)
    turret = Turret()
    rclpy.spin(turret)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
