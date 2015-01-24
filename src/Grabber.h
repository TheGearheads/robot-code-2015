/*
 * Grabber.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Gearheads
 */

#ifndef SRC_GRABBER_H_
#define SRC_GRABBER_H_
#include "WPILib.h"

class Grabber {
	const static int grabberOpenChannel = 0;
	const static int grabberCloseChannel = 1;
	DoubleSolenoid grabberSolenoid;

public:
	Grabber();
	void Open();
	void Close();

};



#endif /* SRC_GRABBER_H_ */
