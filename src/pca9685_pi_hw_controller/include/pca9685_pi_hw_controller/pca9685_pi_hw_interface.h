#ifndef RPI_PCA9685_HW_CONTROLLER_H
#define RPI_PCA9685_HW_CONTROLLER_H
#include "pca9685_pi_hw_controller/pca9685_driver.h"
#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/handle.hpp>
#include <hardware_interface/types/hardware_interface_return_values.hpp>
#include <rclcpp/rclcpp.hpp>

namespace rpi_pca9685_hw_controller {
    struct Pca9685PiHwInterface : public hardware_interface::SystemInterface {
        Pca9685PiHwInterface() = default;

        hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareComponentInterfaceParams & params) override;

        std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

        std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

        hardware_interface::return_type read(const rclcpp::Time &time, const rclcpp::Duration &period) override;

        hardware_interface::return_type write(const rclcpp::Time &time, const rclcpp::Duration &period) override;
    private:
        std::unique_ptr<Pca9685Driver> pca9685_driver_;
    };
}
#endif
