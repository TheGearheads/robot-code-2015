
#include "Button.h"

namespace Util {

std::vector<Button*> Button::buttons;
Task Button::task("ButtonChecker", (FUNCPTR)ButtonChecker);
std::atomic_flag Button::taskRunning = ATOMIC_FLAG_INIT;
std::mutex Button::buttonsMutex;

/**
 * Task to periodically check button input
 */
void Button::ButtonChecker() {
	while (taskRunning.test_and_set()) {
		Wait(0.02);
		buttonsMutex.lock();
		for (auto button : buttons) {
			button->Update();
		}
		buttonsMutex.unlock();
	}
}

/**
 *  Enable or disable the ButtonChecker task
 */
void Button::SetEnabled(bool enabled) { // Enable or disable the ButtonChecker task
	if (enabled) {
		if (!taskRunning.test_and_set()) { // Test if started, and if not, start it
			task.Start();
		}
	} else {
		taskRunning.clear();
		while (task.Verify()) { // Wait for task to end
			Wait(0.02);
		}
		task.Stop();
	}
}

/**
 * Add a Button to be checked by the ButtonChecker Task
 * @param buttonPtr Pointer to a Button
 */
void Button::AddButton(Button* buttonPtr) {
	SetEnabled(true);
	buttonsMutex.lock();
	buttons.push_back(buttonPtr); // Add new button
	buttonsMutex.unlock();
}

/**
 * Remove a Button to being checked by the ButtonChecker Task
 * @param buttonPtr Pointer to a Button
 */
void Button::DelButton(Button* buttonPtr) {
	buttonsMutex.lock();
	Button::buttons.erase(std::remove(Button::buttons.begin(), Button::buttons.end(), buttonPtr), Button::buttons.end());
	buttonsMutex.unlock();
}

/**
 * Search for a Button by key
 * @param key Configuration key to search by
 */
Button* Button::FindButton(std::string key) {
	for (auto button : buttons) {
		if (button->config == key) {
			return button;
		}
	}
	return nullptr;
}

/**
 * Simple constructor for a Button
 * @param buttonChannel The number for the button
 * @param mode The mode for the button (Default: kRaw)
 */
Button::Button(int buttonChannel, Mode mode /* = Button::kRaw */) : buttonChannel(buttonChannel), mode(mode) {
	stick = Joystick::GetStickForPort(0);
	Button::AddButton(this);
}

/**
 * Simple constructor for a Button
 * @param buttonChannel The number for the button
 * @param stick The Joystick the Button is on
 * @param mode The mode for the button (Default: kRaw)
 */
Button::Button(int buttonChannel, Joystick* stick, Mode mode /* = Button::kRaw */) : buttonChannel(buttonChannel), stick(stick), mode(mode) {
	Button::AddButton(this);
}

/**
 * Constructor for a Button to load from Preferences
 * <p><b>Button Preferences</b><br>
 * foo = channel. Either button number, axis number, or pov direction (int)<br>
 * foo.js = joystick (int)<br>
 * foo.mode = raw, press, release, toggle (string)<br>
 * foo.type = button, pov, axis (string)<br>
 * foo.threshold = axis threshold. If negative, value must be less than it. (valid only for axis) (float)<br>
 * foo.index = index of the pov (valid only for pov) (int)
 * </p>
 * @param buttonConfig The configuration key for the button
 */
Button::Button(std::string buttonConfig) {
	auto pref = Preferences::GetInstance();
	config = buttonConfig;

	if (!pref->ContainsKey(buttonConfig.c_str())) {
		DriverStation::ReportError("[Button] Attempting to load config '" + buttonConfig + "' and could not find it\n");
		type = kInvalid;
		return;
	} else {
		buttonChannel = pref->GetInt(buttonConfig.c_str());
		auto stickNum = pref->GetInt((buttonConfig + ".js").c_str(), 0); // Default to joystick 0
		stick = Joystick::GetStickForPort(stickNum);
		std::string modeStr = pref->GetString((buttonConfig + ".mode").c_str(), "raw");
		if (modeStr == "press") {
			SetMode(kPress);
		} else if (modeStr == "release") {
			SetMode(kRelease);
		} else if (modeStr == "toggle") {
			SetMode(kToggle);
		} else if (modeStr == "raw") {
			SetMode(kRaw);
		} else {
			DriverStation::ReportError("[Button] Attempting to load config '" + buttonConfig + "' and found an unknown mode '" + modeStr + "'. Defaulting to 'raw'\n");
			SetMode(kRaw);
		}

		std::string typeStr = pref->GetString((buttonConfig + ".type").c_str(), "button");
		if (typeStr == "button") {
			type = kButton;
		} else if (typeStr == "pov") {
			type = kPOV;
			povIndex = pref->GetInt((buttonConfig + ".pov.index").c_str(), 0);
		} else if (typeStr == "axis") {
			type = kAxis;
			threshold = pref->GetFloat((buttonConfig + ".threshold").c_str(), 0.95);
		} else if (typeStr == "virtual") {
			type = kVirtual;
			otherButton = Button::FindButton(pref->GetString(buttonConfig.c_str()));
		} else {
			DriverStation::ReportError("[Button] Attempting to load config '" + buttonConfig + "' and found an unknown type '" + typeStr + "'. Defaulting to 'raw'\n");
			type = kButton;
		}
		printf("[Button] Loaded config '%s', stick '%d', type '%s', mode '%s', channel '%d'\n", buttonConfig.c_str(), stickNum, typeStr.c_str(), modeStr.c_str(), buttonChannel);

		invert = pref->GetBoolean((buttonConfig + ".invert").c_str(), false);

	}
	Button::AddButton(this);
}

/**
 * Deconstructor for a Button
 */
Button::~Button() {
	Button::DelButton(this);
}

/**
 * Read value of the Button and update according to mode
 */
void Button::Update() {
	bool newValue;
	if (type == kButton) {
		//printf("Updating\n");
		if (buttonChannel > 0 && buttonChannel <= stick->GetButtonCount()) {
			newValue = stick->GetRawButton(buttonChannel);
		}
	} else if (type == kPOV) {
		// 8 direction POV, each position is 45° from eachother
		if (povIndex >= 0 && buttonChannel < stick->GetButtonCount()) {
			newValue = (45 * buttonChannel) == stick->GetPOV(povIndex);
		}
	} else if (type == kAxis) {
		float axisValue = 0;
		if (buttonChannel >= 0 && buttonChannel < stick->GetAxisCount()) {
			axisValue = stick->GetRawAxis(buttonChannel);
		}
		if (threshold < 0) {
			newValue = axisValue < threshold;
		} else if (threshold > 0) {
			newValue = axisValue > threshold;
		} else {
			newValue = false;
		}
	} else if (type == kVirtual && otherButton != nullptr) {
		newValue = otherButton->Get();
	} else {
		newValue = false;
	}

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
 * @param newMode The button mode to set
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
 * @param reset Resets value and last value to false (Default: true)
 * @return Value of the Button
 */
bool Button::Get(bool reset /* = true */) {
	bool returnValue = value;
	if ((mode == Button::kPress || mode == Button::kRelease) && reset) {
		value = false; // Reset to false to show that we've read it
		//lastValue = false;
	}
  // If in Toggle or Raw mode, just return the value

	return returnValue ^ invert;
}

}
