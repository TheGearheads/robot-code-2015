/*
 * LEDs.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs
 */

#include "LEDs.h"

	LEDs::LEDs(uint32_t redChannel, uint32_t greenChannel, uint32_t blueChannel) : red(redChannel) , green(greenChannel) , blue(blueChannel) {	}

void LEDs::Set(float r, float g, float b) {
	red.Set(r);
	green.Set(g);
	blue.Set(b);
}
