/*
 * Drive.cpp

 *
 *  Created on: Jan 17, 2015
 *      Author: Gabs
 */

#include "Drive.h"

SpeedController* Drive::InitMotor(std::string key) {
	auto pref = Preferences::GetInstance();
	std::string type = pref->GetString((key + ".type").c_str(), "CAN");
	int id = pref->GetInt(key.c_str());
	if (type == "PWM") {
		return new Talon(id);
	} else {
		return new CANTalon(id);
	}
}

Drive* Drive::GetInstance() {
	if (instance == nullptr) {
			instance = new Drive();
	}
	return instance;
}

Drive::Drive() {
	auto pref = Preferences::GetInstance();

	frontLeftMotor = InitMotor("drive.frontLeft");
	rearLeftMotor = InitMotor("drive.rearLeft");
	frontRightMotor = InitMotor("drive.frontRight");
	rearRightMotor = InitMotor("drive.rearRight");
	robotDrive = new RobotDrive(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);

//	robotDrive->SetExpiration(pref->GetFloat("drive.expiration", 0.1));
	robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, pref->GetBoolean("drive.frontLeft.inverted", false));
	robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, pref->GetBoolean("drive.rearLeft.inverted", false));
	robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, pref->GetBoolean("drive.frontRight.inverted", true));
	robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, pref->GetBoolean("drive.rearRight.inverted", true));
}

	void Drive::doDrive(float x, float y, float z) {

		robotDrive->MecanumDrive_Cartesian(x, y, z);

}

Drive* Drive::instance = nullptr;



