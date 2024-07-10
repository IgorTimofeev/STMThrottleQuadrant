#pragma once

#include "stm32f4xx_hal.h"
#include "stdint.h"

#include "analog_pin.h"
#include "digital_pin.h"
#include "potentiometer.h"
#include "encoder.h"
#include "usb_device.h"

#pragma pack(push, 1)
struct JoystickReport {
	public:
		// Axis values in range [0; 4096] for ADC mapping
		uint16_t x;
		uint16_t y;
		uint16_t z;
		uint16_t rx;
		uint16_t ry;

		// 16 buttons, 1 bit per each
		uint16_t buttons;
};
#pragma pack(pop)

class Joystick {
	public:
		Joystick() {

		}

		void tick() {
			updateReportAxis();
			updateReportButtons();

			SendGovnoReport((uint8_t*) &_report, sizeof(JoystickReport));
		}

	private:
		Potentiometer
			_speedBrake = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_0), 0, 4096),

			_throttle1 = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_1), 0, 4096),
			_throttle2 = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_2), 0, 4096),

			_flaps = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_3), 0, 4096),
			_trimWheel = Potentiometer(AnalogPin(&hadc1, ADC_CHANNEL_4), 0, 4096);

		Encoder
			_encoder1 = Encoder(
				DigitalPin(GPIOB, GPIO_PIN_4),
				DigitalPin(GPIOB, GPIO_PIN_5),
				DigitalPin(GPIOB, GPIO_PIN_6)
			),
			_encoder2 = Encoder(
				DigitalPin(GPIOB, GPIO_PIN_7),
				DigitalPin(GPIOB, GPIO_PIN_8),
				DigitalPin(GPIOB, GPIO_PIN_9)
			),
			_encoder3 = Encoder(
				DigitalPin(GPIOB, GPIO_PIN_12),
				DigitalPin(GPIOB, GPIO_PIN_13),
				DigitalPin(GPIOB, GPIO_PIN_14)
			);

		DigitalPin
			_toggle1 = DigitalPin(GPIOA, GPIO_PIN_8),
			_toggle2 = DigitalPin(GPIOA, GPIO_PIN_9),
			_toggle3 = DigitalPin(GPIOA, GPIO_PIN_11),

			_button1 = DigitalPin(GPIOA, GPIO_PIN_12),
			_button2 = DigitalPin(GPIOA, GPIO_PIN_15),
			_button3 = DigitalPin(GPIOB, GPIO_PIN_15),

			_landingGear = DigitalPin(GPIOB, GPIO_PIN_3);

		JoystickReport _report;

		void updateReportAxis() {
			_report.x = _speedBrake.getValue();
			_report.y = _throttle1.getValue();
			_report.z = _throttle2.getValue();
			_report.rx = _flaps.getValue();
			_report.ry = _trimWheel.getValue();
		}

		void updateReportButton(uint8_t& index, bool value) {
			_report.buttons |= value << index;
			index++;
		}

		void updateReportButtonsFromEncoder(uint8_t& index, Encoder& encoder) {
			auto state = encoder.getState();

			updateReportButton(index, state.left);
			updateReportButton(index, state.pressed);
			updateReportButton(index, state.right);
		}

		void updateReportButtons() {
			uint8_t index = 0;

			_report.buttons = 0;
			updateReportButton(index, _toggle1.getValue());
			updateReportButton(index, _toggle2.getValue());
			updateReportButton(index, _toggle3.getValue());

			updateReportButtonsFromEncoder(index, _encoder1);
			updateReportButtonsFromEncoder(index, _encoder2);
			updateReportButtonsFromEncoder(index, _encoder3);

			updateReportButton(index, _button1.getValue());
			updateReportButton(index, _button2.getValue());
			updateReportButton(index, _button3.getValue());
		}
};
