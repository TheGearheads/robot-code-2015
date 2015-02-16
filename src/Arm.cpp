/*
 * Arm.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs, Jeff
 */

#include "Arm.h"

Arm* Arm::instance = nullptr;

Arm::Arm() {
	pref = Preferences::GetInstance();
	motorLeftID = pref->GetInt("arm.left");
	motorRightID = pref->GetInt("arm.right");
	motorLeft = new CANTalon(motorLeftID);
	motorRight = new CANTalon(motorRightID);
	motorLeft->SetFeedbackDevice(CANTalon::AnalogPot);
	motorRight->SetFeedbackDevice(CANTalon::AnalogPot);
	controllerRight = new PIDController(0, 0, 0, this, motorRight);
	SetDirection(kUp);
	//SetMode(kPID);
	SetMode(kDirect);
	controllerRight->Enable();

	int i = 0;
	while (1) {
		std::string key = "arm.level." + std::to_string(i);
		if (!pref->ContainsKey(key.c_str())) {
			break;
		}
		levels.push_back(HeightToPot(pref->GetFloat(key.c_str())));
		i++;
	}

	positionMax = i - 1;
}

Arm* Arm::GetInstance() {
	if (instance == nullptr) {
			instance = new Arm();
	}
	return instance;
}

float Arm::GetPosition(Arm::Side side) {
	if (side == Arm::kLeft) {
		return 1023 - motorLeft->GetPosition();
		//return 1023 - motorLeft->GetAnalogInRaw();
	} else if (side == Arm::kRight) {
		return 1023 - motorRight->GetPosition() + pref->GetInt("arm.right.offset");
		//return 1023 - motorRight->GetAnalogInRaw() + pref->GetInt("arm.right.offset");
	}
	return 0;
}

void Arm::SetDirection(Arm::Direction newDirection) {
	if (newDirection == lastDirection) {
		return;
	}

	float leftP, leftI, leftD;
	float rightP, rightI, rightD;

	leftP = pref->GetFloat(newDirection == kUp ? "arm.left.up.p" : "arm.left.down.p");
	leftI = pref->GetFloat(newDirection == kUp ? "arm.left.up.i" : "arm.left.down.i");
	leftD = pref->GetFloat(newDirection == kUp ? "arm.left.up.d" : "arm.left.down.d");
	rightP = pref->GetFloat(newDirection == kUp ? "arm.right.up.p" : "arm.right.down.p");
	rightI = pref->GetFloat(newDirection == kUp ? "arm.right.up.i" : "arm.right.down.i");
	rightD = pref->GetFloat(newDirection == kUp ? "arm.right.up.d" : "arm.right.down.d");

	//motorLeft->SetPID(leftP, leftI, leftD);
	controllerRight->SetPID(rightP, rightI, rightD);
//	controllerRight->SetTolerance(pref->GetFloat("arm.tolerance"));
	SmartDashboard::PutNumber("Tolerance", pref->GetFloat("arm.tolerance"));
	lastDirection = newDirection;
}

void Arm::SetPosition(float position) {
	SetDirection(position > lastPosition ? kUp : kDown);
	//motorLeft->Set(position);
	lastPosition = position;
}

void Arm::Up(int amount /* = 1 */) {
	positionState = std::min(positionState + amount, positionMax);
}
void Arm::Down(int amount /* = 1 */) {
	positionState = std::max(positionState - amount, 0);
}
void Arm::MoveToLevel(int level) {
	SetPosition(levels[std::min(std::max(positionState, 0), positionMax)]);
}


void Arm::DirectDrive(float input) {
	motorLeft->Set(input);
	//motorRight->Set(input);
	SetDirection(input > 0 ? kUp : kDown);
	SmartDashboard::PutNumber("leftArmPosition", GetPosition(kLeft));
	SmartDashboard::PutNumber("rightArmPosition", GetPosition(kRight));
}

void Arm::SetMode(Arm::Mode newMode) {
	if (newMode == kDirect) {
		motorLeft->SetControlMode(CANTalon::kPercentVbus);
		controllerRight->Disable();
	} else {
		motorLeft->SetControlMode(CANTalon::kPosition);
		controllerRight->Enable();
	}
}

double Arm::PIDGet() {
	SmartDashboard::PutBoolean("Following", true);
	auto pref = Preferences::GetInstance();
	SmartDashboard::PutBoolean("Followed", abs(Deadband(GetPosition(kLeft) - GetPosition(kRight), pref->GetFloat("arm.deadband"))) < 0.1);
	SmartDashboard::PutNumber("RawDifference", GetPosition(kLeft) - GetPosition(kRight));
	SmartDashboard::PutNumber("Difference", Deadband(GetPosition(kLeft) - GetPosition(kRight), pref->GetFloat("arm.deadband")));
	SmartDashboard::PutNumber("Deadband", pref->GetFloat("arm.deadband"));
	return -Deadband(GetPosition(kLeft) - GetPosition(kRight), pref->GetFloat("arm.deadband"));
//	return GetPosition(kRight) - GetPosition(kLeft);
}
