/*
 * LEDs.cpp
 */

#include "LEDs.h"

Task LEDs::task("LEDRunner", (FUNCPTR)LEDRunner);
std::atomic_flag LEDs::taskRunning = ATOMIC_FLAG_INIT;

/**
 * Task to handle the display of LEDs
 */
void LEDs::LEDRunner() {
	// This is kind of ugly :(
	auto ds = DriverStation::GetInstance();
	int mode = 0;
	//float hueOutput = 0;
	auto leds = LEDController::GetInstance();
	leds->SetBrightness(30);
	LEDStrip frontLeft(0, 8);
	LEDStrip rearLeft(8, 16);
	LEDStrip rearRight(24, 16);
	LEDStrip frontRight(40, 8);
	std::vector<Util::Color> tmp;
	while (taskRunning.test_and_set()) {
		Wait(0.2);
		if (ds->IsDisabled()) {
			tmp.clear(); tmp.resize(16, 0xffff00);
			if (!ds->IsDSAttached()) {
				// Not attached to the DS, so, alternate yellow/off
				for (int i = 0; i < 8; i++) {
					tmp[i * 2] = 0x000000;
				}
			}
			rearLeft.Set(tmp);
			rearRight.Set(tmp);
			tmp.resize(8);
			frontRight.Set(tmp);
			frontLeft.Set(tmp);
			mode = Auton::GetInstance()->GetMode();
			tmp.clear();
			tmp.resize(3);
			tmp[0] = mode & 1 ? 0xffff00 : 0x00;
			tmp[1] = mode & 2 ? 0xffff00 : 0x00;
			tmp[2] = mode & 4 ? 0xffff00 : 0x00;
			rearRight.Set(tmp, 0);

			tmp.clear(); tmp.resize(6);
			tmp[0] = ds->IsDSAttached() ? 0x00ff00 : 0x00;
			tmp[1] = ds->IsFMSAttached() ? 0x00ff00 : 0x00;
			float hueOutput = Interpolate(ds->GetBatteryVoltage(), 12.0f, 13.0f, 0.0f, 120.0f);
			//hueOutput = ((int)hueOutput + 5) % 360;
			//float hueOutput
			//printf("Voltage: %f (%f) ", ds->GetBatteryVoltage(), hueOutput);
			tmp[2] = Util::Color(hueOutput, 1.0, 0.75);
			//Util::RGB c = tmp[2];
			//printf("(%d, %d, %d)\n", c.r, c.g, c.b);

			auto position = ds->GetLocation();
			auto alliance = ds->GetAlliance();
			Util::Color allianceColor = alliance == DriverStation::kRed ? 0xff0000 : (alliance == DriverStation::kBlue ? 0x0000ff : 0xffff00);
			if (position) {
				tmp[2 + position] = allianceColor;
			//} else {
				//position += 1;
				//tmp[2 + position] = allianceColor;
				//tmp[2 + position + 1] = allianceColor;
				//tmp[2 + position + 2] = allianceColor;
			}
			rearRight.Set(tmp, 3);
			rearRight.Show();
		} else {
			if (ds->IsAutonomous()) {
				auto alliance = ds->GetAlliance();
				Util::Color allianceColor = alliance == DriverStation::kRed ? 0xff0000 : (alliance == DriverStation::kBlue ? 0x0000ff : 0xffff00);
				tmp.clear();
				tmp.resize(16, allianceColor);
				rearLeft.Set(tmp);
				rearRight.Set(tmp);
				tmp.resize(8);
				frontLeft.Set(tmp);
				frontRight.Set(tmp);
			} else if (ds->IsOperatorControl()) {
				double timeLeft = ds->GetMatchTime();
				tmp.clear();
				tmp.resize(16, 0xffff00);
				if (timeLeft < 0 || timeLeft > 30) {
					// All yellow
				} else if (timeLeft > 20) {
					for (int i = 0; i < 8; i++) {
						tmp[i * 2] = 0x00ff00;
					}
				} else if (timeLeft > 5) {
					// off and green->red
					float hueOutput = Interpolate((float)timeLeft, 5.0f, 20.f, 0.0f, 120.0f);
					for (int i = 0; i < 8; i++) {
						tmp[i * 2 + 1] = 0x00;
						tmp[i * 2] = Util::Color(hueOutput, 1.0, 0.75);
						//tmp[i * 2] = 0x00ff00;
					}
				} else {
					// Just red
					tmp.clear();
					tmp.resize(16, 0xff0000);
				}
				if (Grabber::GetInstance()->Get(Grabber::kMini)) {
					tmp[0] = 0xff00ff;
					tmp[15] = 0xff00ff;
				}
				if (!Grabber::GetInstance()->Get(Grabber::kMain)) {
					tmp[1] = 0x00ffff;
					tmp[14] = 0x00ffff;
				}
				rearLeft.Set(tmp);
				rearRight.Set(tmp);
				tmp.resize(8);
				if (Grabber::GetInstance()->Get(Grabber::kMini)) {
					tmp[7] = 0xff00ff;
				}
				if (!Grabber::GetInstance()->Get(Grabber::kMain)) {
					tmp[6] = 0x00ffff;
				}
				frontLeft.Set(tmp);
				frontRight.Set(tmp);

				//printf("Match Time: %f\n", ds->GetMatchTime());

			}
		}
		frontLeft.Show();
		rearLeft.Show();
		frontRight.Show();
		rearRight.Show();
	}
}

/**
 *  Enable or disable the LEDRunner task
 */
void LEDs::SetEnabled(bool enabled) {
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

LEDs* LEDs::GetInstance() {
	if (instance == nullptr) {
			instance = new LEDs();
	}
	return instance;
}

LEDs::LEDs() {
	SetEnabled(true);
}

LEDs* LEDs::instance = nullptr;

