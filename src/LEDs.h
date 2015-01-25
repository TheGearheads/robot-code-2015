/*
 * LEDs.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs
 */

#ifndef SRC_LEDS_H_
#define SRC_LEDS_H_
#include "LED.h"

class LEDs {
	LED red;
	LED green;
	LED blue;

public:
	LEDs(uint32_t redChannel, uint32_t greenChannel, uint32_t blueChannel);

void Set(float r, float g, float b);

};


#endif /* SRC_LEDS_H_ */
