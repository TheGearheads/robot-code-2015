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

	const static int frontLeftID = 30;
	const static int rearLeftID = 31;
	const static int frontRightID = 32;
	const static int rearRightID = 33;

	RobotDrive robotDrive;
	CANTalon frontLeftMotor;
	CANTalon rearLeftMotor;
	CANTalon frontRightMotor;
	CANTalon rearRightMotor;

public:
	Drive();
	void doDrive(float x, float y, float z);

};




#endif /* ROBOT_CODE_2015_SRC_DRIVE_H_ */
