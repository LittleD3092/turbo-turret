from ultralytics import YOLO
import os
import cv2

# Find project root based on the location of this file
# Postcondition: an absolute path of folder named PROJECT_NAME is returned
def findProjectRoot():
    currentPath = os.path.abspath(__file__)
    while os.path.basename(currentPath) != PROJECT_NAME:
        currentPath = os.path.dirname(currentPath)
        if currentPath == "/":
            raise Exception("Project root not found")
    return currentPath

PROJECT_NAME = "target_recognize"
PROJECT_ROOT = findProjectRoot()
os.chdir(PROJECT_ROOT)
MODEL_PATH = PROJECT_ROOT + "/runs/detect/train/weights/best.pt"

# Load model
model = YOLO(MODEL_PATH)

# load camera stream
cap = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    if ret == False:
        break

    # Detect objects
    results = model(frame)
    result = results[0].boxes.xyxy

    # Draw bounding boxes
    for i in range(result.shape[0]):
        x1 = int(result[i, 0])
        y1 = int(result[i, 1])
        x2 = int(result[i, 2])
        y2 = int(result[i, 3])
        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)    

    # Display the resulting frame
    cv2.imshow('frame', frame)

    # Press Q on keyboard to  exit
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break