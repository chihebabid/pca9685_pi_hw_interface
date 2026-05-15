from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    # URDF inline
    robot_description = """<?xml version="1.0"?>
<robot name="pca9685_robot">
  <link name="base_link"/>
  <ros2_control name="PCA9685System" type="system">
    <hardware plugin="rpi_pca9685_hw_controller/Pca9685PiHwInterface">
      <param name="i2c_bus">1</param>
      <param name="i2c_address">0x40</param>
      <param name="pwm_frequency">50</param>
    </hardware>
    <joint name="servo_pan">
      <command_interface name="position"/>
      <state_interface name="position"/>
      <param name="channel">0</param>
      <param name="min_pulse_us">500</param>
      <param name="max_pulse_us">2500</param>
      <param name="min_angle_deg">0</param>
      <param name="max_angle_deg">180</param>
    </joint>
    <joint name="servo_tilt">
      <command_interface name="position"/>
      <state_interface name="position"/>
      <param name="channel">1</param>
      <param name="min_pulse_us">1000</param>
      <param name="max_pulse_us">2000</param>
      <param name="min_angle_deg">0</param>
      <param name="max_angle_deg">180</param>
    </joint>
    <joint name="gripper">
      <command_interface name="position"/>
      <state_interface name="position"/>
      <param name="channel">2</param>
      <param name="min_pulse_us">600</param>
      <param name="max_pulse_us">2400</param>
      <param name="min_angle_deg">0</param>
      <param name="max_angle_deg">90</param>
    </joint>
  </ros2_control>
</robot>"""

    return LaunchDescription([
        # 1. Robot State Publisher (publie le topic /robot_description)
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': robot_description}]
        ),

        # 2. Controller Manager (écoute le topic)
        Node(
            package='controller_manager',
            executable='ros2_control_node',
            name='controller_manager',
            output='screen',
            parameters=[{'update_rate': 50}]
        ),

        # 3. Spawners
        Node(
            package='controller_manager',
            executable='spawner',
            arguments=['joint_state_broadcaster', '--controller-manager', '/controller_manager'],
            output='screen'
        ),
        Node(
            package='controller_manager',
            executable='spawner',
            arguments=['forward_position_controller', '--controller-manager', '/controller_manager'],
            output='screen'
        ),
    ])
