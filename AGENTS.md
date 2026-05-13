# AGENTS.md - AI Coding Agent Guidelines for pca9685_pi_hw_controller

## Architecture Overview
This is a ROS2 hardware interface package for Raspberry Pi, implementing `hardware_interface::SystemInterface` to control PCA9685 16-channel PWM driver over I2C. Core components include:
- **Hardware interface**: `Pca9685PiHwInterface` exports command/state interfaces for servo joints, mapping position commands to PWM pulses
- **PWM driver**: `Pca9685Driver` handles PCA9685 initialization, frequency setting, and servo angle-to-pulse conversion
- **I2C driver**: `I2cDriver` provides low-level I2C communication using Linux ioctl

Key design decisions: Uses ros2_control framework for standardized hardware abstraction; supports up to 16 joints (channels); default PWM frequency 50Hz for servos.

## Build and Development Workflow
- **Cross-compilation**: Built via workspace's `./compile_all.sh` using `PI.cmake` toolchain for aarch64 targeting Raspberry Pi
- **Dependencies**: Requires `hardware_interface`, `pluginlib`, `rclcpp_lifecycle` from ROS2 Jazzy; no external libraries beyond standard Linux I2C
- **Plugin export**: Uses `pluginlib_export_plugin_description_file` for ros2_control discovery (see `pca9685_pi_hw_controller.xml`)
- **Testing**: No specific tests; integrate with ros2_control controllers for validation

## Key Dependencies and Integrations
- **ROS2 Jazzy**: `hardware_interface` for SystemInterface, `pluginlib` for dynamic loading, `rclcpp_lifecycle` for lifecycle management
- **Hardware**: PCA9685 I2C PWM driver (default address 0x40); Raspberry Pi I2C bus (default /dev/i2c-1)
- **Integration**: Exports as plugin for ros2_control; joints configured via URDF parameters (channel, pulse limits, angle ranges)

## Code Patterns and Conventions
- **Class structure**: `Pca9685PiHwInterface` inherits `SystemInterface`; uses `JointConfigData` struct for per-joint config (see `pca9685_pi_hw_interface.h`)
- **Parameter parsing**: `on_init` reads hardware parameters (i2c_bus, i2c_address, pwm_frequency) and joint parameters (channel, min/max pulse/angle)
- **Interface export**: `export_command_interfaces`/`export_state_interfaces` create handles for "position" interface type
- **Read/write cycle**: `read` mirrors command to state (no feedback); `write` converts angle commands to PWM via `Pca9685Driver::set_servo_degree`
- **Error handling**: Throws `std::runtime_error` on I2C failures; returns `ERROR` from write on PWM set failures
- **I2C operations**: Uses ioctl for slave addressing and 7-bit mode; writes/reads bytes for register access (see `I2cDriver::write_byte`/`read_byte`)

Reference files: `src/pca9685_pi_hw_interface.cpp` (main logic), `include/pca9685_pi_hw_controller/pca9685_driver.h` (PWM API), `pca9685_pi_hw_controller.xml` (plugin description)</content>
<parameter name="filePath">/home/chiheb/workspace_ros_group/ws_ros_pi/src/pca9685_pi_hw_controller/AGENTS.md
