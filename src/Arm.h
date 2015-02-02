/*
 * Arm.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_ARM_H_
#define ROBOT_CODE_2015_SRC_ARM_H_

#include <vector>
#include <string>
#include "util/Util.h"
#include "WPILib.h"
#include "ArmPIDSource.h"
#include "ArmHelpers.h"

class Arm {
public:
	typedef enum { kLeft, kRight, kInvalid } Side;
	typedef enum { kDown, kUp, kInvalidDir } Direction;

	Arm* GetInstance();
	void SetDirection(Direction newDirection);
	void SetPosition(float position);
	float GetPosition(Side side);
	void Up(int amount = 1);
	void Down(int amount = 1);
	void MoveToLevel(int level);

private:
	static Arm* instance;
	Preferences* pref;
	int positionState;
	int positionMax;
	int motorLeftID;
	int motorRightID;
	float lastPosition;
	Direction lastDirection = kInvalidDir;
	std::vector<float> levels;

	CANTalon* motorLeft;
	CANTalon* motorRight;
	PIDController* controllerRight;

	Arm();

};




#endif /* ROBOT_CODE_2015_SRC_ARM_H_ */
