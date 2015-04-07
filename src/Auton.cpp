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
	rotary = new AnalogInput(0);
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
	int mode = rotary->GetValue() * 12 / 4096;
	SmartDashboard::PutNumber("AutonState", state);
	SmartDashboard::PutNumber("AutonMode", mode);
	if (mode == 1) { //TOTE
		switch (state) {
		case 0: //Close the grabber
			grabber->Close();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 1: //Raise arms a bit
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 2: //Drive backwards a bit
			drive->doDrive(0, 0.3, 0);
			arm->DirectDrive(0);
			if (timer.HasPeriodPassed(0.2)) {
				state++;
			}
			break;
		case 3: //Rotate
			drive->doDrive(0, 0, 0.3);
			if (timer.HasPeriodPassed(1.9)) {
				state++;
			}
			break;
		case 4: //Drive forward
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(3.5)) {
				state++;
			}
			break;
		case 5: //Stop driving, bring the arms down
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 6: //Open grabber
			grabber->Open();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);
		}
	} else if (mode == 2) { //TOTE AND BIN
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

		case 3: //Stop, 2nd grabber out
			drive->doDrive(0, 0, 0);
			grabber->Open(Grabber::kMini);
			if (timer.HasPeriodPassed(1.0)) {
				state++;
			}
			break;

		case 4: //Rotate
			drive->doDrive(0, 0, -0.3);
			if (timer.HasPeriodPassed(1.9)) {
				state++;
			}
			break;

		case 5: //Drive forward, over bump
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(4.5)) {
				state++;
			}
			break;

		case 6: //Rotate
			drive->doDrive(0, 0, 0.3);
			if (timer.HasPeriodPassed(1.7)) {
				state++;
			}
			break;

		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);
			grabber->Close(Grabber::kMini);
		}
	} else if (mode == 3) { //BIN
		switch (state) {
		case 0: //Close grabber
			grabber->Close();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 1: //Raise arms a bit
			arm->DirectDrive(0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 2: //Drive backward
			drive->doDrive(0, 0.5, 0);
			arm->DirectDrive(0);
			if (timer.HasPeriodPassed(2)) {
				state++;
			}
			break;
		/*case 3: //Drive forward
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(3.5)) {
				state++;
			}
			break;
		case 4: //Stop driving, bring the arms down
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(-0.5);
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		case 5: //Open grabber
			grabber->Open();
			if (timer.HasPeriodPassed(0.5)) {
				state++;
			}
			break;
		*/
		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);

		}
	} else if (mode == 4) { //DRIVE
		switch (state) {
		case 0: //Drive forward
			drive->doDrive(0, -0.3, 0);
			if (timer.HasPeriodPassed(2.1)) {
				state++;
			}
			break;
		default:
			drive->doDrive(0, 0, 0);
			arm->DirectDrive(0);
		}
	}
}
