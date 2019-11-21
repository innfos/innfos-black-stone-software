#include <thread>
#include <signal.h>
#include <string.h>
#include <chrono>
#include <math.h>

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
	double start_joint[axis_num];
	double middle_joint[axis_num];
	double target_joint[axis_num];

	//Remeber to execute if you want move the robot.
	robot.ActivatePositionMode();
	robot.GetCurrentMachineJoint(start_joint);
	memcpy(target_joint,start_joint,sizeof(double)*axis_num);
	target_joint[axis_num-1] += 20*pi/180;//Axis axis_num moves 20(degree)

	int i;
	AccDecDate speed[axis_num];

	for (i=0;i<axis_num;i++)
	{
		speed[i].SetParameter(100*pi/180,600*pi/180,3000*pi/180);
	}

	if(MoveJointPath(&robot,start_joint,target_joint,speed) < 0)
	{
		return -1;
	}

	if(MoveJointPath(&robot,target_joint,start_joint,speed) < 0)
	{
		return -1;
	}

	return 0;
}
