/*
 * Arm.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs, Jeff
 */

#include "Arm.h"

Arm::Arm() {
	pref = Preferences::GetInstance();
	motorLeftID = pref->GetInt("arm.left.ID");
	motorRightID = pref->GetInt("arm.right.ID");
	motorLeft = new CANTalon(motorLeftID);
	motorRight = new CANTalon(motorRightID);
	motorLeft->SetControlMode(CANTalon::kPosition);
	controllerRight = new PIDController(0, 0, 0, new ArmPIDSource(motorLeft, motorRight), motorRight);
	SetDirection(kUp);

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
		return motorLeft->GetPosition();
	} else if (side == Arm::kRight) {
		return motorRight->GetPosition();
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

	motorLeft->SetPID(leftP, leftI, leftD);
	controllerRight->SetPID(rightP, rightI, rightD);
	lastDirection = newDirection;
}

void Arm::SetPosition(float position) {
	SetDirection(position > lastPosition ? kUp : kDown);
	motorLeft->Set(position);
	lastPosition = position;
}

void Arm::Up(int amount /* = 1 */) {
	positionState = std::min(positionState + amount, positionMax);
}
void Arm::Down(int amount /* = 1 */) {
	positionState = std::min(positionState - amount, 0);
}
void Arm::MoveToLevel(int level) {
	SetPosition(levels[std::min(std::max(positionState, 0), positionMax)]);
}

Arm* Arm::instance = nullptr;
