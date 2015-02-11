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

	SpeedController* frontLeftMotor;
	SpeedController* rearLeftMotor;
	SpeedController* frontRightMotor;
	SpeedController* rearRightMotor;
	RobotDrive* robotDrive;
	static Drive* instance;

public:
	Drive();
	void doDrive(float x, float y, float z);
	static SpeedController* InitMotor(std::string key);
	static Drive* GetInstance();
};




#endif /* ROBOT_CODE_2015_SRC_DRIVE_H_ */
