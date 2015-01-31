/*
 * Arm.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_ARM_H_
#define ROBOT_CODE_2015_SRC_ARM_H_

#include "WPILib.h"
#include "Util.h"
#include "ArmPIDSource.h"

class Arm {
	typedef enum { kLeft, kRight, kInvalid } Side;
	typedef enum { kDown, kUp, kInvalidDir } Direction;

	int motorLeftID;
	int motorRightID;
	float lastPosition;
	Direction lastDirection = kInvalidDir;

	CANTalon* motorLeft;
	CANTalon* motorRight;
	PIDController* controller;

public:
	Arm();
	void SetDirection(Direction newDirection);
	void SetPosition(float position);
	float GetPosition(Side side);
};




#endif /* ROBOT_CODE_2015_SRC_ARM_H_ */
