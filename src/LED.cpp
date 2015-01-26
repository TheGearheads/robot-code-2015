/*
 * LED.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs
 */

#include "LED.h"


LED::LED(uint32_t channel) : PWM(channel) {
	SetPeriodMultiplier(PWM::kPeriodMultiplier_1X);

}

	void LED::Set(float value) {
		SetRaw((int)(value * 32767));
	}
