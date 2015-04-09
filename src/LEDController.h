/*
 * LEDController.h
 */

#ifndef SRC_LEDCONTROLLER_H_
#define SRC_LEDCONTROLLER_H_

#include <vector>
#include "WPILib.h"
#include "util/Color.h"

class LEDController {
	public:
		void SetBrightness(uint8_t newBrightness);
		uint8_t GetBrightness();
		void Set(int idx, Util::Color led, bool show = false);
		void Set(int idx, std::vector<Util::Color> values, bool show = false);
		Util::Color Get(int idx);
		void Clear();
		void Show();
		void Refresh();
		void Write(uint8_t* buf, int length);
		static LEDController* GetInstance();
	private:
		LEDController();
		uint8_t brightness;
		std::vector<Util::Color> leds;
		std::string preferance;
		I2C* controller;
		static LEDController* instance;
};

#endif /* SRC_LEDCONTROLLER_H_ */
