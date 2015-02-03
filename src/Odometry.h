/*
 * Odometry.h
 *
 *  Created on: Feb 2, 2015
 *      Author: Gabs
 */

#ifndef SRC_ODOMETRY_H_
#define SRC_ODOMETRY_H_

#include "WPILib.h"

class Odometry {
public:
	static Odometry* GetInstance();
	void Update();

	float GetX();
	float GetY();
	float GetRotation();
	void Reset();

private:
	Util::Mouse* mouse;
	Gyro* gyro;
	float x;
	float y;
	float rot;

	static Odometry* instance;
	static Task task;

	static void OdometryTask();
}



#endif /* SRC_ODOMETRY_H_ */
