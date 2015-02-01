/*
 * Util.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#include <util/Util.h>

double deadband(double v, double deadband) {
	// If v is within `deadband` of 0, then just return 0.
	// Else, interpolate |v| from [deadband, 1] into [0, 1] and
	// make it negative if it was that before
	return (std::abs(v) < deadband) ? 0 : (std::signbit(v) ? -1 : 1) * interpolate(std::abs(v), deadband, 1.0, 0.0, 1.0);
}



