#pragma once
#include <string>
#include <array>

int openPort(std::string device_name, int baudrate);

int setSpeed(int port,uint8_t scs_id, uint16_t speed);

int moveArm(int port, uint8_t scs_id, int16_t angle);

int moveAll(int port, const std::array<int16_t,5>& angles );

int closePort(int port);