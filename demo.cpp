#include "Jetank/SCS_combi.hpp"
#include "Jetank/Motors.h"


const char* DEVICENAME = "/dev/ttyTHS1";
const int BAUDRATE = 1000000;

const int BEARINGS_MOTOR{1}; // -90 <-0-> 90
    const int ARM_PITCH_MOTOR{2}; // -100 <-15-> 100
    const int ARM_FLIP_MOTOR{3}; // -105 <-0-> 105
    const int CLAW_MOTOR{4}; // -60 <-0-> 20
    const int CAMERA_MOTOR{5}; // -5 <- -45-> -95

	constexpr int BEAR_MAX{90};
	constexpr int BEAR_MIN{-90};

	constexpr int PITCH_MAX{100};
	constexpr int PITCH_MIN{-100};

	constexpr int FLIP_MAX{105};
	constexpr int FLIP_MIN{-105};

	constexpr int CLAW_MAX{20};
	constexpr int CLAW_MIN{-60};

	constexpr int CAMERA_MAX{-5};
	constexpr int CAMERA_MIN{-95};

    std::vector<int> ARM_MOTORS = {BEARINGS_MOTOR, ARM_PITCH_MOTOR, ARM_FLIP_MOTOR, CLAW_MOTOR, CAMERA_MOTOR};

	std::vector<int> move_ranges(int min, int max, double steps=0.1)
	{
		std::vector<int> range;
		int diff = std::abs((max - min));

		double step = ((double)diff) * steps;
		int stp = ((int)(1.0/steps));
		for (int i = 0; i < stp; i++)
		{
			double st = min + (step * i);
			range.push_back(st);
		}
		return range;
	}
inline void move_sleep(void)
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(500ms);
}
int main()
{
	// Gets port of device
	using namespace std::chrono_literals;
	int port = openPort(DEVICENAME,BAUDRATE);
	if(port == -1)
	{
		std::cout << "Failed to open device " << DEVICENAME << std::endl; 
		return -1;
	}

	//Servo s = Servo(DEVICENAME, BAUDRATE);
	//int p = s.getPort();

	for(int i=1; i<6; i++)
	{
		setSpeed(port,i,600);
		std::this_thread::sleep_for(200ms);
	}
	//std::this_thread::sleep_for(200ms);

	/*for(int i=1; i<6; i++)
	{
		moveServo(port,i,-30);
		std::this_thread::sleep_for(200ms);
	}
	*/
	std::vector<int> bear_range = move_ranges(BEAR_MIN, BEAR_MAX);
	std::vector<int> pitch_range = move_ranges(PITCH_MIN, PITCH_MAX);
	std::vector<int> flip_range = move_ranges(FLIP_MIN, FLIP_MAX);
	std::vector<int> claw_range = move_ranges(CLAW_MIN, CLAW_MAX);
	std::vector<int> cam_range = move_ranges(CAMERA_MIN, CAMERA_MAX);
	
	
	Motors m;
	double speed = 0.5;
	m.setSpeed(speed);
	char ch;
	int angl = 4; // 0 to 9, ie 10 steps
	int motor_choise;
	system("stty raw");
	while (1)
	{
		ch = getchar(); 
		system("clear");
		printf("\rArm controls:\n");
		printf("\rControl angle with with q (decrease) and e (increase).\n");
		printf("\rApply angle to a servo with '1' to '5'.\n");
		printf("\r(1): arm rotation, (2): arm pitch, (3): arm flip, (4): claw, (5): camara \n");
		printf("\rServos online. \n\rCurrent angle: %i.\n", angl);		
		printf("\rStop motors by pressing 'z'. Exit program by pressing 'c'.\n\n");
		printf("\rMotor controls:\n");
		printf("\rSteer with w (forward), a (left), d (right), s (backwards).\n");
		printf("\rIncrease or decrease speed by pressing up and down arrow keys.\n");
		printf("\rStop motors by pressing 'z'. Exit program by pressing 'c'.\n\n");
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

		else if (ch == 'z')
		{
			m.moveStop();
		}
		else if (ch == 'c')
		{
			m.moveStop();
			system("stty cooked");
			system("clear");
			exit(1);
		}
		else if (ch == 49)
		{
			//printf("");
			int angle = bear_range.at(angl);
			moveServo(port,BEARINGS_MOTOR, angle);
			move_sleep();	
		}
		else if (ch == 50)
		{
			int angle = pitch_range.at(angl);
			moveServo(port,ARM_PITCH_MOTOR, angle);
			move_sleep();
		}
		else if (ch == 51)
		{
			int angle = flip_range.at(angl);
			moveServo(port,ARM_FLIP_MOTOR, angle);
			move_sleep();
		}
		else if (ch == 52)
		{
			int angle = claw_range.at(angl);
			moveServo(port,CLAW_MOTOR, angle);
			move_sleep();
		}
		else if (ch == 53)
		{
			int angle = cam_range.at(angl);
			moveServo(port,CAMERA_MOTOR, angle);
			move_sleep();
		}
		else if (ch == 'q')
		{
			if (angl > 0)
			{
				angl -= 1;
			}
		}
		else if (ch == 'e')
		{
			if (angl < 9)
			{
				angl += 1;
			}
		}		
		else if (ch == 65)// arrow keys
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
	/*moveServo(port,CLAW_MOTOR, -30);
	std::cout << "ARM_PITCH_MOTOR" << '\n';
	std::this_thread::sleep_for(1000ms);
	moveServo(port,CLAW_MOTOR, -20);*/
	

	//moveAllServos(port,{0,0,0,0,0});
	closePort(port);
	return 0;

}
