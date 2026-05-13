//
// Created by chiheb on 11/05/2026.
//

#ifndef WS_ROS_PI_PCA9685_DRIVER_H
#define WS_ROS_PI_PCA9685_DRIVER_H
#include "i2c_driver.h"
#include <memory>
namespace rpi_pca9685_hw_controller {
    constexpr uint8_t PCA9685_MODE1  {0x0};
    constexpr uint8_t  PCA9685_PRESCALE {0xFE};
    constexpr uint8_t LED0_ON_L {0x6};
    constexpr uint8_t LED0_ON_H {0x7};
    constexpr uint8_t LED0_OFF_L {0x8};
    constexpr uint8_t LED0_OFF_H {0x9};
    constexpr uint8_t ALL_LED_ON_L {0xFA};
    constexpr uint8_t ALL_LED_ON_H {0xFB};
    constexpr uint8_t ALL_LED_OFF_L {0xFC};
    constexpr uint8_t ALL_LED_OFF_H {0xFD};
    struct Pca9685Driver {
        Pca9685Driver(uint8_t i2c_bus, uint8_t i2c_address,uint8_t freq=50);
        void set_servo_degree(uint8_t channel, uint8_t degree);
        void set_pulsewidth_min_max(uint16_t min, uint16_t max);
        void set_pulse_width(uint8_t channel, uint16_t pw);
        void set_all_pulse_width(uint16_t pw);
        ~Pca9685Driver()=default;
    private:
        void set_pwm_frequency(uint8_t freq);
        std::unique_ptr<I2cDriver> i2c_driver_;
        uint16_t pulse_width_min_ {500};
        uint16_t pulse_width_max_ {2500};
    };
}


#endif //WS_ROS_PI_PCA9685_DRIVER_H
