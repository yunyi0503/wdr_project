from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            output='screen'),
        Node(
            package='ros_7489',
            executable='set_background_color',  # 启动设置背景颜色的节点
            output='screen'),
        Node(
            package='ros_7489',
            executable='spawn_jerry',
            output='screen'),
        Node(
            package='ros_7489',
            executable='rotate_jerry',
            output='screen'),
        Node(
            package='ros_7489',
            executable='subscribe_jerry_position',
            output='screen'),
        Node(
            package='ros_7489',
            executable='broadcast_tf',
            output='screen'),
        Node(
            package='ros_7489',
            executable='follow_jerry',
            output='screen'),
    ])
