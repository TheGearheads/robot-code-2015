#include "Axis.h"

namespace Util {

/**
 * Simple constructor for a Axis
 * @param axisChannel The number for the axis
 */
Axis::Axis(int axisChannel) : axisChannel(axisChannel) {
	stick = Joystick::GetStickForPort(0);
}

/**
 * Simple constructor for a Axis
 * @param axisChannel The number for the axis
 * @param stick The Joystick the Axis is on
 */
Axis::Axis(int axisChannel, Joystick* stick) : axisChannel(axisChannel), stick(stick) {
}

/**
 * Constructor for a Axis to load from Preferences
 * <p><b>Axis Preferences</b><br>
 * foo = channel. Either axis number, axis number, or pov direction (int)<br>
 * foo.js = joystick (int)<br>
 * </p>
 * @param axisConfig The configuration key for the axis
 */
Axis::Axis(std::string axisConfig) {
	auto pref = Preferences::GetInstance();
	config = axisConfig;

	if (!pref->ContainsKey(axisConfig.c_str())) {
		DriverStation::ReportError("[Axis] Attempting to load config '" + axisConfig + "' and could not find it");
		return;
	} else {
		axisChannel = pref->GetInt(axisConfig.c_str());
		auto stickNum = pref->GetInt((axisConfig + ".js").c_str(), 0); // Default to joystick 0
		stick = Joystick::GetStickForPort(stickNum);

		invert = pref->GetBoolean((axisConfig + ".invert").c_str(), false);
		deadband = pref->GetFloat((axisConfig + ".deadband").c_str());

	}
}

/**
 * Deconstructor for a Axis
 */
Axis::~Axis() {
}

void Axis::SetDeadband(float newDeadband) {
	deadband = newDeadband;
}

float Axis::GetDeadband() {
	return deadband;
}

/**
 * Get the value of the axis, applying invert and deadband
 * @return Value of the Axis
 */
float Axis::Get() {
	return (invert ? -1 : 1) * Deadband(stick->GetRawAxis(axisChannel), deadband);
}

}
