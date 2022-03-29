#include "Servos.h"
#include <thread>



int main()
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
