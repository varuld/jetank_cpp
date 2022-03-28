#include "helper_funcs.hpp"
#include "stepper_move.hpp"
#include "move_wrapper.hpp"

int main()
{
    int file;
    int adapter_nr = 1;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0)
    {
        printf("Could not open %s.\n", filename);
        return -1;
    }



    if (ioctl(file, I2C_SLAVE, addr) < 0)
    {
        printf("IO Control failed.\n");
        return -1;
    }
    initialize(file);
    double speed = 0.4;
    char ch;
    bool running = false, speed_changed = false, turn_right = false;
    system("stty raw");
    while (1)
    {
        if (speed_changed)
        {
            printf("Current speed: %3.1f\n", speed);
        }
        ch = getchar();
        if (ch == 'w' && !running || speed_changed)
        {
            forward(file, speed);
			/*if (speed < 0)
			{
            	//forward(file, speed);
				backward(file, speed);
			}
			else
			{
            	forward(file, speed);
				//backward(file, speed);
			}
			*/
            running = true;
            speed_changed = false;
        }
        else if (ch == 'w' && !running || turn_right)
		{
			rightward(file, speed);
		}
        else if (ch == 's' && running)
        {
            stop_forward(file);
            running = false;
        }
		else if (ch == 's' && turn_right)
        {
            stop_rightward(file);
            turn_right = false;
        }
        else if (ch == 65)
        {
            speed += 0.1;
            speed_changed = true;
        }
        else if (ch == 66)
        {
            speed -= 0.1;
            speed_changed = true;
        }
		else if (ch == 67)
        {
            //speed += 0.1;
            //speed_changed = true;
			turn_right = true;
        }
/*		else if (ch == 68)
        {
            speed += 0.1;
            speed_changed = true;
        }*/
        else if (ch == 'q')
        {
            if (running)
            {
                stop_forward(file);
            }
            system("stty cooked");
            system("clear");
            return 0;
        }
    }
}
