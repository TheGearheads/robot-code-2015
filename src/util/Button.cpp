
#include "Button.h"

namespace Util {

Button::Button(Mode mode /* = Button::kRaw */) : mode(mode) {}

/**
 * Update the value of the Button according to the mode
 * @param newValue The new value
 */
void Button::Update(bool newValue) {
	if (mode == Button::kRaw) {
		value = newValue;
	} else if (mode == Button::kPress) {
		if (!lastValue && newValue) { // If wasn't pressed but now is
			value = true; // Set to true (leading edge)
		}
	} else if (mode == Button::kRelease) {
		if (lastValue && !newValue) { // If was pressed but now isn't
			value = true; // Set to true (trailing edge)
		}
	} else if (mode == Button::kToggle) {
		if (!lastValue && newValue) { // If wasn't pressed  but now is
			value = !value; // Invert
		}
	}
	lastValue = newValue;
}

/**
 * Set Button's mode
 */
void Button::SetMode(Button::Mode newMode) {
	mode = newMode;
}

/**
 * Get if the button is currently pressed on not
 * @return Raw value of the Button
 */
bool Button::IsPressed() {
	return lastValue;
}

/**
 * Get the value of the button and reset if needed
 * @return Value of the Button
 */
bool Button::Get(bool reset /* = true */) {
	bool returnValue = value;
	if ((mode == Button::kPress || mode == Button::kRelease) && reset) {
		value = false; // Reset to false to show that we've read it
		lastValue = false;
	}
  // If in Toggle or Raw mode, just return the value

	return returnValue;
}

}
