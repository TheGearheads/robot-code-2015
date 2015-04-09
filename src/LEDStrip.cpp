#include "LEDStrip.h"

LEDStrip::LEDStrip(int idx, int count) : start_idx(idx), count(count) { }

void LEDStrip::Set(int idx, Util::Color led, bool show /*= false*/) {
	LEDController::GetInstance()->Set(start_idx + idx, led, show);
}

void LEDStrip::Set(int idx, std::vector<Util::Color> values, bool show /*= false*/) {
	LEDController::GetInstance()->Set(start_idx + idx, values, show);
}

Util::Color LEDStrip::Get(int idx) {
	return LEDController::GetInstance()->Get(start_idx + idx);
}

void LEDStrip::Clear() {
	std::vector<Util::Color> tmp;
	tmp.resize(count);
	Set(start_idx, tmp, true);
}

void LEDStrip::Show() {
	LEDController::GetInstance()->Show();
}

