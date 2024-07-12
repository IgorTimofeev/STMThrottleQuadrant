#pragma once

#include "stm32f4xx_hal.h"
#include "usb_device.h"
#include "stdint.h"

#include "../encoder.h"
#include "report_descriptor.h"

class JoystickEncoder {
	public:
		JoystickEncoder(const Encoder& encoder) : _encoder(encoder) {

		}

		void read() {
			auto state = _encoder.read();

			if (!(state.left || state.right))
				return;

			auto time = HAL_GetTick();

			if (state.left)
				_leftDeadline = time + _interval;

			if (state.right)
				_rightDeadline = time + _interval;
		}

		void tick() {
			if (_leftDeadline == 0 && _rightDeadline == 0)
				return;

			auto time = HAL_GetTick();

			if (time >= _leftDeadline)
				_leftDeadline = 0;

			// Right
			if (time >= _rightDeadline)
				_rightDeadline = 0;
		}

		void updateReport(JoystickReportDescriptor& report, uint8_t& index) {
			report.buttons |= (_leftDeadline > 0) << index++;
			report.buttons |= _pressed << index++;
			report.buttons |= (_rightDeadline > 0) << index++;
		}

	private:
		Encoder _encoder;

		uint32_t
			_leftDeadline = 0,
			_rightDeadline = 0,
			_interval = 50;

		bool _pressed = false;
};
