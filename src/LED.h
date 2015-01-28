/*
 * LED.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#include "WPILib.h"

class LED : public PWM {

	public:

	// Means there's no implicit conversion from uint32_t
	// to our LED class. Shouldn't matter, but this forces things
	// to be cleaner.
	explicit LED(uint32_t channel);
	void Set(float value);

};




#endif /* SRC_LED_H_ */
