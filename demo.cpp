#include "Jetank/Motors.h"
#include "Jetank/Servos.h"

void serve()
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
	serve();
}
