#ifndef SRC_MOUSE_H_
#define SRC_MOUSE_H_

#include <fcntl.h>
#include <string>
#include <linux/input.h>
#include <unistd.h>
#include <errno.h>
#include "WPILib.h"

namespace Util {

class Mouse {
	int fd;
	int x;
	int y;
	int dpi;

public:
	Mouse(std::string eventDevice, int dpi = 1);
	void Poll();
	void Reset();
	int GetRawX();
	int GetRawY();
	float GetX();
	float GetY();

};

}

#endif
