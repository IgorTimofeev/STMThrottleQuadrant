#pragma once

#include "stm32f4xx_hal.h"
#include "usb_device.h"
#include "stdint.h"

#include "../digital_pin.h"
#include "report_descriptor.h"

class JoystickAbstractButton {
	public:
		JoystickAbstractButton(const DigitalPin& pin) :
			_pin(pin)
		{

		}

		void updateReport(JoystickReportDescriptor& report, uint8_t& index);

	protected:
		DigitalPin _pin;
};

class JoystickButton : public JoystickAbstractButton {
	public:
		JoystickButton(const DigitalPin& pin) : JoystickAbstractButton(pin) {

		}

		void tick() {
			_state = _pin.getValue();
		}

		void updateReport(JoystickReportDescriptor& report, uint8_t& index) {
			report.buttons |= _state << index++;
		}

	private:
		bool _state = false;
};

class JoystickToggleButton : public JoystickAbstractButton {
	public:
		JoystickToggleButton(const DigitalPin& pin) : JoystickAbstractButton(pin) {
			_lastPinValue = _pin.getValue();
		}

		void tick() {
			auto pinValue = _pin.getValue();
			auto time = HAL_GetTick();

			if (pinValue != _lastPinValue) {
				if (pinValue) {
					_pressDeadline1 = time + _pressDuration;
				}
				else {
					_pressDeadline2 = time + _pressDuration;
				}

				_lastPinValue = pinValue;
			}

			if (time >= _pressDeadline1)
				_pressDeadline1 = 0;

			if (time >= _pressDeadline2)
				_pressDeadline2 = 0;
		}

		void updateReport(JoystickReportDescriptor& report, uint8_t& index) {
			report.buttons |= (_pressDeadline1 > 0) << index++;
			report.buttons |= (_pressDeadline2 > 0) << index++;
		}

	private:
		uint16_t _pressDuration = 250;
		uint32_t _pressDeadline1 = 0;
		uint32_t _pressDeadline2 = 0;
		bool _lastPinValue = false;
};
