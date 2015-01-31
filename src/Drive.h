/*
 * Drive.h
 *
 *  Created on: Jan 17, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_DRIVE_H_
#define ROBOT_CODE_2015_SRC_DRIVE_H_

#include "WPILib.h"

class Drive {

	int frontLeftID;
	int rearLeftID;
	int frontRightID;
	int rearRightID;

	CANTalon* frontLeftMotor;
	CANTalon* rearLeftMotor;
	CANTalon* frontRightMotor;
	CANTalon* rearRightMotor;
	RobotDrive* robotDrive;

public:
	Drive();
	void doDrive(float x, float y, float z);

};




#endif /* ROBOT_CODE_2015_SRC_DRIVE_H_ */
