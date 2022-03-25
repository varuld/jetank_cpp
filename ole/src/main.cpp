#include <iostream>
#include <chrono>
#include <thread>
#include "SCS15.h"


const char* DEVICENAME = "/dev/ttyTHS1";
const int BAUDRATE = 1000000;

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


	for(int i=1; i<6; i++)
	{
		setSpeed(port,i,200);
		std::this_thread::sleep_for(200ms);
	}


	for(int i=1; i<6; i++)
	{
		moveArm(port,i,-30);
		std::this_thread::sleep_for(200ms);
	}

	for(int i=1; i<6; i++)
	{
		moveArm(port,i,0);
		std::this_thread::sleep_for(200ms);
	}
	closePort(port);
	return 0;

}
