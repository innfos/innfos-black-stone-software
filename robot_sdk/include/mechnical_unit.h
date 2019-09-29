#ifndef MECHNICAL_UNIT_H
#define MECHNICAL_UNIT_H


#include "base.h"
#include "actuatorcontroller.h"

class AccDecDate
{
public:
	double vel;
	double acc;
	double jerk;
	void SetParameter(double v,double a,double jerk);
};

enum RobotType
{
	NE30_6,
	DOF6_UR2,
	BlackStone,
	DOF7_SRS,
	DOF3_MECHANICAL,
	Othertype,
};

enum ActuatorType
{
	QDD_EL20_36,
	QDD_NE30_36,
	QDD_LITE_NE30_36,
	QDD_PR60_36,
	QDD_PRO_NU80_80_110,
	QDD_PRO_PR60_80_90,
};

class LinkUnit
{
private:
	uint8_t id_; //sca id
	ActuatorType type_;//sca type
	ActuatorController *pointer_;

	//sca parameters
	double max_motor_speed_;//transfer to axis
	double min_soft_limit_;
	double max_soft_limit_;

	int joint_type_;//0:revolute, 1:prismatic

	double reduction_rate_;
	double home_position_;	
	double direct_; //rotation direct


	//dynamics 
	double m_; //mass
	double p_[3];// position of center-of-mass(in the link coordinantes)	
	double Ixx_;//inertia Ixx
	double Ixy_;//inertia Ixy
	double Ixz_;//inertia Ixz
	double Iyy_;//inertia Iyy
	double Iyz_;//inertia Iyz
	double Izz_;//inertia Izz
	double fv_;// viscous friction
	double fc_; //coulomb friction
	double Jm_;//motor inertia 
public:

	AccDecDate joint_speed_;

	//kinematics MDH parameters
	double theta_;
	double alpha_;
	double a_;
	double d_;

	LinkUnit();
	void SetActuatorId(ActuatorController *pointer,uint8_t id);
	void SetMotinParameter(double reduction_rate,double direct);
	void SetParamets(ActuatorController *pointer,
		uint8_t id,
		double reduction_rate,
		double direct,
		double theta,
		double alpha,
		double a,
		double d);
	int GetActuatorData();
	double GetActuatorPositionSlow();
	double GetActuatorPositionFast();
	double GetActuatorCurrentFast();
	double GetActuatorVelocityFast();
	uint32_t GetErrorCode();
	void SetActuatorPosition(double pos);
	int CheckPosition(double joint,double last_joint,double sample);
	void RequestCVPValue();

	~LinkUnit();
};

class Robot
{
private:
	int axis_num_;
	RobotType type_;
	AccDecDate rot_speed_;
	AccDecDate line_speed_;
	vector <uint8_t> idArray;
	ActuatorController *pController;
	LinkUnit link_data_[MAX_AXIS_NUM];
	vector< ActuatorController::UnifiedID > unified_id_array_;

	int GetParametersFromActuator();
	int AddLinkUnit(LinkUnit *link_unit,int axis_num);

public:

	Robot();

	int InitRobot(LinkUnit *link_unit,int axis_num);
	void ActivateCurrentMode();
	void ActivatePositionMode();

	int GetRobotJointNum();
	void RequestCVPValue();
	void AddParaRequestCallback(ActuatorController::doubleFuncPointer callback);
	void ClearAllActuatorCallbacks();
	int GetRobotType();
	uint32_t GetErrorCode();
	void GetCurrentCVPFast(double current[],double vel[],double pos[]);
	void GetCurrentMachineJoint(double angle[]);
	void GetCurrentMachineJointFast(double angle[]);
	int SendMachinePosition(double joint[],double last_joint[]);
	int SendPosition(double joint[],double last_joint[],int sample_us);
	int SetPosition(double joint[]);
	void GetJointSpeedAccDecParameters(AccDecDate *joint_speed);
	void GetLineSpeedAccDecParameters(AccDecDate *line_speed);
	void GetRotateSpeedAccDecParameters(AccDecDate *rot_speed);
	int ForwardKinematics(double q[],double pose[]);
	int InverseKinematics(double q[],double pose[]);
	int ForwardDynamics();
	int InverseDynamics();

	~Robot();

};

void DisableAllActuator();
void GetResourceDataSpeed(
	double *vel_line,
	double *acc_line,
	double *dec_line,
	double *jerk_line,
	double *vel_rot,
	double *acc_rot,
	double *dec_rot,
	double *jerk_rot);

#endif
