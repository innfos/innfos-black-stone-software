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

	//reduction_rate and  rotate direct
	//NE30 reduction_rate=36;
	link_unit[0].SetMotinParameter(36,1);
	link_unit[1].SetMotinParameter(36,1);
	link_unit[2].SetMotinParameter(36,1);
	link_unit[3].SetMotinParameter(36,1);
	link_unit[4].SetMotinParameter(36,1);
	link_unit[5].SetMotinParameter(36,1);

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

