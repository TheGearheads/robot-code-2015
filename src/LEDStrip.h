/*
 * LEDStrip.h
 */

#ifndef SRC_LEDSTRIP_H_
#define SRC_LEDSTRIP_H_

#include <vector>
#include "WPILib.h"
#include "util/Color.h"
#include "LEDController.h"

class LEDStrip {
	public:
		LEDStrip(int idx, int count);
		void Set(int idx, Util::Color led, bool show = false);
		void Set(int idx, std::vector<Util::Color> values, bool show = false);
		Util::Color Get(int idx);
		void Clear();
		void Show();
	private:
		uint8_t start_idx;
		uint8_t count;
};

#endif /* SRC_LEDSTRIP_H_ */
