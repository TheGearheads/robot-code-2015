/*
 * ArmPIDSource.h
 *
 *  Created on: Jan 22, 2015
 *      Author: admin
 */

#ifndef SRC_ARMPIDSOURCE_H_
#define SRC_ARMPIDSOURCE_H_
#include "WPILib.h"


class ArmPIDSource : public PIDSource {
	CANTalon* primary;
	CANTalon* secondary;
public:
	ArmPIDSource(CANTalon* primary, CANTalon* secondary);
	double PIDGet();
};





#endif /* SRC_ARMPIDSOURCE_H_ */
