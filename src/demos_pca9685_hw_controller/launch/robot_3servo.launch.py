from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from launch.substitutions import PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

    ld = LaunchDescription()
    pkg_share = FindPackageShare('pi_hw_controller')
    xacro_path = 'urdf/robot_with_pca9685.urdf.xacro'

    robot_description = PathJoinSubstitution([
        get_package_share_directory('demos_pca9685_hw_controller'),
        xacro_path
    ])

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description':Command(['xacro ', robot_description])
        }]
    )
    joint_state_publisher_gui = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        output='screen')

    ld.add_action( joint_state_publisher_gui )
    ld.add_action( robot_state_publisher_node )

    return ld