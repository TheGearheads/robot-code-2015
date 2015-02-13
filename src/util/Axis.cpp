#include "Axis.h"

namespace Util {

std::vector<Axis*> Axis::axes;
Task Axis::task("AxisChecker", (FUNCPTR)AxisChecker);
bool Axis::taskRunning = false;

/**
 * Task to periodically check axis input
 */
void Axis::AxisChecker() {
	taskRunning = true;
	while (taskRunning) {
		DriverStation::GetInstance()->WaitForData(); // Wait for an update from the DriverStation
		for (auto axis : axes) {
			axis->Update();
		}
	}
}

/**
 *  Enable or disable the AxisChecker task
 */
void Axis::SetEnabled(bool enabled) { // Enable or disable the AxisChecker task
	if (enabled == taskRunning) {
		return;
	}
	if (enabled) {
		task.Start();
	} else {
		taskRunning = false;
		while (task.Verify()) { // Wait for task to end
			Wait(0.02);
		}
		task.Stop();
	}
}

/**
 * Add a Axis to be checked by the AxisChecker Task
 * @param axisPtr Pointer to a Axis
 */
void Axis::AddAxis(Axis* axisPtr) {
	SetEnabled(false);
	axes.push_back(axisPtr); // Add new axis
	SetEnabled(true);
}

/**
 * Remove a Axis to being checked by the AxisChecker Task
 * @param axisPtr Pointer to a Axis
 */
void Axis::DelAxis(Axis* axisPtr) {
	SetEnabled(false);
	Axis::axes.erase(std::remove(Axis::axes.begin(), Axis::axes.end(), axisPtr), Axis::axes.end());
	SetEnabled(true);
}

/**
 * Search for a Axis by key
 * @param key Configuration key to search by
 */
Axis* Axis::FindAxis(std::string key) {
	for (auto axis : axes) {
		if (axis->config == key) {
			return axis;
		}
	}
	return nullptr;
}

/**
 * Simple constructor for a Axis
 * @param axisChannel The number for the axis
 * @param mode The mode for the axis (Default: kRaw)
 */
Axis::Axis(int axisChannel, Mode mode /* = Axis::kRaw */) : axisChannel(axisChannel), mode(mode) {
	stick = Joystick::GetStickForPort(0);
	Axis::AddAxis(this);
}

/**
 * Simple constructor for a Axis
 * @param axisChannel The number for the axis
 * @param stick The Joystick the Axis is on
 * @param mode The mode for the axis (Default: kRaw)
 */
Axis::Axis(int axisChannel, Joystick* stick, Mode mode /* = Axis::kRaw */) : axisChannel(axisChannel), stick(stick), mode(mode) {
	Axis::AddAxis(this);
}

/**
 * Constructor for a Axis to load from Preferences
 * <p><b>Axis Preferences</b><br>
 * foo = channel. Either axis number, axis number, or pov direction (int)<br>
 * foo.js = joystick (int)<br>
 * foo.mode = raw, press, release, toggle (string)<br>
 * foo.type = axis, pov, axis (string)<br>
 * foo.threshold = axis threshold. If negative, value must be less than it. (valid only for axis) (float)<br>
 * foo.index = index of the pov (valid only for pov) (int)
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
	Axis::AddAxis(this);
}

/**
 * Deconstructor for a Axis
 */
Axis::~Axis() {
	Axis::DelAxis(this);
}

void SetDeadband(float newDeadband) {
	deadband = newDeadband;
}

float GetDeadband() {
	return deadband;
}

/**
 * Get the value of the axis, applying invert and deadband
 * @return Value of the Axis
 */
bool Axis::Get() {
	return (invert ? -1 : 1) * deadband(stick->GetRawAxis(axisChannel), deadband);
}

