#pragma once

#include "analog_pin.h"
#include "math.h"

class Potentiometer {
	public:
		Potentiometer(const AnalogPin& analogPin, uint32_t minimum, uint32_t maximum) :
			_analogPin(analogPin),
			_minimum(minimum),
			_maximum(maximum)
		{

		}

		uint32_t getValue() {
			uint32_t pinValue = _analogPin.getSmoothValue(20, 0.005);

//			return pinValue;

			uint32_t clampedPinValue = Math::clamp(pinValue, _minimum, _maximum);
			float ratio = (float) (clampedPinValue - _minimum) / (float) (_maximum - _minimum);

			return (uint32_t) (ratio * 4096.0f);
		}

	private:
		AnalogPin _analogPin;
		uint32_t _minimum;
		uint32_t _maximum;

};
