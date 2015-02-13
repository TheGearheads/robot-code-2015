/*
 * Axis.h
 */

#ifndef SRC_UTIL_AXIS_H_
#define SRC_UTIL_AXIS_H_

#include <vector>
#include "WPILib.h"

namespace Util {

class Axis {
	public:
		Axis(int axisChannel);
		Axis(int axisChannel, Joystick* stick);
		Axis(std::string axisConfig);
		~Axis();
		void SetDeadband(float newDeadband);
		float GetDeadband();
		bool Get();
	private:
		int axisChannel;
		bool invert = false;
		float deadband;
		Joystick* stick;
		std::string config;

		static std::vector<Axis*> axes;
		static Task task;
		static bool taskRunning;

		static void AxisChecker();
		static void SetEnabled(bool enabled);
		static void AddAxis(Axis* axisPtr);
		static void DelAxis(Axis* axisPtr);
		static Axis* FindAxis(std::string key);


};

}

#endif /* SRC_UTIL_AXIS_H_ */
