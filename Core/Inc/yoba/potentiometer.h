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

		uint32_t getValue() const {
			float value = (float) _analogPin.getValue() / 4096.0f;

			return (uint32_t) (_minimum + value * (_maximum - _minimum));
		}

	private:
		AnalogPin _analogPin;
		uint32_t _minimum;
		uint32_t _maximum;
};
