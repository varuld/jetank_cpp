#include "Jetank/Motors.h"
#include "Jetank/Servos.h"
#include <thread>
#include <chrono>
#include <string>

int serve()
{
	using namespace std::chrono_literals;

	Servos servos;
	if(!servos.isConnected())
	{
		std::cout<<"Could not connect\n";
		return -1;
	}

	for(int i=1;i<6;i++)
	{
		servos.setServoSpeed(i,400);
	}


	for(int i=1;i<6;i++)
	{
		servos.setServoAngle(i,30);
		std::this_thread::sleep_for(200ms);
	}

	for(int i=1;i<6;i++)
	{
		servos.setServoAngle(i,0);
		std::this_thread::sleep_for(200ms);
	}
}
void movement_demo_script()
{
	Motors m;
	double speed = 0.5;
	m.setSpeed(speed);
	//char ch;

	using namespace std::chrono_literals;
	//system("stty raw");

	//(Motors::*p_forward_move)(&Motors::m);// = Motors::moveForward;
	//m.p_forward_move = &Motors::Motors::moveForward
	//run_f_ptr(*Motors::p_forward_move);

	m.moveForward();
	std::this_thread::sleep_for(200ms);

	m.moveStop();
	/*system("stty cooked");
	system("clear");
	exit(1);*/
	return;
}
void motor_demo_run()
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
int main()
{
	//motor_demo_run();
	movement_demo_script();
	//int s = serve();
}
