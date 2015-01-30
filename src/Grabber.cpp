/*
 * Grabber.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gearheads
 */
#include "Grabber.h"

Grabber::Grabber() {
	auto pref = Preferences::GetInstance();
	grabberCloseChannel = pref->GetInt("grabber.closeChannel");
	grabberOpenChannel = pref->GetInt("grabber.openChannel");
	grabberSolenoid = new DoubleSolenoid(grabberOpenChannel, grabberCloseChannel);
}

void Grabber::Open() {
	grabberSolenoid->Set(DoubleSolenoid::kForward);
}

void Grabber::Close() {
	grabberSolenoid->Set(DoubleSolenoid::kReverse);
}

