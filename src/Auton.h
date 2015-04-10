/*
 * Auton.h
 *
 *  Created on: Feb 10, 2015
 *      Author: Gabs
 */

#ifndef SRC_AUTON_H_
#define SRC_AUTON_H_

#include "WPILib.h"
#include "Drive.h"
#include "Arm.h"
#include "Grabber.h"
#include "LEDStrip.h"

class Auton {
public:
	Auton();
	int GetMode();
	void Reset();
	void doAuton();
	static Auton* GetInstance();

private:
	Timer timer;
	int state;
	AnalogInput* rotary;
	static Auton* instance;

};



#endif /* SRC_AUTON_H_ */
