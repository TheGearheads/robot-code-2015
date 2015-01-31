#include "WPILib.h"
#include "Drive.h"
#include "Input.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = NULL;
	Drive drive;
	Joystick stick;
	Input input;
	Preferences* pref;

public:
	Robot() : IterativeRobot(), stick(0){

	}

	void RobotInit()
	{
		//comment out next line to set for Joystick
		input.SetType(Input::kXbox);
		lw = LiveWindow::GetInstance();
		pref = Preferences::GetInstance();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{


		//LED controls

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		drive.doDrive(input.GetX(), input.GetY(), input.GetRotation());

		//LED controls

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
