#include "Jetank/motors.h"
#include "Jetank/Servos.h"

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
        printf("\rMotor controls:\n");
        printf("\rSteer with w (forward), a (left), d (right), s (backwards).\n");
        printf("\rIncrease or decrease speed by pressing up and down arrow keys.\n");
        printf("\rStop motors by pressing 's'. Exit program by pressing 'q'.\n\n");
        printf("\r Motors online. \n\rCurrent speed: %3.1f.\n", speed);
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
            if (speed < 1.0)
            {
                speed += 0.1;
                m.setSpeed(speed);
            }
        }
        else if (ch == 66)
        {
            if (speed > 0.0)
            {
                speed -= 0.1;
                m.setSpeed(speed);
            }
        }
    }
}
