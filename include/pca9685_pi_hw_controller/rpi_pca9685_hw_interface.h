
#ifndef RPI_PCA9685_HW_CONTROLLER_H
#define RPI_PCA9685_HW_CONTROLLER_H
#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/handle.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include <rclcpp/rclcpp.hpp>
namespace rpi_pca9685_hw_controller {
    struct RpiPca9685HwInterface : public hardware_interface::SystemInterface {
        RpiPca9685HwInterface() = default;

        CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

        std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

        std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

        hardware_interface::return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;

        hardware_interface::return_type write(const rclcpp::Time & time, const rclcpp::Duration & period) override;
    };
}
#endif
