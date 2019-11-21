#include <thread>
#include <signal.h>
#include <string.h>
#include <chrono>

#include "interpolation.h"
#include "mechnical_unit.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	int link_num=6;
	LinkUnit link_unit[link_num];	

	if(link_unit[0].InitActuator((uint8_t)1, QDD_NE30_36) < 0)
	{
		return -1;
	}
	if(link_unit[1].InitActuator((uint8_t)2, QDD_NE30_36) < 0)
	{
		return -1;
	}
	if(link_unit[2].InitActuator((uint8_t)3, QDD_NE30_36) < 0)
	{
		return -1;
	}
	if(link_unit[3].InitActuator((uint8_t)4, QDD_NE30_36) < 0)
	{
		return -1;
	}
	if(link_unit[4].InitActuator((uint8_t)5, QDD_NE30_36) < 0)
	{
		return -1;
	}
	if(link_unit[5].InitActuator((uint8_t)6, QDD_NE30_36) < 0)
	{
		return -1;
	}

	Robot robot;
	if(robot.InitRobot(link_unit,link_num) < 0)
	{
		return -1;
	}

	int axis_num=robot.GetRobotJointNum();
	double joint[axis_num];
	robot.GetCurrentMachineJoint(joint);

	int i;
	cout << "Current joint(degree) : ";
	for(i=0;i<axis_num;i++)
	{
		cout << joint[i]*180/pi << " ";
	}
	cout << endl;

	return 0;
}

