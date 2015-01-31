/*
 * Input.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#include "Input.h"

Input::Input() : stick(0) {
	auto pref = Preferences::GetInstance();
	std::string profile = pref->GetString("input.profile");
	axisX = pref->GetInt(("input." + profile + ".axis.x").c_str());
	axisY = pref->GetInt(("input." + profile + ".axis.y").c_str());
	axisRot = pref->GetInt(("input." + profile + ".axis.rot").c_str());
	deadbandX = pref->GetFloat(("input." + profile + ".axis.x.deadband").c_str());
	deadbandY = pref->GetFloat(("input." + profile + ".axis.y.deadband").c_str());
	deadbandRot = pref->GetFloat(("input." + profile + ".axis.rot.deadband").c_str());
	speedMultiplier = pref->GetFloat("input.speedMultiplier");
	speedButton = pref->GetInt(("input." + profile + ".speedButton").c_str());
}

float Input::GetX() {
	return deadband(stick.GetRawAxis(axisX), deadbandX) * (stick.GetRawButton(speedButton) ? speedMultiplier : 1);
}

float Input::GetY() {
	return deadband(stick.GetRawAxis(axisY), deadbandY) * (stick.GetRawButton(speedButton) ? speedMultiplier : 1);
}

float Input::GetRotation() {
	return deadband(stick.GetRawAxis(axisRot), deadbandRot) * (stick.GetRawButton(speedButton) ? speedMultiplier : 1);
}

