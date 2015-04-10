/*
 * Grabber.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gearheads
 */
#include "Grabber.h"

Grabber::Grabber() {
	auto pref = Preferences::GetInstance();
	int grabberOpenChannel;
	int grabberCloseChannel;

	grabberCloseChannel = pref->GetInt("grabber.closeChannel");
	grabberOpenChannel = pref->GetInt("grabber.openChannel");
	grabberSolenoid = new DoubleSolenoid(pref->GetInt("grabber.pcm", 5), grabberOpenChannel, grabberCloseChannel);

	grabberCloseChannel = pref->GetInt("grabber.mini.closeChannel");
	grabberOpenChannel = pref->GetInt("grabber.mini.openChannel");
	miniGrabberSolenoid = new DoubleSolenoid(pref->GetInt("grabber.pcm", 5), grabberOpenChannel, grabberCloseChannel);

	compressor = new Compressor(pref->GetInt("grabber.pcm", 5));
	compressor->SetClosedLoopControl(true);
}

Grabber* Grabber::GetInstance() {
	if (instance == nullptr) {
			instance = new Grabber();
	}
	return instance;
}

bool Grabber::Get(GrabberType type /*= kMain*/) {
	if (type == kMain) {
		return statusMain;
	} else {
		return statusMini;
	}
}

void Grabber::Open(GrabberType type /*= kMain*/) {
	DoubleSolenoid* solenoid;
	if (type == kMain) {
		statusMain = true;
		solenoid = grabberSolenoid;
	} else {
		statusMini = true;
		solenoid = miniGrabberSolenoid;
	}
	SmartDashboard::PutBoolean("grabber", statusMain);
	SmartDashboard::PutBoolean("miniGrabber", statusMini);
	solenoid->Set(DoubleSolenoid::kForward);
}

void Grabber::Close(GrabberType type /*= kMain*/) {
	DoubleSolenoid* solenoid;
	if (type == kMain) {
		statusMain = false;
		solenoid = grabberSolenoid;
	} else {
		statusMini = false;
		solenoid = miniGrabberSolenoid;
	}
	SmartDashboard::PutBoolean("grabber", statusMain);
	SmartDashboard::PutBoolean("miniGrabber", statusMini);
	solenoid->Set(DoubleSolenoid::kReverse);
}

Grabber* Grabber::instance = nullptr;
