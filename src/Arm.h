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

class Arm {

	const static int motorLeftID = 34;	//Motor a ID
	const static int motorRightID = 35;	//Motor b ID
	typedef enum { kLeft, kRight, kInvalid } Side;

	CANTalon* motorLeft;
	CANTalon* motorRight;

public:
	Arm();
	void SetPosition(float position);
	void Move(float speed);
	float GetPosition(Arm::Side side);
};




#endif /* ROBOT_CODE_2015_SRC_ARM_H_ */
