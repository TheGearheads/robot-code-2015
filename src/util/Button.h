/*
 * Button.h
 */

#ifndef SRC_UTIL_BUTTON_H_
#define SRC_UTIL_BUTTON_H_

#include <vector>
#include "WPILib.h"

namespace Util {

class Button {
	public:
		enum Mode {
			kRaw, kPress, kRelease, kToggle
		};
		Button(int buttonChannel, Mode mode = kRaw);
		Button(int buttonChannel, Joystick* stick, Mode mode = kRaw);
		Button(std::string buttonConfig);
		~Button();
		void Update();
		void SetMode(Mode newMode);
		bool IsPressed();
		bool Get(bool reset = true);
	private:
		enum ChannelType {
			kButton, kPOV, kAxis, kInvalid
		};
		bool value = false;
		bool lastValue = false;
		ChannelType type = kButton;
		float threshold;
		int povIndex;
		int buttonChannel;
		Joystick* stick;
		Mode mode = kRaw;

		static std::vector<Button*> buttons;
		static Task task;
		static bool taskRunning;

		static void ButtonChecker();
		static void SetEnabled(bool enabled);
		static void AddButton(Button* buttonPtr);
		static void DelButton(Button* buttonPtr);


};

}

#endif /* SRC_UTIL_BUTTON_H_ */
