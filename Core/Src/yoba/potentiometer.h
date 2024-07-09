#pragma once

#include "analog_pin.h"
#include "math.h"

class Potentiometer {
	public:
		Potentiometer(const AnalogPin& analogPin, float minimum, float maximum) :
			_analogPin(analogPin),
			_minimum(minimum),
			_maximum(maximum)
		{

		}

		float getValue() const {
			float value = (float) _analogPin.getValue() / 4096.0f;

			value = Math::clamp(value, _minimum, _maximum);

			return (value - _minimum) / (_maximum - _minimum);
		}

	private:
		AnalogPin _analogPin;
		float _minimum;
		float _maximum;
};
