/*
 * Arm.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs, Jeff
 */

#include "Arm.h"

Arm::Arm() {
	motorLeft = new CANTalon(motorLeftID);
	motorRight = new CANTalon(motorRightID);
	motorLeft->SetControlMode(CANTalon::kPosition);
	motorRight->SetControlMode(CANTalon::kFollower);
	motorRight->Set(motorLeftID);
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

void Arm::SetPosition(float position) {
	motorLeft->Set(position);
}
