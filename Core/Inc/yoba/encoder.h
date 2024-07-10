#pragma once

#include "digital_pin.h"

struct EncoderState {
	public:
		bool
			left,
			right,
			pressed;
};

class Encoder {
	public:
		Encoder(const DigitalPin& clkPin, const DigitalPin& dtPin, const DigitalPin& swPin) :
			_clkPin(clkPin),
			_dtPin(dtPin),
			_swPin(swPin)
		{
			_oldRotation = readRotation();
		}

		EncoderState getState() {
			EncoderState state;
			state.left = false;
			state.right = false;
			state.pressed = _swPin.getValue();

			auto rotation = readRotation();

			if (rotation != _oldRotation) {
				switch (_oldRotation | (rotation << 2)) {
//					case 0: case 5: case 10: case 15:
//						break;
//					case 1: case 7: case 8: case 14:
//						_value--;
//						break;
//					case 2: case 4: case 11: case 13:
//						_value++;
//						break;
//					case 3: case 12:
//						_value -= 2;
//						break;
//					default:
//						_value += 2;
//						break;

					// Button simulation
					case 0: case 5: case 10: case 15:
						break;
					case 1: case 7: case 8: case 14: case 3: case 12:
						state.left = true;
						break;
					default:
						state.right = true;
						break;

				}

				_oldRotation = rotation;
			}


			return state;
		}

	private:

		DigitalPin _clkPin;
		DigitalPin _dtPin;
		DigitalPin _swPin;
		uint8_t _oldRotation = 0;

		uint8_t readRotation() {
			return (_clkPin.getValue() << 1) | _dtPin.getValue();
		}
};
