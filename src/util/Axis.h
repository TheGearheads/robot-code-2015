/*
 * Axis.h
 */

#ifndef SRC_UTIL_AXIS_H_
#define SRC_UTIL_AXIS_H_

#include <vector>
#include "WPILib.h"
#include "Util.h"

namespace Util {

class Axis {
	public:
		Axis(int axisChannel);
		Axis(int axisChannel, Joystick* stick);
		Axis(std::string axisConfig);
		~Axis();
		void SetDeadband(float newDeadband);
		float GetDeadband();
		float Get();
	private:
		int axisChannel;
		bool invert = false;
		float deadband;
		Joystick* stick;
		std::string config;

};

}

#endif /* SRC_UTIL_AXIS_H_ */
