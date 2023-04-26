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
    print('Serial port 0 is unavailable.')
    try:
        ser = serial.Serial('/dev/ttyACM1', 9600)
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

        self.lastTimeRecv = time.time()

    def turret_callback(self, request, response):
        print("recv request: " + request.title)

        if time.time() - self.lastTimeRecv < 0.05:
            response.title = 'busy'
            return response
        
        self.lastTimeRecv = time.time()

        print("checking ping command")
        # case 1: ping
        if request.title == 'ping':
            response.title = 'pong'
        
        print("checking run command")
        # case 2: run
        if request.title == 'run' and self.state == 'stop':
            if request.direction == 'CW':
                ser.write(b'runCW\n')
                printByMe('serial send runCW')
                self.state = 'run'
            elif request.direction == 'CCW':
                ser.write(b'runCCW\n')
                printByMe('serial send runCCW')
                self.state = 'run'
            elif request.direction == 'lower' and time.time():
                ser.write(b'lower\n')
                printByMe('serial send lower')
            elif request.direction == 'rise' and time.time():
                ser.write(b'rise\n')
                printByMe('serial send rise')
            response.title = 'OK'
        
        print("checking stop command")
        # case 3: stop
        if request.title == 'stop' and self.state == 'run':
            ser.write(b'stop\n')
            printByMe('serial send stop')
            response.title = 'OK'
            self.state = 'stop'
        
        print("checking step to command")
        # case 4: to
        if request.title == 'to' and self.state == 'stop' and request.direction == 'left-right':
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

        print("checking servo to command")
        if request.title == 'to' and self.state == 'stop' and request.direction == 'up-down':
            angle = 0
            while angle < abs(request.position):
                ser.write(b'lower\n' if request.position >= 0 else b'rise\n')
                angle += 5
                time.sleep(0.1)
            response.title = 'OK'

        ser.read_all()

        print('respond with title: ' + response.title)
        return response

def main(args = None):
    print('turret.py launched.')

    # Test serial port
    while True:
        ser.write(b'ping\n')
        respond = b''
        time.sleep(0.1)
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
