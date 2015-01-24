/*
 * Input.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#include "Input.h"

Input::Input() : stick(0), type(kJoystick) {

}

float Input::GetX() {
	if (type == kJoystick) {
		return deadband(stick.GetX(), 0.1);
	} else if (type == kXbox) {
		return deadband(stick.GetX(Joystick::kLeftHand), 0.15) * (stick.GetRawButton(0) ? 0.5 : 1);
	}
	return 0;
}

float Input::GetY() {
	if (type == kJoystick) {
		return deadband(stick.GetY(), 0.1);
	} else if (type == kXbox) {
		return deadband(stick.GetY(Joystick::kLeftHand), 0.15) * (stick.GetRawButton(0) ? 0.5 : 1);
	}
	return 0;
}

float Input::GetRotation() {
	if (type == kJoystick) {
		return deadband(stick.GetZ(), 0.1);
	} else if (type == kXbox) {
		return deadband(stick.GetRawAxis(4), 0.15) * (stick.GetRawButton(0) ? 0.5 : 1);
	}
	return 0;
}

void Input::SetType(Input::JoystickType newType) {
	type = newType;
}
