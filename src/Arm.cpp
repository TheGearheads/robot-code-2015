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
	//controllerRight = new PIDController(0, 0, 0, this, motorRight);
	SetDirection(kUp);
	//SetMode(kPID);
	SetMode(kDirect);
	//controllerRight->Enable();
	misaligned = false;

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
	if (newDirection == direction) {
		return;
	}
	SmartDashboard::PutString("ArmDirection", newDirection == kUp ? "Up" : "Down");

	//float p, i, d;

	//p = pref->GetFloat(newDirection == kUp ? "arm.up.p" : "arm.down.p");
	//i = pref->GetFloat(newDirection == kUp ? "arm.up.i" : "arm.down.i");
	//d = pref->GetFloat(newDirection == kUp ? "arm.up.d" : "arm.down.d");

	//motorLeft->SetPID(leftP, leftI, leftD);
	//controllerRight->SetPID(rightP, rightI, rightD);
//	controllerRight->SetTolerance(pref->GetFloat("arm.tolerance"));
	direction = newDirection;
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
	float leftInput = input;
	float rightInput = input;

	SetDirection(input > 0 ? kUp : kDown);

	int leftPos = GetPosition(kLeft);
	int rightPos = GetPosition(kRight);
	int diff = abs(rightPos - leftPos);
	int tolerance = pref->GetInt("arm.tolerance");
	int hysteresis = pref->GetInt("arm.hysteresis");


	SmartDashboard::PutNumber("leftArmPosition", leftPos);
	SmartDashboard::PutNumber("rightArmPosition", rightPos);
	SmartDashboard::PutNumber("Tolerance", tolerance);
	SmartDashboard::PutNumber("Difference", diff);
	SmartDashboard::PutNumber("Hysteresis", hysteresis);

	if (diff > tolerance || (diff > hysteresis && misaligned)) {
		misaligned = true;
		if (direction == kUp) {
			if (rightPos > leftPos) {
				rightInput = 0;
			} else {
				leftInput = 0;
			}
		} else if (direction == kDown) {
			if (rightPos < leftPos) {
				rightInput = 0;
			} else {
				leftInput = 0;
			}
		}
	} else {
		misaligned = false;
	}

	int minPot = pref->GetInt("arm.pot.min");
	int maxPot = pref->GetInt("arm.pot.max");
	int range = pref->GetInt("arm.range");
	int speedLimit = pref->GetInt("arm.speedLimit");

	bool inRange = std::max(leftPos, rightPos) > (maxPot - range);
	inRange |= std::min(leftPos, rightPos) < (minPot + range);
	leftInput = (inRange && std::abs(leftInput) > speedLimit) ? (std::signbit(leftInput) ? -1 : 1) * speedLimit : leftInput;
	rightInput = (inRange && std::abs(rightInput) > speedLimit) ? (std::signbit(rightInput) ? -1 : 1) * speedLimit : rightInput;

	motorLeft->Set(leftInput);
	motorRight->Set(rightInput);
}

void Arm::SetMode(Arm::Mode newMode) {
	if (newMode == kDirect) {
		motorLeft->SetControlMode(CANTalon::kPercentVbus);
		//controllerRight->Disable();
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
	SmartDashboard::PutNumber("Deadband", pref->GetFloat("arm.deadband"));
	return -Deadband(GetPosition(kLeft) - GetPosition(kRight), pref->GetFloat("arm.deadband"));
//	return GetPosition(kRight) - GetPosition(kLeft);
}
