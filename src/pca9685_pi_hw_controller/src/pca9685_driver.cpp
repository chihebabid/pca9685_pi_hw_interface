//
// Created by chiheb on 11/05/2026.
//

#include "pca9685_pi_hw_controller/pca9685_driver.h"

namespace rpi_pca9685_hw_controller {
    Pca9685Driver::Pca9685Driver(uint8_t i2c_bus, uint8_t i2c_address,uint8_t freq):i2c_driver_(std::make_unique<I2cDriver>(i2c_bus,
        i2c_address)) {
        // Initialize the PCA9685
        i2c_driver_->write_byte(0x00, 0x00); // MODE1 register: normal mode
        i2c_driver_->write_byte(0x01, 0x04); // MODE2 register: totem pole output
        i2c_driver_->write_byte(0xFE, 0x79); // PRE_SCALE register: set frequency to 50Hz
    }
}