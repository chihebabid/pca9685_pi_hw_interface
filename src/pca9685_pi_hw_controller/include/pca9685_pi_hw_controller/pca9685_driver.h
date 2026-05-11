//
// Created by chiheb on 11/05/2026.
//

#ifndef WS_ROS_PI_PCA9685_DRIVER_H
#define WS_ROS_PI_PCA9685_DRIVER_H
#include "i2c_driver.h"
#include <memory>
namespace rpi_pca9685_hw_controller {
    struct Pca9685Driver {
        Pca9685Driver(uint8_t i2c_bus, uint8_t i2c_address,uint8_t freq=50);
    private:
    std::unique_ptr<I2cDriver> i2c_driver_;
    };
}


#endif //WS_ROS_PI_PCA9685_DRIVER_H
