#pragma once

#include "stdint.h"
#include "analog_pin.h"
#include "digital_pin.h"
#include "potentiometer.h"
#include <stdbool.h>
#include "encoder.h"
#include "math.h"
#include "onboard_led.h"
#include "stm32f4xx_hal.h"

void yoba(void) {
	Potentiometer
		speedBrake = Potentiometer(AnalogPin(&hadc1, 0), 0, 1),
		throttle1 = Potentiometer(AnalogPin(&hadc1, 1), 0, 1),
		throttle2 = Potentiometer(AnalogPin(&hadc1, 2), 0, 1),
		flaps = Potentiometer(AnalogPin(&hadc1, 3), 0, 1),
		trimWheel = Potentiometer(AnalogPin(&hadc1, 4), 0, 1);

	DigitalPin
		ledPin = DigitalPin(GPIOC, GPIO_PIN_13),
		landingGear = DigitalPin(GPIOA, GPIO_PIN_8);

	OnboardLED onboardLED = OnboardLED(DigitalPin(GPIOC, GPIO_PIN_13), 100);

	while (true) {
		onboardLED.tick();

		HAL_Delay(1);
	}
}
