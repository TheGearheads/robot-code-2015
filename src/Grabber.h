/*
 * Grabber.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Gearheads
 */

#ifndef SRC_GRABBER_H_
#define SRC_GRABBER_H_
#include "WPILib.h"

/* Pointers allow us to delay the creation of the object
 * until after we load preferences.
 * grabberSolenoid will point to a DoubleSolenoid instance.
 */

class Grabber {
	DoubleSolenoid* grabberSolenoid;
	DoubleSolenoid* miniGrabberSolenoid;
	bool statusMain;
	bool statusMini;
	Compressor* compressor;
	static Grabber* instance;
	Grabber();

//Grabber(); is a special function, a constructor. It's called upon the creation of the class.

/* Static variables are shared among all the instances of that class.
 * If we were to have two Grabbers, the variable "instance" would be the same
 * in both. Setting one will set the other as well.
 */

public:
	enum GrabberType { kMain, kMini };
	static Grabber* GetInstance();
	bool Get(GrabberType type = kMain);
	void Open(GrabberType type = kMain);
	void Close(GrabberType type = kMain);

};

//enum is a special integer that is a type, not a function. the entire structure is an enumeration.
//kMain and kMini are 0 and 1, respectively. if 1 is passed to open/close, it would be the same as passing in kMini.
//each element within the brackets has a unique value, making it easier to write code.


#endif /* SRC_GRABBER_H_ */
