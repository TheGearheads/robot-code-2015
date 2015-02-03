/*
 * LEDs.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Gabs, Jeff, Joe
 */

#include "LEDs.h"

/**
 * LEDs class to control RGB LEDs
 *
 * @param relayChannel The LEDs Relay channel
 * @param redChannel The PWM channel to give the Red signal
 * @param greenChannel The PWM channel to give the Green signal
 * @param blueChannel The PWM channel to give the Blue signal
 */
LEDs::LEDs(uint32_t relayChannel, uint32_t redChannel, uint32_t greenChannel, uint32_t blueChannel) : power(relayChannel),
red(redChannel), green(greenChannel), blue(blueChannel) {
	power.Set(Relay::kOn);
}

/**
 * Set the color of the LEDs
 *
 * Takes an RGB triplet
 * @param r Red [0, 1]
 * @param g Green [0, 1]
 * @param b Blue [0, 1]
 */
void LEDs::Set(float r, float g, float b) {
	red.Set(r);
	green.Set(g);
	blue.Set(b);
}

/**
 * Set the color of the LEDs
 *
 * <a href="rttps://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV">HSV to RGB conversion</a>
 *
 * Takes an HSV triplet
 * @param h Hue [0, 360)
 * @param s Saturation [0, 1]
 * @param v Value [0, 1]
 */
void LEDs::HSV(float h, float s, float v) {
	h = fmod(h, 360);
	float chroma = v * s;
	float hPrime = h / 60.0;
	float X = chroma * (1.0 - fabs(fmod(hPrime, 2) - 1));

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

/*
 * should be called once in the periodic functions
 * entirely untested
 * -Jeff
 *
 * @param sat Saturation [0,1] 1 by default
 * @param val Value [0,1] 1 by default
 */
void LEDs::Rainbow(float sat=1, float val=1) {
	//Set the hue
	HSV(lastHue, sat, val);

	//Manipulate lastHue
	lastHue++;
	if (lastHue == 360) {
		lastHue = 0;
	}
}

