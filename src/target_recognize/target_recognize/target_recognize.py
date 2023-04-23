# ROS
import rclpy
from rclpy.node import Node
from target_recognize_srv.srv import TargetRecognize as TargetRecognizeSrv

# Python built-in
import os

# image processing
from ultralytics import YOLO
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

# git
import git

# Print the message, with the name of the file
# Precondition: printMsg is a string you want to print
# Postcondition: print the message, with the name 
#                of this script
def printByMe(printMsg = ''):
    print(os.path.basename(__file__) + ': ' + printMsg)

# Find project root
# Preconditions: None
# Postconditions: an absolute path of git root is returned
def findProjectRoot():
    git_repo = git.Repo('.', search_parent_directories=True)
    git_root = git_repo.git.rev_parse("--show-toplevel")
    return git_root

# class v4l2Camera for image subscription
class V4l2CameraClient(Node):
    # Constructor, create ros subscription
    def __init__(self):
        super().__init__('v4l2_camera_client')
        self.bridge = CvBridge()
        self.sub = self.create_subscription(Image, 'image_raw', self.v4l2_camera_callback, 1)
        self.cv_image = None

    def v4l2_camera_callback(self, msg):
        self.cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")

# class TargetRecognize for ros service
class TargetRecognize(Node):
    # Constructor, create ros service
    # Precondition: None
    # Postcondition: create ros service with name 'target_recognize'
    def __init__(self):
        super().__init__('target_recognize')
        self.srv = self.create_service(TargetRecognizeSrv, 'target_recognize', self.target_recognize_callback)

        self.model = YOLO(findProjectRoot() + "/src/target_recognize/runs/detect/train/weights/best.pt")

        self.camera = V4l2CameraClient()

    def target_recognize_callback(self, request, response):
        printByMe('target_recognize_callback is called.')
        if request.title == "ping":
            response.title = "pong"
            return response
        elif request.title == "detect":
            response.title = "OK"
            rclpy.spin_once(self.camera)
            results = self.model(self.camera.cv_image)
            result = results[0].boxes.xyxy
            response.result_array_height = len(result)
            response.result_array_width = len(result[0]) if response.result_array_height > 0 else 0
            response.result_array = []
            response.img_resolution_width = self.camera.cv_image.shape[1]
            response.img_resolution_height = self.camera.cv_image.shape[0]
            for row in result:
                for element in row:
                    response.result_array.append(int(element.item()))
            print("request processed")
            return response
        else:
            response.title = "ERROR"
            print("unknown request")
            return response

def main(args = None):
    printByMe('Start target_recognize node.')

    # run ROS2
    rclpy.init(args=args)
    target_recognize = TargetRecognize()
    rclpy.spin(target_recognize)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
