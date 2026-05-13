//
// Created by chiheb on 11/05/2026.
//

#include "pca9685_pi_hw_controller/pca9685_driver.h"
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std::chrono_literals;
namespace rpi_pca9685_hw_controller {
    Pca9685Driver::Pca9685Driver(uint8_t i2c_bus, uint8_t i2c_address,uint8_t freq):i2c_driver_(std::make_unique<I2cDriver>(i2c_bus,
        i2c_address)) {
        (*i2c_driver_).set_slave().set_7bits_mode();
        // Initialize the PCA9685
        i2c_driver_->write_byte(PCA9685_MODE1, 0x00); // MODE1 register: normal mode
        i2c_driver_->write_byte(0x01, 0x04); // MODE2 register: totem pole output
        set_pwm_frequency(freq);
    }

    void Pca9685Driver::set_pwm_frequency(uint8_t freq) {
        float frequency{freq*0.8449f};
        float prescaleval {25'000'000};       // 25MHz
        prescaleval /= 4096;                // 4096 PWM cycles
        prescaleval /= frequency;                // Calculate the frequency division value
        prescaleval -= 1;
        float prescale {prescaleval + 0.5f};
        uint8_t oldmode {i2c_driver_->read_byte(PCA9685_MODE1)}; // MODE1 register
        uint8_t newmode {static_cast<uint8_t>((oldmode&0x7F) | 0x10)};
        i2c_driver_->write_byte(PCA9685_MODE1, newmode); // Go to sleep
        i2c_driver_->write_byte(PCA9685_PRESCALE, static_cast<uint8_t>(prescale)); // Set predivider
        i2c_driver_->write_byte(PCA9685_MODE1, oldmode);
        std::this_thread::sleep_for(5000us);
        i2c_driver_->write_byte(PCA9685_MODE1, oldmode | 0xa0);
    }

    void Pca9685Driver::set_servo_degree(uint8_t channel, uint8_t degree) {
        degree=std::clamp(degree, static_cast<uint8_t>(0), static_cast<uint8_t>(180));
        uint16_t pulse_width {static_cast<uint16_t>(((pulse_width_max_ - pulse_width_min_) * degree / 180) + pulse_width_min_)};
        set_pulse_width(channel,pulse_width);
    }

    void Pca9685Driver::set_pulse_width(uint8_t channel,uint16_t pw) {
        i2c_driver_->write_byte(LED0_ON_L+4*channel, 0);
        i2c_driver_->write_byte(LED0_ON_L+4*channel + 1,0);
        i2c_driver_->write_byte(LED0_ON_L+4*channel + 2, pw & 0xFF);
        i2c_driver_->write_byte(LED0_ON_L+4*channel + 3, pw>>8);
    }

    void Pca9685Driver::set_all_pulse_width(uint16_t pw) {
        i2c_driver_->write_byte(ALL_LED_ON_L, 0);
        i2c_driver_->write_byte(ALL_LED_ON_H, 0);
        i2c_driver_->write_byte(ALL_LED_OFF_L, pw & 0xFF);
        i2c_driver_->write_byte(ALL_LED_OFF_H, pw >> 8);
    }

    void Pca9685Driver::set_pulsewidth_min_max(uint16_t min, uint16_t max) {
        pulse_width_min_ = min;
        pulse_width_max_ = max;
    }
}