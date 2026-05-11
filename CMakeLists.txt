cmake_minimum_required(VERSION 3.8)
project(pca9685_pi_hw_controller)
cmake_policy(SET CMP0167 OLD)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)


add_library(
        pca9685_pi_hw_controller SHARED
        src/pca9685_pi_hw_controller/rpi_pca9685_hw_interface.cpp
        src/pca9685_pi_hw_controller/i2c_driver.cpp
)



target_include_directories(
        pca9685_pi_hw_controller
        PUBLIC
        include
)

ament_target_dependencies(
        pca9685_pi_hw_controller
        hardware_interface
        pluginlib              # ← Ajouté
        rclcpp
        rclcpp_lifecycle
)

# prevent pluginlib from using boost
target_compile_definitions(pca9685_pi_hw_controller PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

pluginlib_export_plugin_description_file(hardware_interface pca9685_hardware_interface.xml)

install(
        TARGETS
        pca9685_pi_hw_controller
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_export_include_directories(
        include
)
ament_export_libraries(
        pca9685_pi_hw_controller
)
ament_export_dependencies(m
        hardware_interface
        pluginlib
        rclcpp
        rclcpp_lifecycle
)
ament_package()
