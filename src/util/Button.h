
namespace Util {

class Button {

	public:
		enum Mode {
			kRaw, kPress, kRelease, kToggle
		};
		Button(int buttonChannel, Joystick stick, Mode mode = kRaw);
		void Update();
		void SetMode(Mode newMode);
		bool IsPressed();
		bool Get(bool reset = true);
	private:
		bool value = false;
		bool lastValue = false;
		Mode mode = kRaw;
		int buttonChannel;
		Joystick stick;


};

}
