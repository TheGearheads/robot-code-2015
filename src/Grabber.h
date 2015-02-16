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
	int grabberOpenChannel;
	int grabberCloseChannel;
	DoubleSolenoid* grabberSolenoid;
	Compressor* compressor;
	static Grabber* instance;
	Grabber();

public:
	static Grabber* GetInstance();
	void Open();
	void Close();

};



#endif /* SRC_GRABBER_H_ */
