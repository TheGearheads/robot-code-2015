/*
 * Arm.h
 */

#ifndef ROBOT_CODE_2015_SRC_ARMHELPERS_H_
#define ROBOT_CODE_2015_SRC_ARMHELPERS_H_

#include <math.h>
#include "WPILib.h"
#include "util/Util.h"

float HeightToPot(float height);
float HeightToAngle(float height);
int AngleToPot(float angle);
float AngleToHeight(float angle);
float PotToAngle(int pot);
float PotToHeight(int pot);

#endif /* ROBOT_CODE_2015_SRC_ARMHELPERS_H_ */
