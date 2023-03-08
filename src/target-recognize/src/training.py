from ultralytics import YOLO
import os

# Find project root based on the location of this file
# Postcondition: an absolute path of folder named PROJECT_NAME is returned
def findProjectRoot():
    currentPath = os.path.abspath(__file__)
    while os.path.basename(currentPath) != PROJECT_NAME:
        currentPath = os.path.dirname(currentPath)
        if currentPath == "/":
            raise Exception("Project root not found")
    return currentPath


PROJECT_NAME = "target-recognize"
PROJECT_ROOT = findProjectRoot()
os.chdir(PROJECT_ROOT)
TRAINING_DATA_PATH = PROJECT_ROOT + "/res/archery-targets-dataset/data.yaml"

model = YOLO("yolov8n.yaml") # build a new model from scratch
model.train(data = TRAINING_DATA_PATH, epochs = 100, imgsz = 640)

model.export()