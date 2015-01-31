
namespace Util {

class Button {
	bool value = false;
	bool lastValue = false;

	public:
		enum Mode {
			kRaw, kPress, kRelease, kToggle
		};
		Button(Mode mode = kRaw);
		void Update(bool newvalue);
		void SetMode(Mode newMode);
		bool IsPressed();
		bool Get(bool reset = true);
	private:
		Mode mode = kRaw;

};

}
