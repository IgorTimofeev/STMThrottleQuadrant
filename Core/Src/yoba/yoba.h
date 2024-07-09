#pragma once

#include "stdint.h"
#include "analog_pin.h"
#include "digital_pin.h"
#include "potentiometer.h"
#include <stdbool.h>
#include "encoder.h"
#include "math.h"
#include "stm32f4xx_hal.h"

Potentiometer
	speedBrake = Potentiometer(AnalogPin(&hadc1, 0), 0, 1),
	throttle1 = Potentiometer(AnalogPin(&hadc1, 1), 0, 1),
	throttle2 = Potentiometer(AnalogPin(&hadc1, 2), 0, 1),
	flaps = Potentiometer(AnalogPin(&hadc1, 3), 0, 1),
	trimWheel = Potentiometer(AnalogPin(&hadc1, 4), 0, 1);

DigitalPin
	ledPin = DigitalPin(GPIOC, GPIO_PIN_13),
	landingGear = DigitalPin(GPIOA, GPIO_PIN_8);

DigitalPin onboardLEDPin = DigitalPin(GPIOC, GPIO_PIN_13);

void yobaMain() {
	onboardLEDPin.setValue(true);

	while (true) {
		HAL_Delay(1);
	}
}

void yobaInterrupt(uint16_t pin) {
	switch (pin) {
		case GPIO_PIN_12:
			// Похуй...

			break;
	}
}
