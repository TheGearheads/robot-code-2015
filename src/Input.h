/*
 * Input.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_INPUT_H_
#define ROBOT_CODE_2015_SRC_INPUT_H_

#include "WPILib.h"
#include "Util.h"

class Input {

public:
	typedef enum {
		kXbox, kJoystick
	} JoystickType;

	Joystick stick;
	JoystickType type;
	Input();
	float GetX();
	float GetY();
	float GetRotation();
	void SetType(JoystickType newType);

};


#endif /* ROBOT_CODE_2015_SRC_INPUT_H_ */
