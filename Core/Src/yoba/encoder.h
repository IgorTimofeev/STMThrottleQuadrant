#pragma once

#include "digital_pin.h"

class Encoder {
	public:
		Encoder(const DigitalPin& clkPin, const DigitalPin& dtPin, const DigitalPin& swPin) :
			_clkPin(clkPin),
			_dtPin(dtPin),
			_swPin(swPin)
		{
			_clkPin.begin(GPIO_MODE_IT_RISING_FALLING, GPIO_PULLUP);
			_dtPin.begin(GPIO_MODE_IT_RISING_FALLING, GPIO_PULLUP);
			_swPin.begin(GPIO_MODE_INPUT, GPIO_PULLUP);

			_oldState = readState();
		}

		void tick() {
			auto newState = readState();

			if (newState != _oldState) {
				switch (_oldState | (newState << 2)) {
					case 0: case 5: case 10: case 15:
						break;
					case 1: case 7: case 8: case 14:
						_value--;
						break;
					case 2: case 4: case 11: case 13:
						_value++;
						break;
					case 3: case 12:
						_value -= 2;
						break;
					default:
						_value += 2;
						break;
				}

				_oldState = newState;
			}

			_isPressed = _swPin.getValue();
		}

		void setValue(int32_t value) {
			_value = value;
		}

		int32_t getValue() const {
			return _value;
		}

		bool isPressed() const {
			return _isPressed;
		}

	private:

		DigitalPin _clkPin;
		DigitalPin _dtPin;
		DigitalPin _swPin;
		uint8_t _oldState = 0;
		int32_t _value = 0;
		bool _isPressed = false;

		uint8_t readState() {
			return (_clkPin.getValue() << 1) | _dtPin.getValue();
		}
};
