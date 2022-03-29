#include "Servos.h"
#include "Motors.h"

#include <thread>


constexpr double INIT_SPEED{0.5};
constexpr double SPEED_STEP{0.1};

constexpr char SPEED_UP{65};
constexpr char SPEED_DOWN{66};

constexpr char FREM{'w'};
constexpr char BAK{'s'};
constexpr char HJR{'d'};
constexpr char VNST{'a'};

constexpr char PAUSE{'x'};
constexpr char QUITE{'q'};

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
int motor_exp()
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
		if (ch ==  FREM) //'w')
		{
			m.moveForward();
		}

		else if (ch == HJR) //'d')
		{
			m.moveRight();
		}

		else if (ch == VNST) //'a')
		{
			m.moveLeft();
		}

		else if (ch == BAK) //'s')
		{
			m.moveBackward();
		}

		else if (ch == PAUSE)//'x')
		{
			m.moveStop();
		}

		else if (ch == QUITE) //'q')
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
int main(int argc, char const *argv[])
{
	return 0;
}
