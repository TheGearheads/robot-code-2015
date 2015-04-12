/*
 * LEDs.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs
 */

#ifndef SRC_LEDS_H_
#define SRC_LEDS_H_

#include <atomic>
#include "LEDStrip.h"
#include "Auton.h"
#include "Grabber.h"
#include "util/Util.h"

class LEDs {
	public:
		static void SetEnabled(bool enabled);
		static LEDs* GetInstance();
		LEDs();

	private:
		static Task task;
		static std::atomic_flag taskRunning;
		static void LEDRunner();
		static LEDs* instance;

};


#endif /* SRC_LEDS_H_ */
