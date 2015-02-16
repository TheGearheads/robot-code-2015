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

public:
	Robot() : IterativeRobot(), stick(0){

	}

	void RobotInit()
	{
		//comment out next line to set for Joystick
		lw = LiveWindow::GetInstance();
		//Arm::GetInstance()->SetMode(Arm::kDirect);
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
		SmartDashboard::PutBoolean("Following", false);

	}

	void TeleopPeriodic()
	{
		drive.doDrive(input.GetX(), input.GetY(), input.GetRotation());
		input.GetGrabberInput();
		input.GetArmInput();
		//LED controls

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
