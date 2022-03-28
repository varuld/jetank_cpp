#include "motors.h"

int main()
{
    Motors m;
    double speed = 0.5;
    m.setSpeed(speed);
    char ch;
    system("stty raw");
    while (1)
    {
        ch = getchar();
        system("clear");
        printf("\rMotors online. Speed: %3.1f\n", speed);
        if (ch == 'w')
        {
            m.moveForward();
        }
        
        else if (ch == 'd')
        {
            m.moveRight();
        }
        
        else if (ch == 'a')
        {
            m.moveLeft();
        }
    
        else if (ch == 's')
        {
            m.moveBackward();
        }
        
        else if (ch == 'x')
        {
            m.moveStop();
        }
        
        else if (ch == 'q')
        {
            m.moveStop();
            system("stty cooked");
            system("clear");
            exit(1);
        }
        else if (ch == 65)
        {
            speed += 0.1;
            m.setSpeed(speed);
        }
        else if (ch == 66)
        {
            speed -= 0.1;
            m.setSpeed(speed);
        }
    }
}