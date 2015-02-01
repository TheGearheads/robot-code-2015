/*
 * Util.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Gabs
 */

#ifndef ROBOT_CODE_2015_SRC_UTIL_H_
#define ROBOT_CODE_2015_SRC_UTIL_H_

#include <cstdio>
#include <algorithm>
#include "Button.h"

// C++ templates are some witchcraft
// https://en.wikipedia.org/wiki/Template_%28C%2B%2B%29#Function_templates
// They let you define a generic function which operates on type T
// Below, coerce(-2.0, -1.0, 1.0) operates on floats (well, doubles). When the compiler
// sees this, it takes the template below and basically replaces all the T's
// with "double". When it sees coerce(1, 5, 10), it replaces all the T's with "int"
template<class T>
T coerce(T v, T r_min, T r_max) {
	// Coerces v into [r_min, r_max]
	// i.e. if v < r_min, return r_min
	//      if v > r_max, return r_max
	//      else,         return v
	return std::min(r_max, std::max(r_min, v));
}

// A bit more complex, using 2 types instead of just one.
template<class T, class U>
U interpolate(T v, T d_min, T d_max, U r_min, U r_max) {
	// Coerce v into [d_min, d_max]
	// then linear interpolates into [r_min, r_max]
	// https://en.wikipedia.org/wiki/Linear_interpolation
	// (y - y0) / (x - x0) = (y1 - y0) / (x1 - x0)
	// y = y0 + (y1 - y0) * (x - x0) / (x1 - x0)
	// y = r_min + (r_max - r_min) * (v - d_min) / (d_max - d_min)
	// y = (v - d_min) * (r_max - r_min) / (d_max - d_min) + r_min
	return (coerce(v, d_min, d_max) - d_min) * (r_max - r_min) / (d_max - d_min) + r_min;
}

double deadband(double v, double deadband);




#endif /* ROBOT_CODE_2015_SRC_UTIL_H_ */
