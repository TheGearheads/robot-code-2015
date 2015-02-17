/*
 * Auton.cpp
 *
 *  Created on: Feb 10, 2015
 *      Author: Gabs
 */

#include "WPILib.h"
#include "Drive.h"
#include "Arm.h"
#include "Grabber.h"
#include "Auton.h"


Auton::Auton() {
	timer.Start();
	state = 0;
}

void Auton::Reset() {
	timer.Reset();
	state = 0;
}

void Auton::doAuton() {
	auto drive = Drive::GetInstance();
	auto arm = Arm::GetInstance();
	auto grabber = Grabber::GetInstance();
	auto pref = Preferences::GetInstance();
	int mode = pref->GetInt("auton.mode");
	SmartDashboard::PutNumber("AutonState", state);
	SmartDashboard::PutNumber("AutonMode", mode);
	if (mode == 0) {
		switch (state) {
		case 0:
			grabber->Close();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 1:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 2:
			drive->doDrive(0, 0.3, 0);
			arm->DirectDrive(0);
			if (timer.HasPeriodPassed(0.2)) {
				state++;
			}
			break;
		case 3:
			drive->doDrive(0, 0, 0.3);
			if (timer.HasPeriodPassed(1.9)) {
				state++;
			}
			break;
		case 4:
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(4)) {
				state++;
			}
			break;
		case 5:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 6:
			//grabber->Open(); //Not sure if we should drop it, ask Joe
			//drive->doDrive(0, 0.3, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);
		}
	} else if (mode == 1) {
		switch (state) {
		case 0:	//Close the grabber
			drive->doDrive(0, 0, 0);
			grabber->Close();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 1:	//Raise the arms
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(2.0)) {
				state++;
			}
			break;

		case 2: //Stop the arms, drive a tiny bit forward
			arm->DirectDrive(0);
			drive->doDrive(0, -0.5, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 3: //Stop, arms down
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(1.0)) {
				state++;
			}
			break;

		case 4: //Release grabber
			grabber->Open();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 5: //Bring arms down moar
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(1.0)) {
				state++;
			}
			break;

		case 6:	//Stop arms, move forward
			arm->DirectDrive(0);
			drive->doDrive(0, -0.5, 0);
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 7: //Stop driving, close grabber
			drive->doDrive(0, 0, 0);
			grabber->Close();
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 8: //Raise arms
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 9: //Drive forward
			drive->doDrive(0, -0.2, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 10: //Stop arms, rotate robot
			arm->DirectDrive(0);
			drive->doDrive(0, 0, -0.3);
			if (timer.HasPeriodPassed(1.7)) {
				state++;
			}
			break;

		case 11: //Drive forward, over bump
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(3)) {
				state++;
			}
			break;

		case 12: //Drive forward, off of bump
			drive->doDrive(0, -0.2, 0);
			if (timer.HasPeriodPassed(2)) {
				state++;
			}
			break;

		case 13: //Stop driving
			drive->doDrive(0, 0, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);
		}
	/*} else if (mode == 2) {
		switch (state) {
		case 0: //Close grabber
			grabber->Close();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 1:	//Raise the arms
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(2.0)) {
				state++;
			}
			break;

		case 2: //Stop the arms, drive a tiny bit forward
			arm->DirectDrive(0);
			drive->doDrive(0, -0.5, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 3: //Stop, arms down
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(1.0)) {
				state++;
			}
			break;

		case 4: //Release grabber
			grabber->Open();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 5: //Bring arms down moar
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(1.0)) {
				state++;
			}
			break;

		case 6:	//Stop arms, move forward
			arm->DirectDrive(0);
			drive->doDrive(0, -0.5, 0);
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 7: //Stop driving, close grabber
			drive->doDrive(0, 0, 0);
			grabber->Close();
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 8: //Raise arms
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(0.3)) {
				state++;
			}
			break;

		case 9: //Drive forward
			drive->doDrive(0, -0.2, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		case 10: //Stop arms, rotate robot
			arm->DirectDrive(0);
			drive->doDrive(0, 0, -0.3);
			if (timer.HasPeriodPassed(1.7)) {
				state++;
			}
			break;

		case 11: //Drive forward, over bump
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(3)) {
				state++;
			}
			break;

		case 12: //Drive forward, off of bump
			drive->doDrive(0, -0.2, 0);
			if (timer.HasPeriodPassed(2)) {
				state++;
			}
			break;

		case 13: //Stop driving
			drive->doDrive(0, 0, 0);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;

		}*/
	}
}