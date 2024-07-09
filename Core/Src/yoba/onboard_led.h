#pragma once

#include "digital_pin.h"

class OnboardLED {
	public:
		OnboardLED(const DigitalPin& pin, uint32_t interval) :
			_pin(pin),
			_interval(interval)
		{
			_deadline = HAL_GetTick() + _interval;
		}


		void tick() {
			uint32_t time = HAL_GetTick();

			if (time <= _deadline)
				return;

			_pin.setValue(_state);

			_state = !_state;
			_deadline = time + _interval;
		}

	private:
		DigitalPin _pin;
		uint32_t _interval;

		bool _state = false;
		uint32_t _deadline;
};
