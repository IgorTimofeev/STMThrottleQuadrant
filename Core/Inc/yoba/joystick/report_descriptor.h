#pragma once

#include "stdint.h"

#pragma pack(push, 1)
struct JoystickReportDescriptor {
	public:
		// Axis with values in range [0; 4096] for precise ADC mapping
		// Speed brake
		uint16_t x;
		// Throttle left
		uint16_t y;
		// Throttle right
		uint16_t z;
		// Flaps
		uint16_t rx;
		// Pitch trim wheel
		uint16_t ry;

		// Push buttons, 1 bit per each
		// 3 toggle switches with 2 virtual buttons per each (1 button for "on" state and 1 for "off")
		// 3 rotary encoders with 3 virtual buttons per each (1 button for left rotation, 1 for push button and 1 for right rotation)
		// 3 push buttons
		// 1 landing gear toggle switch with 2 virtual buttons
		uint32_t buttons;
};
#pragma pack(pop)
