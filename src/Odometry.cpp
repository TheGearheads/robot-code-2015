/*
 * Odometry.cpp
 *
 *  Created on: Feb 2, 2015
 *      Author: Gabs
 */

#include "Odometry.h"

Task Odometry::task("OdometryTask", (FUNCPTR)OdometryTask);

void Odometry::OdometryTask() {
	while (true) {
		Wait(0.01);
		Odometry::GetInstance()->Update();
	}

}

Odometry::Odometry() {
	auto pref = Prefernces::GetInstance();
	mouse = new Mouse(pref->GetString("odometry.device"));
	gyro = new Gyro(pref->GetInt("odometry.gyroChannel"));
}

Odometry* Odometry::GetInstance() {
	if (instance == nullptr) {
			instance = new Odometry();
	}
	return instance;
}

void Odometry::Update() {
	mouse->Poll();
	rot = gyro->GetAngle();
}

void Odometry::Reset() {
	x = 0;
	y = 0;
	rot = 0;
	gyro->Reset();
}

float Odometry::GetX() {
	return x;
}

float Odometry::GetY() {
	return y;
}

float Odometry::GetRotation() {
	return rot;
}

Odometry* Odometry::instance = nullptr;
