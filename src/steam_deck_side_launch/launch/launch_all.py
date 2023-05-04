from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="controller_input",
            executable="controller_input"
        ),
        Node(
            package="target_recognize",
            executable="target_recognize"
        )
    ])