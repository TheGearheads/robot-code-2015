/*
 * Drive.cpp

 *
 *  Created on: Jan 17, 2015
 *      Author: Gabs
 */

#include "Drive.h"

Drive::Drive() {
	auto pref = Preferences::GetInstance();
	frontLeftID = pref->GetInt("drive.frontLeft.ID");
	rearLeftID = pref->GetInt("drive.rearLeft.ID");
	frontRightID = pref->GetInt("drive.frontRight.ID");
	rearRightID = pref->GetInt("drive.rearRight.ID");

	frontLeftMotor = new CANTalon(frontLeftID);
	rearLeftMotor = new CANTalon(rearLeftID);
	frontRightMotor = new CANTalon(frontRightID);
	rearRightMotor = new CANTalon(rearRightID);
	robotDrive = new RobotDrive(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);

	robotDrive.SetExpiration(pref->GetFloat("drive.expiration", 0.1));
	robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, pref->GetBoolean("drive.frontLeft.inverted", false));
	robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, pref->GetBoolean("drive.rearLeft.inverted", false));
	robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, pref->GetBoolean("drive.frontRight.inverted", true));
	robotDrive.SetInvertedMotor(RobotDrive::kRearRightMotor, pref->GetBoolean("drive.rearRight.inverted", true));
}

	void Drive::doDrive(float x, float y, float z) {

		robotDrive.MecanumDrive_Cartesian(x, y, z);

}




