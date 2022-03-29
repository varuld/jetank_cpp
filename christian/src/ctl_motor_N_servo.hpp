#ifndef MOTORS_OBJ_INIT_H_DEF
#define MOTORS_OBJ_INIT_H_DEF

#include "Servos.h"
#include "Motors.h"

#include <thread>


constexpr double INIT_SPEED{0.5};
constexpr double SPEED_STEP{0.1};

constexpr char SPEED_UP{65};
constexpr char SPEED_DOWN{66};

constexpr char FORWARD{'w'};
constexpr char BACK{'s'};
constexpr char RIGHT{'d'};
constexpr char LEFT{'a'};

constexpr char PAUSE{'x'};
constexpr char QUITE{'q'};

constexpr std::string MOTOR_OBJ_NAME{"m"};

int servo_exp()
{
    using namespace std::chrono_literals;

    // Gets port of device
    Servos servos = Servos();
    if(!servos.isConnected())
    {
        std::cout<<"Could not open connection\n";
    }
    servos.setServoSpeed(2,300);
    servos.setServoAngle(2,45);

    for(int i=0;i<10;i++)
    {
        std::this_thread::sleep_for(100ms);
        std::cout << "Current angle is: "<<servos.getServoData(2).current_angle <<'\n';
    }

    servos.setServoAngle(2,0);

    for(int i=0;i<10;i++)
    {
        std::this_thread::sleep_for(100ms);
        std::cout << "Current angle is: "<<servos.getServoData(2).current_angle <<'\n';
    }

    return 0;
}
//int motor_exp();
Motors motor_ojb(std:string motors_name=MOTOR_OBJ_NAME, char up_ctl =FORWARD, char back_clt=BACK, char right_clt=RIGHT, char left_ctl=LEFT , char pause_clt=PAUSE, char quite_clt=QUITE);
{

    Motors m;
    double speed = INIT_SPEED; //0.5;
    m.setSpeed(speed);
    char ch;
    system("stty raw");
    while (1)
    {
        ch = getchar();
        system("clear");
        printf("\rMotors online. Speed: %3.1f\n", speed);
        if (ch ==  up_ctl) //'w')
        {
            m.moveForward();
        }

        else if (ch == right_clt) //'d')
        {
            m.moveRight();
        }

        else if (ch == left_ctl) //'a')
        {
            m.moveLeft();
        }

        else if (ch == back_clt) //'s')
        {
            m.moveBackward();
        }

        else if (ch == pause_clt)//'x')
        {
            m.moveStop();
        }

        else if (ch == quite_clt) //'q')
        {
            m.moveStop();
            system("stty cooked");
            system("clear");
            exit(1);
        }
        else if (ch == SPEED_UP) //65)
        {
            speed += SPEED_STEP; //0.1;
            m.setSpeed(speed);
        }
        else if (ch == SPEED_DOWN) //66)
        {
            speed -= SPEED_STEP;// 0.1;
            m.setSpeed(speed);
        }
    }
}
#endif
