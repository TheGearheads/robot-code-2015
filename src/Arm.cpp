/*
 * Arm.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs, Jeff
 */

#include "Arm.h"

Arm::Arm() {
	auto pref = Preferences::GetInstance();
	motorLeftID = pref->GetInt("arm.left.ID");
	motorRightID = pref->GetInt("arm.right.ID");
	motorLeft = new CANTalon(motorLeftID);
	motorRight = new CANTalon(motorRightID);
	motorLeft->SetControlMode(CANTalon::kPosition);
	motorRight->Set(motorLeftID);
	controller = new PIDController(0, 0, 0, new ArmPIDSource(motorLeft, motorRight), motorRight);
	SetDirection(kUp);
}


float Arm::GetPosition(Arm::Side side) {
	// return interpolate(position.GetValue(), potentiometerMin, potentiometerMax, 0.0, 1.0);
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

	auto pref = Preferences::GetInstance();

	leftP = pref->GetFloat(newDirection == kUp ? "arm.left.up.p" : "arm.left.down.p");
	leftI = pref->GetFloat(newDirection == kUp ? "arm.left.up.i" : "arm.left.down.i");
	leftD = pref->GetFloat(newDirection == kUp ? "arm.left.up.d" : "arm.left.down.d");
	rightP = pref->GetFloat(newDirection == kUp ? "arm.right.up.p" : "arm.right.down.p");
	rightI = pref->GetFloat(newDirection == kUp ? "arm.right.up.i" : "arm.right.down.i");
	rightD = pref->GetFloat(newDirection == kUp ? "arm.right.up.d" : "arm.right.down.d");

	motorLeft->SetPID(leftP, leftI, leftD);
	controller->SetPID(rightP, rightI, rightD);
	lastDirection = newDirection;
}

void Arm::SetPosition(float position) {
	SetDirection(position > lastPosition ? kUp : kDown);
	motorLeft->Set(position);
	lastPosition = position;
}
