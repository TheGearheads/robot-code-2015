/*
 * Arm.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs, Jeff
 */

#include "Arm.h"

Arm::Arm() {
	motors[0] = new CANTalon(motorAID);
	motors[1] = new CANTalon(motorBID);
	motors[0]->SetControlMode(CANTalon::kPosition);
	motors[1]->SetControlMode(CANTalon::kFollower);
	motors[1]->Set(motorAID);
}


float Arm::GetPosition() {
	// return interpolate(position.GetValue(), potentiometerMin, potentiometerMax, 0.0, 1.0);
	return 0;
}

void Arm::SetPosition(float position) {
	motors[0]->Set(position);
}
