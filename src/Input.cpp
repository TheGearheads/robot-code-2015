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
	speedButton = new Util::Button("input." + profile + ".speedButton");
	upButton = new Util::Button("input." + profile + ".upButton");
	downButton = new Util::Button("input." + profile + ".downButton");
	grabberButton = new Util::Button("input." + profile + ".grabberButton");
}

float Input::GetX() {
	return deadband(stick.GetRawAxis(axisX), deadbandX) * (speedButton->Get() ? speedMultiplier : 1);
}

float Input::GetY() {
	return deadband(stick.GetRawAxis(axisY), deadbandY) * (speedButton->Get() ? speedMultiplier : 1);
}

float Input::GetRotation() {
	return deadband(stick.GetRawAxis(axisRot), deadbandRot) * (speedButton->Get() ? speedMultiplier : 1);
}


void Input::GetArmInput() {
	if (upButton->Get()) {
		Arm::GetInstance()->Up();
	} else if (downButton->Get()) {
		Arm::GetInstance()->Down();
	}
}

void Input::GetGrabberInput() {
	if (grabberButton->Get()) {
		Grabber::GetInstance()->Open();
	} else {
		Grabber::GetInstance()->Close();
	}
}
