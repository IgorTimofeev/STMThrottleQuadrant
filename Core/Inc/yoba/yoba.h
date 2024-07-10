#pragma once

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include <stdbool.h>

#include "joystick/joystick.h"
#include "digital_pin.h"

Joystick joystick = Joystick();
DigitalPin LEDPin = DigitalPin(GPIOC, GPIO_PIN_13);

void yobaMain() {
	LEDPin.setValue(true);

	while (true) {
		joystick.tick();
	}
}

void yobaInterrupt(uint16_t pin) {
	switch (pin) {
		case GPIO_PIN_12:
			// Похуй...

			break;
	}
}
