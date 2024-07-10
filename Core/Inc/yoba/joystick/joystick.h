#pragma once

#include <yoba/joystick/report_descriptor.h>
#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "usb_device.h"

#include "../analog_pin.h"
#include "../digital_pin.h"
#include "../potentiometer.h"
#include "../encoder.h"

#include "report_descriptor.h"
#include "button.h"
#include "encoder.h"

class Joystick {
	public:
		Joystick() {

		}

		void tick() {
			updateReportAxis();
			updateReportButtons();

			SendGovnoReport((uint8_t*) &_report, sizeof(JoystickReportDescriptor));
		}

	private:
		JoystickReportDescriptor _report;

		Potentiometer
			_speedBrake = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_0), 1657, 2800),

			_throttle1 = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_1), 1701, 2930),
			_throttle2 = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_2), 1717, 2800),

			_flaps = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_3), 1682, 2950),
			_trimWheel = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_4), 0, 4096);

		JoystickEncoder
			_encoder1 = JoystickEncoder(Encoder(
				DigitalPin(GPIOB, GPIO_PIN_4),
				DigitalPin(GPIOB, GPIO_PIN_5),
				DigitalPin(GPIOB, GPIO_PIN_6)
			)),
			_encoder2 = JoystickEncoder(Encoder(
				DigitalPin(GPIOB, GPIO_PIN_7),
				DigitalPin(GPIOB, GPIO_PIN_8),
				DigitalPin(GPIOB, GPIO_PIN_9)
			)),
			_encoder3 = JoystickEncoder(Encoder(
				DigitalPin(GPIOB, GPIO_PIN_12),
				DigitalPin(GPIOB, GPIO_PIN_13),
				DigitalPin(GPIOB, GPIO_PIN_14)
			));

		JoystickToggleButton
			_toggle1 = JoystickToggleButton(DigitalPin(GPIOA, GPIO_PIN_8)),
			_toggle2 = JoystickToggleButton(DigitalPin(GPIOA, GPIO_PIN_9)),
			_toggle3 = JoystickToggleButton(DigitalPin(GPIOA, GPIO_PIN_10)),

			_landingGear = JoystickToggleButton(DigitalPin(GPIOB, GPIO_PIN_3));

		JoystickButton
			_button1 = JoystickButton(DigitalPin(GPIOB, GPIO_PIN_10)),
			_button2 = JoystickButton(DigitalPin(GPIOA, GPIO_PIN_15)),
			_button3 = JoystickButton(DigitalPin(GPIOB, GPIO_PIN_15));

		void updateReportAxis() {
			_report.x = _speedBrake.getValue();
			_report.y = _throttle1.getValue();
			_report.z = _throttle2.getValue();
			_report.rx = _flaps.getValue();
			_report.ry = _trimWheel.getValue();
		}

		void updateReportButtons() {
			uint8_t index = 0;

			_report.buttons = 0;

			_toggle1.updateReport(_report, index);
			_toggle2.updateReport(_report, index);
			_toggle3.updateReport(_report, index);

			_encoder1.updateReport(_report, index);
			_encoder2.updateReport(_report, index);
			_encoder3.updateReport(_report, index);

			_button1.updateReport(_report, index);
			_button2.updateReport(_report, index);
			_button3.updateReport(_report, index);

			_landingGear.updateReport(_report, index);
		}
};
