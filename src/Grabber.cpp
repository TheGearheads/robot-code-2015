/*
 * Grabber.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gearheads
 */
#include "Grabber.h"

Grabber::Grabber() : grabberSolenoid(grabberOpenChannel, grabberCloseChannel) {
}

void Grabber::Open() {
	grabberSolenoid.Set(DoubleSolenoid::kForward);
}

void Grabber::Close() {
	grabberSolenoid.Set(DoubleSolenoid::kReverse);
}

