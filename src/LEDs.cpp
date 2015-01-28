/*
 * LEDs.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs, Jeff, Joe (the spelling errors guy)
 */

#include "LEDs.h"

LEDs::LEDs(uint32_t redChannel, uint32_t greenChannel, uint32_t blueChannel) : red(redChannel), green(greenChannel), blue(blueChannel) {}

void LEDs::Set(float r, float g, float b) {
	red.Set(r);
	green.Set(g);
	blue.Set(b);
}

void LEDs::HSV(float h, float s, float v) {
	h = fmod(h, 360);
	float chroma = v * s;
	float hPrime = h / 60.0;
	float X = chroma * (1.0 - fabs(fmod(hPrime, 2) - 1));

	//R sub 1, G sub 1, and B sub1
	float r1, g1, b1;

	if (0 <= hPrime && hPrime < 1) {
		r1 = chroma;
		g1 = X;
		b1 = 0;
	} else if (1 <= hPrime && hPrime < 2) {
		r1 = X;
		g1 = chroma;
		b1 = 0;
	} else if (2 <= hPrime && hPrime < 3) {
		r1 = 0;
		g1 = chroma;
		b1 = X;
	} else if (3 <= hPrime && hPrime < 4) {
		r1 = 0;
		g1 = X;
		b1 = chroma;
	} else if (4 <= hPrime && hPrime < 5) {
		r1 = X;
		g1 = 0;
		b1 = chroma;
	} else if (5 <= hPrime && hPrime < 6) {
		r1 = chroma;
		g1 = 0;
		b1 = X;
	}

	float m = v - chroma;
	Set(r1 + m, g1 + m, b1 + m);
}