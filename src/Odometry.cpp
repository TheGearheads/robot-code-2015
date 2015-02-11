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

Odometry::Odometry() : x(0), y(0), rot(0) {
	auto pref = Preferences::GetInstance();
	mouseLeft = new Util::Mouse(pref->GetString("odometry.left"), pref->GetInt("odometry.left.dpi", 1));
	mouseRight = new Util::Mouse(pref->GetString("odometry.right"), pref->GetInt("odometry.right.dpi", 1));
	sensorOffset = pref->GetFloat("odometry.separation") / 2;
}

Odometry* Odometry::GetInstance() {
	if (instance == nullptr) {
			instance = new Odometry();
	}
	return instance;
}

void Odometry::Update() {
	mouseLeft->Poll();
	mouseRight->Poll();

float dlx = mouseLeft->GetX();
float dly =-mouseLeft->GetY();
float drx = mouseRight->GetX();
float dry = -mouseRight->GetY();

float lx = x - sensorOffset * cos(rot);
float ly = y - sensorOffset * sin(rot);
float rx = x + sensorOffset * cos(rot);
float ry = y + sensorOffset * sin(rot);

lx += dlx * cos(rot) + dly * sin(rot);
ly += dlx * sin(rot) - dly * cos(rot);
rx += drx * cos(rot) + dry * sin(rot);
ry += drx * sin(rot) - dry * cos(rot);

x = (lx + rx) /2;
y = (ly + ry) /2;
rot = atan2(ry - ly, rx - lx); // is this correct?

mouseLeft->Reset();
mouseRight->Reset();

}

void Odometry::Reset() {
	x = 0;
	y = 0;
	rot = 0;
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
