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

class Auton {
public:
	Auton();
	void Reset();
	void doAuton();


private:
	Timer timer;
	int state;

};



#endif /* SRC_AUTON_H_ */
