#ifndef INTERFACE_H
#define INTERFACE_H

#include "execute.h"

/* Corresponding to the boot button */

/** @brief   interface
 *  @file    interface.h
 *  @author  yue
 *  @version 1.0.0
 *  @date    2019.11.18
 *  @note    注解. 例如: 本文件有什么具体功能啊, 使用时要注意什么啊..
 *  @since   自从...
 */

int Boot();

/* Corresponding to the mode0/Shutdown button */
void ShutDown();

/* Corresponding to the mode1/record button */
/* return 0:normal   <0: error */
int RecordContinuousPoint(string file_name);

/* Corresponding to the mode2/replay button */
/* return 0:normal   <0: error */
int ReplayTrajectory(string file_name);

/* Corresponding to the mode3/record button */
/* return 0:normal   <0: error */
int RecordSinglePoint();

/* Corresponding to the mode4/replay button */
/* return 0:normal   <0: error */
int ReplayPath();

/* set speed overide Ranges:0.1-1  , please set default=1*/
void SetReplayOverride(double value);

/* Corresponding to the stop button of the interface */
void SetStopFlag();

/* Corresponding to the mode4 OperationCycle button */
void SetOperationCycleMode(OperationCycleMode mode);

/* Corresponding to the mode3 record button */
void SetRecordFlag();

/* Real-time position */
void GetRealTimePos(double value[]);

/* Corresponding to the jog joint button */
/* axis=0-5  step (degree) */
/* return 0:normal   <0: error */
int JogInJointCoordinateSystem(int axis,double step);

/* Corresponding to the jog joint button */
/* axis=0-5  step (mm/degree) */
/* return 0:normal   <0: error */
int JogInCartesianCoordinateSystem(int axis,double step);

#endif
