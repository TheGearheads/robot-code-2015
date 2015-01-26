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
	LED(uint32_t channel);
	void Set(float value);

};




#endif /* SRC_LED_H_ */
