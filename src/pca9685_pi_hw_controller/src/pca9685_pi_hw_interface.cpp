//
// Created by chiheb on 10/05/2026.
//
#include "pca9685_pi_hw_controller/pca9685_pi_hw_interface.h"
#include "rclcpp/rclcpp.hpp"

namespace rpi_pca9685_hw_controller {


    hardware_interface::CallbackReturn Pca9685PiHwInterface::on_init(const hardware_interface::HardwareComponentInterfaceParams & params)
    {
        if (hardware_interface::SystemInterface::on_init(params) != CallbackReturn::SUCCESS) {
            return CallbackReturn::ERROR;
        }
        if (info_.joints.size()==0 or info_.joints.size() >16) {
            RCLCPP_ERROR(rclcpp::get_logger("Pca9685PiHwInterface"), "Error : Incorrect number of joints, %zu found!", info_.joints.size());
            return CallbackReturn::ERROR;
        }

        for (const auto &param : params.hardware_info.hardware_parameters) {
            if (param.first == "i2c_bus") {
                i2c_bus_number_ = std::stoi(param.second);
            } else if (param.first == "i2c_address") {
                i2c_address_ = std::stoi(param.second, nullptr, 0);
            } else if (param.first == "pwm_frequency") {
                pwm_frequency_ = std::stoi(param.second);
            }
        }

        joint_configs_.resize(info_.joints.size());
        for (size_t i {}; i < info_.joints.size(); ++i) {
            joint_configs_[i].channel=stoll(info_.joints[i].parameters["channel"]);
        }
        return CallbackReturn::SUCCESS;
    }

    std::vector<hardware_interface::StateInterface> Pca9685PiHwInterface::export_state_interfaces() {
        RCLCPP_DEBUG(rclcpp::get_logger("Pca9685PiHwInterface"), "Export state interfaces");
        std::vector<hardware_interface::StateInterface> state_interfaces;
        for (size_t i = 0; i < info_.joints.size(); i++)   {

        }



        return state_interfaces;
    }

}

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
    rpi_pca9685_hw_controller::Pca9685PiHwInterface, hardware_interface::SystemInterface)