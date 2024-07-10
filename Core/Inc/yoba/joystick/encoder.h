#pragma once

#include <yoba/joystick/report_descriptor.h>
#include "stm32f4xx_hal.h"
#include "usb_device.h"
#include "stdint.h"

#include "../encoder.h"
#include "report_descriptor.h"

class JoystickEncoder {
	public:
		JoystickEncoder(const Encoder& encoder) : _encoder(encoder) {

		}

		void updateReport(JoystickReportDescriptor& report, uint8_t& index) {
			auto state = _encoder.getState();
			auto time = HAL_GetTick();

			// Left
			if (state.left) {
				_leftDeadline = time + _interval;
			}
			else if (time >= _leftDeadline) {
				_leftDeadline = 0;
			}

			// Right
			if (state.right) {
				_rightDeadline = time + _interval;
			}
			else if (time >= _rightDeadline) {
				_rightDeadline = 0;
			}

			report.buttons |= (_leftDeadline > 0) << index++;
			report.buttons |= state.pressed << index++;
			report.buttons |= (_rightDeadline > 0) << index++;
		}

	private:
		uint32_t _leftDeadline = 0;
		uint32_t _rightDeadline = 0;
		uint32_t _interval = 200;
		Encoder _encoder;
};
