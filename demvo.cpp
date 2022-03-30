#include "Jetank/Motors.h"
#include "Jetank/Servos.h"

#include <thread>
#include <chrono>
#include <string>


int main()
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
