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
	axisX = new Util::Axis("input." + profile + ".axis.x");
	axisY = new Util::Axis("input." + profile + ".axis.y");
	axisRot = new Util::Axis("input." + profile + ".axis.rot");
	speedMultiplier = pref->GetFloat("input.speedMultiplier");
	speedButton = new Util::Button("input." + profile + ".speedButton");
	upButton = new Util::Button("input." + profile + ".upButton");
	downButton = new Util::Button("input." + profile + ".downButton");
	grabberButton = new Util::Button("input." + profile + ".grabberButton");
}

float Input::GetX() {
	return axisX->Get() * (speedButton->Get() ? speedMultiplier : 1);
}

float Input::GetY() {
	return axisY->Get() * (speedButton->Get() ? speedMultiplier : 1);
}

float Input::GetRotation() {
	return axisRot->Get() * (speedButton->Get() ? speedMultiplier : 1);
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
