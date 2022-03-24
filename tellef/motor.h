#ifndef MOTOR_H
#define MOTOR_H

// Adresses
constexpr int PWM_ADDR             = 0x60;
constexpr int I2C_ON_LOW           = 0x06;
constexpr int I2C_ON_HIGH          = 0x07;
constexpr int I2C_OFF_LOW          = 0x08;
constexpr int I2C_OFF_HIGH         = 0x09;

// Variables
constexpr int FREQUENCY            = 1600;


class Motor
{
public:
    Motor();

private:
    int speed = 0;
};

#endif
