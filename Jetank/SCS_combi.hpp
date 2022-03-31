#ifndef SCS_HEADER
#define SCS_HEADER

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <array>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <termio.h>
#include <cmath>


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

/*class Servo
{*/

    // Packet Fields
    const int PKT_HEADER0 = 0;
    const int PKT_HEADER1 = 1;
    const int PKT_ID = 2;
    const int PKT_LENGTH = 3;
    const int PKT_INSTRUCTION = 4;
    const int PKT_ERROR = 4;
    const int PKT_PARAMETER0 = 5;

    // Addresses
    const int ADDR_STS_GOAL_SPEED = 46;
    const int ADDR_STS_GOAL_POSITION = 42;
    const int ADDR_SCS_PRESENT_POSITION  = 56;


    // Instructions
    const int INST_WRITE = 3;
    const int INST_SYNC_WRITE = 131;

    // Angle Constants
    const int SERVO_INPUT_RANGE = 850;
    const int SERVO_ANGLE_RANGE = 180;

    
    /*int port;
    char* DEVICENAME;
    int BAUDRATE;*/
/*public:
    Servo(char* DEVICENAME="/dev/ttyTHS1", int BAUDRATE=1000000)
    {
        this->DEVICENAME = DEVICENAME;
        this->BAUDRATE = BAUDRATE;
        int port = openPort(DEVICENAME,BAUDRATE);
        if(port == -1)
        {
            std::cout << "Failed to open device " << DEVICENAME << std::endl; 
            //exit(1);
            //return -1;
        }
    }
    ~Servo()
    {
        closePort(port);
        //close(port);
    }
    int getPort() const {return port;}*/
    int openPort(std::string devicename,int baudrate)
    {
        int port = ::open(devicename.c_str() ,O_RDWR | O_NOCTTY | O_SYNC);
        struct termios tty;

        if(tcgetattr(port,&tty)!=0)
        {
            return -1;
        }
        cfmakeraw(&tty);
        tty.c_iflag &= ~(IXON | IXOFF);

        cfsetspeed(&tty, baudrate);
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 0;
        int err = ::tcsetattr(port, TCSAFLUSH, &tty);
        if (err != 0) {
            ::close(port);
            port = -1;
        }
        return port;
    }

    int closePort(int port)
    {
        return close(port);
    }

    int setSpeed(int port,uint8_t scs_id, uint16_t speed)
    {
        uint8_t txpacket[7 + 2];
        txpacket[PKT_HEADER0] = 0xFF;
        txpacket[PKT_HEADER1] = 0xFF;
        txpacket[PKT_ID] = scs_id;
        txpacket[PKT_LENGTH] = 2 + 3;       /* SPEED: 2 bytes. */
                                            /* INSTRUCTION + ADDRESS + CHECKSUM : 3 bytes */

        txpacket[PKT_INSTRUCTION] = INST_WRITE;
        txpacket[PKT_PARAMETER0] = ADDR_STS_GOAL_SPEED; 

        /* Insert data with swapped endianess */
        txpacket[PKT_PARAMETER0 + 1] = speed >> 8;
        txpacket[PKT_PARAMETER0 + 2] = speed & 0xFF;


        /* Calculate the checksum */
        uint8_t checksum = 0;
        for(int i=2; i < 8;i++)
        {
            checksum += txpacket[i];
        }
        checksum = ~checksum & 0xFF; /* Flip bits */
        txpacket[8] = checksum;

        /* Write to device */
        ssize_t written_length = write(port,txpacket,9);
        if (written_length != 9)
        {
            return -1;
        }
        return 0;
    }

    int moveServo(int port, uint8_t scs_id, int16_t angle)
    {
        int16_t offset = 512 + (SERVO_INPUT_RANGE * angle)/SERVO_ANGLE_RANGE;
        uint8_t txpacket[7 + 4];        
        txpacket[PKT_ID] = 254;             /* ID of broadcast message */

        txpacket[PKT_LENGTH] = 3 + 4;       /* SCS_ID + OFFSET = 3 bytes */
                                            /* INSTRUCTION + ADDRESS + DATA_LENGTH + CHECKSUM */
        txpacket[PKT_INSTRUCTION] = INST_SYNC_WRITE;

        txpacket[PKT_PARAMETER0 ] = ADDR_STS_GOAL_POSITION;
        txpacket[PKT_PARAMETER0 + 1] = 2;   /* DATA_LENGTH */
        txpacket[PKT_PARAMETER0 + 2] = scs_id;

        /* Insert data with swapped ednianess */
        txpacket[PKT_PARAMETER0 + 3] = offset >>8;
        txpacket[PKT_PARAMETER0 + 4] = offset & 0xFF;

        txpacket[PKT_HEADER0] = 0xFF;
        txpacket[PKT_HEADER1] = 0xFF;

        uint8_t checksum = 0;
        for(int i=2; i < 10;i++)
        {
            checksum += txpacket[i];
        }
        checksum = ~checksum & 0xFF; //Flip bits
        txpacket[10] = checksum;

        ssize_t written_length = write(port,txpacket,11);
        if (written_length != 11)
        {
            return -1;
        }
        return 0;
    }




    // DON'T USE WITH HIGH SPEED!
    int moveAllServos(int port, const std::array<int16_t,5>& angles )
    {
        int16_t offsets[angles.size()];
        for(int i=0;i<angles.size();i++)
        {
            offsets[i] = 512 + (SERVO_INPUT_RANGE * angles[i])/SERVO_ANGLE_RANGE;
        }

        uint8_t txpacket[8 + 3*angles.size()];

        txpacket[PKT_HEADER0] = 0xFF;
        txpacket[PKT_HEADER1] = 0xFF;
        txpacket[PKT_ID] = 254;         /* BROADCAST_ID */
        txpacket[PKT_LENGTH] = 3*5 + 4; 
        txpacket[PKT_INSTRUCTION] = INST_SYNC_WRITE;

        txpacket[PKT_PARAMETER0 ] = ADDR_STS_GOAL_POSITION;
        txpacket[PKT_PARAMETER0 + 1] = 2; //len

        int data_start = PKT_PARAMETER0 + 2;
        for(int i=0;i<angles.size();i++)
        {
            txpacket[data_start + 3*i] = i + 1;      /* SCS_ID  */

            /* Swap endianness */
            txpacket[data_start + 3*i + 1] = offsets[i] >> 8; 
            txpacket[data_start + 3*i + 2] = offsets[i] & 0xFF;
        }

        uint8_t checksum = 0;
        for(int i=2; i < 22;i++)
        {
            checksum += txpacket[i];
        }
        checksum = ~checksum & 0xFF; //Flip bits
        txpacket[22] = checksum;


        
        ssize_t written_length = write(port,txpacket,23);
        if (written_length != 23)
        {
            return -1;
        }
        return 0;
    }
//};
#endif