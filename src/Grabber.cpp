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
	grabberSolenoid = new DoubleSolenoid(pref->GetInt("grabber.pcm", 5), grabberOpenChannel, grabberCloseChannel);
	compressor = new Compressor(pref->GetInt("grabber.pcm", 5));
	compressor->SetClosedLoopControl(true);
}

Grabber* Grabber::GetInstance() {
	if (instance == nullptr) {
			instance = new Grabber();
	}
	return instance;
}

void Grabber::Open() {
	SmartDashboard::PutBoolean("grabber", true);
	grabberSolenoid->Set(DoubleSolenoid::kForward);
}

void Grabber::Close() {
	SmartDashboard::PutBoolean("grabber", false);
	grabberSolenoid->Set(DoubleSolenoid::kReverse);
}

Grabber* Grabber::instance = nullptr;
