/*
 * Odometry.h
 *
 *  Created on: Feb 2, 2015
 *      Author: Gabs
 */

#ifndef SRC_ODOMETRY_H_
#define SRC_ODOMETRY_H_

#include <math.h>
#include "WPILib.h"
#include "util/Mouse.h"

class Odometry {
public:
	static Odometry* GetInstance();
	void Update();

	float GetX();
	float GetY();
	float GetRotation();
	void Reset();

private:
	Util::Mouse* mouseLeft;
	Util::Mouse* mouseRight;
	float sensorOffset;
	float x;
	float y;
	float rot;
	Odometry();

	static Odometry* instance;
	static Task task;

	static void OdometryTask();
};



#endif /* SRC_ODOMETRY_H_ */
