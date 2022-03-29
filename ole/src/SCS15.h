#pragma once
#include <string>
#include <array>





int openPort(std::string device_name, int baudrate);

int setSpeed(int port,uint8_t scs_id, uint16_t speed);

int moveServo(int port, uint8_t scs_id, int16_t angle);

int moveAllServos(int port, const std::array<int16_t,5>& angles );

int closePort(int port);




// Draft of what the class can look like
struct SCS15
{
    uint16_t speed;
    uint16_t angle;
};

class SCS15_Controller
{
public:
    int setSpeed();
    int setAngle();
    int getPort();
private:
    int speed = 0;
    int port = -1; 
    SCS15 servos[5];
};