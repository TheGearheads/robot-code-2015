/*
 * Drive.cpp

 *
 *  Created on: Jan 17, 2015
 *      Author: Gabs
 */

#include "Drive.h"

Drive::Drive() : robotDrive(frontLeftID, rearLeftID, frontRightID, rearRightID) {

		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

	void Drive::doDrive(float x, float y, float z) {

		robotDrive.MecanumDrive_Cartesian(x, y, z);

}



