
#include "Mouse.h"

namespace Util {

Mouse::Mouse(std::string eventDevice, int dpi /* = 1 */) : dpi(dpi) {
	// Open the event device
	fd = open(eventDevice.c_str(), O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT) {
			DriverStation::ReportError(("[Mouse] Could not locate Mouse device '" + eventDevice + "'").c_str());
		} else if (errno == EACCES) {
			DriverStation::ReportError(("[Mouse] Do not have permissions to Mouse device '" + eventDevice + "', are we a member of the 'input' group?").c_str());
		} else {
			DriverStation::ReportError(("[Mouse] Unknown error opening Mouse device '" + eventDevice + "'").c_str());
		}
	}

	// Set nonblocking so the read() call below won't just
	// sit and wait for new data
	int flags = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	Reset();
}

void Mouse::Reset() {
	x = 0;
	y = 0;
}

void Mouse::Poll() {
	int count;
	input_event ev;
	while (1) { // This loops until there's nothing left to read
		count = read(fd, &ev, sizeof(input_event));
		if(count < 0 && errno == EAGAIN) {
			return; // Nothing to read, so break out of loop
		} else if (count >= 0) {
			if (ev.type == EV_REL) { // Movement event
				if (ev.code == REL_X) { // On the X axis
					x += ev.value;
				} else if (ev.code == REL_Y) { // On the Y axis
					y += ev.value;
				}
			}
		}
	}
}

int Mouse::GetRawX() {
	return x;
}

int Mouse::GetRawY() {
	return y;
}

float Mouse::GetX() {
	return ((float)x) / dpi;
}

float Mouse::GetY() {
	return ((float)y) / dpi;
}

}
