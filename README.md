# innfos-robot-cpp-sdk

cd innfos-robot-cpp-sdk/example

mkdir build

cmake ..

make

可执行文件存储在bin文件夹下

5个demo

mode0： 文件夹bin/basic下     功能: 失能机器人

mode1： 文件夹bin/advanced下  功能:异步方式连续记录机器人关节点位（弧度），并打印到终端

mode2： 文件夹bin/advanced下  功能:连续记录机器人关节点位（弧度）一分钟，之后复现该轨迹

mode3： 文件夹bin/advanced下  功能:同步获取方式得到机器人当前点的位置

mode4： 文件夹bin/advanced下  功能:同步获取方式得到机器人当前点的位置，并以关节插值的方式使驱动得最后一轴来回运动20度

类函数：ActuatorController

ActuatorController::processEvents();

处理控制器事件

class linkUnit：


/*
 * uint8_t id：执行器减速比
 * ActuatorType type_ :执行器型号 ，类型定义如下
     enum ActuatorType
    {
      QDD_LITE_PR60_36,
      QDD_LITE_NE30_36,
      QDD_LITE_EL20_36,
      QDD_PR60_36,
      QDD_NE30_36,
      QDD_EL20_36,
      QDD_PRO_NU80_100_110,
      QDD_PRO_PR60_80_90,
      QDD_PRO_NE30_50_70,
      ACTUATOR_FREE,
    };

 */
int InitActuator(uint8_t id,ActuatorType type_);

class Robot：

int InitRobot(LinkUnit *link_unit,int axis_num);

配置机器人

link_unit

机器人的关节单元

axis_num

关节个数

int GetRobotJointNum();

获取机器人关节个数

void ActivateCurrentMode();

设置机器人工作在电流模式下

void ActivatePositionMode();

设置机器人工作在位置模式下

void RequestCVPValue();

向机器人发送一次电流、速度和位置的刷新指令

void GetCurrentMachineJointFast(double angle[]);

获取机器人当前的关节角度（单位：弧度），此方式未向机器人发送位置刷新指令

void GetCurrentMachineJoint(double angle[]);

获取机器人当前的关节角度（单位：弧度），此方式会刷新一次位置再返回位置数据

//运动函数

int MoveJointPath(Robot *unit,double start_joint[],double target_joint[],AccDecDate *speed);

以关节插补的方式从起点运动到终点

unit：要驱动的机器人

start_joint：起点的关节角度数组，维数和机器人轴数一致

target_joint：终点的关节角度数组，维数和机器人轴数一致

speed：关节速度规划数组，维数和机器人轴数一致

return：0：正常 小于0则出现异常状况

class AccDecDate：

void SetParameter(double v,double a,double jerk);

设置运动插补速度参数

v 最大速度

a 最大加速度

jerk 最大加加速度

