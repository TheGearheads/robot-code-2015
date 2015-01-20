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
	return stick.GetX();
}
float Input::GetY() {
	return stick.GetY();
}
float Input::GetRotation() {
	if (type == kJoystick) {
		return deadband(stick.GetZ(), 0.1);
	} else if (type == kXbox) {
		return deadband(stick.GetX(Joystick::kRightHand), 0.1);
	}
	return 0;
}

void Input::SetType(Input::JoystickType newType) {
	type = newType;
}
