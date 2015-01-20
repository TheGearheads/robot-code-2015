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

	const static int motorAID = 34;	//Motor a ID
	const static int motorBID = 35;	//Motor b ID
	const static int potentiometerChannel = 0;
	const static short potentiometerMin = 0;
	const static short potentiometerMax = 4095;

	CANTalon* motors[2];

public:
	Arm();
	void SetPosition(float position);
	void Move(float speed);
	float GetPosition();
};




#endif /* ROBOT_CODE_2015_SRC_ARM_H_ */
