//
// Created by chiheb on 10/05/2026.
//
#include "pca9685_pi_hw_controller/pca9685_pi_hw_interface.h"

namespace rpi_pca9685_hw_controller {
    hardware_interface::CallbackReturn Pca9685PiHwInterface::on_init(const hardware_interface::HardwareInfo &info) {
        if (hardware_interface::SystemInterface::on_init(info) != CallbackReturn::SUCCESS) {
            return CallbackReturn::ERROR;
        }
        return CallbackReturn::SUCCESS;
    }

}

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
    rpi_pca9685_hw_controller::Pca9685PiHwInterface, hardware_interface::SystemInterface)