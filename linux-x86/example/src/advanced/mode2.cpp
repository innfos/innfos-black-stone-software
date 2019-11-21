#include <math.h>
#include <thread>
#include <signal.h>
#include <string.h>
#include <chrono>

#include "interpolation.h"
#include "mechnical_unit.h"

using namespace std;

static bool bExit = false;

void ProcessSignal(int sign)
{
    bExit = true;
}

int main(int argc, char *argv[])
{
	int link_num=6;
	LinkUnit link_unit[link_num];	

	// Init the link
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
    signal(SIGINT,ProcessSignal);

	//example : one minute data
	int time=1;//minute
	int sample=2500;//us
	int record_num=60.0*1000000.0/sample;
	double *pos_list = new double [record_num*axis_num];
	if(!pos_list)
	{
		cout << "Memory error !" << endl;
		return -1;
	}

	cout << "Recording ... " << endl;
	bExit = false;
	int count=0;

	robot.ActivateCurrentMode();
	while (!bExit &&count<=record_num) 
	{
		robot.RequestCVPValue();
		std::this_thread::sleep_for(std::chrono::microseconds(2500));//us
		ActuatorController::processEvents();
		robot.GetCurrentMachineJointFast(&pos_list[count*axis_num]);
		count ++ ;
	}
	cout << "count = " << record_num << endl;	
	cout << "count = " << count << endl;
	cout << "Record successfully." << endl;
	bExit = false;
	int i;
	AccDecDate speed[axis_num];
	for (i=0;i<axis_num;i++)
	{
		speed[i].SetParameter(100*pi/180,600*pi/180,3000*pi/180);
	}

	//Remeber to execute if you want move the robot.
	char any_char[256];
	cout << "Waiting : " << endl;
	cin >> any_char;

	robot.ActivatePositionMode();
	double start_joint[axis_num];
	robot.GetCurrentMachineJoint(start_joint);
	if(MoveJointPath(&robot,start_joint,pos_list,speed) < 0)
	{
		delete [] pos_list;
		return -1;
	}
	for (i=1;i<count;i++)
	{
		if (robot.SendPosition(&pos_list[axis_num*i],&pos_list[axis_num*(i-1)]) < 0)
		{
			delete [] pos_list;
			return -1;
		}
		this_thread::sleep_for(std::chrono::microseconds(sample));				
	}

	delete [] pos_list;
	return 0;
}
