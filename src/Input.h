/*
 * Input.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_INPUT_H_
#define ROBOT_CODE_2015_SRC_INPUT_H_

#include <util/Util.h>
#include "WPILib.h"

class Input {

int axisX;
int axisY;
int axisRot;

float deadbandX;
float deadbandY;
float deadbandRot;

float speedMultiplier;
Util::Button speedButton;

public:


	Joystick stick;
	Input();
	float GetX();
	float GetY();
	float GetRotation();

};


#endif /* ROBOT_CODE_2015_SRC_INPUT_H_ */
