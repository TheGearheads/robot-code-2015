/*
 * ArmPIDSource.cpp
 *
 *  Created on: Jan 22, 2015
 *      Author: admin
 */

#include "ArmPIDSource.h"

ArmPIDSource::ArmPIDSource(CANTalon* primary, CANTalon* secondary) : primary(primary), secondary(secondary) {}

double ArmPIDSource::PIDGet() {
	return primary->GetPosition() - secondary->GetPosition();
}


