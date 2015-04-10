#include "WPILib.h"
#include "Drive.h"
#include "Input.h"
#include "Auton.h"
#include "LEDStrip.h"
#include "LEDController.h"
#include "LEDs.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = NULL;
	Drive* drive;
	Joystick stick;
	Input input;
	Auton* auton;
	LEDs* leds;

public:
	Robot() : IterativeRobot(), stick(0){
		auton = Auton::GetInstance();
		drive = Drive::GetInstance();
		leds = LEDs::GetInstance();
	}

	void RobotInit() {
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit() {
		auton->Reset();
	}

	void DisabledInit() {
	}

	void AutonomousPeriodic() {
		auton->doAuton();
	}

	void TeleopInit() {
		SmartDashboard::PutBoolean("Following", false);
	}

	void TeleopPeriodic() {
		drive->doDrive(input.GetX(), input.GetY(), input.GetRotation());
		input.GetGrabberInput();
		input.GetArmInput();
	}

	void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
