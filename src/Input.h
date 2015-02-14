/*
 * Input.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_INPUT_H_
#define ROBOT_CODE_2015_SRC_INPUT_H_

#include "util/Util.h"
#include "WPILib.h"
#include "Arm.h"
#include "Grabber.h"

class Input {

Util::Axis* axisX;
Util::Axis* axisY;
Util::Axis* axisRot;


float speedMultiplier;
Util::Button* speedButton;
Util::Button* upButton;
Util::Button* downButton;
Util::Button* grabberButton;

public:

	Joystick stick;
	Input();
	float GetX();
	float GetY();
	float GetRotation();
	void GetArmInput();
	void GetGrabberInput();

};


#endif /* ROBOT_CODE_2015_SRC_INPUT_H_ */
