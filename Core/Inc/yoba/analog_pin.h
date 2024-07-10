#pragma once

#include "math.h"
#include <cmath>
#include "stm32f4xx_hal.h"

class AnalogPin {
	public:
		AnalogPin(ADC_HandleTypeDef* adc, uint32_t channel) :
			_adc(adc),
			_channel(channel)
		{

		}

		uint32_t getValue() {
			// Changing channel
			ADC_ChannelConfTypeDef channelConfig = {
				.Channel = _channel,
				.Rank = 1,
				.SamplingTime = ADC_SAMPLETIME_28CYCLES,
			};

			HAL_ADC_ConfigChannel(&hadc1, &channelConfig);

			// Reading value
			HAL_ADC_Start(_adc);
			HAL_ADC_PollForConversion(_adc, HAL_MAX_DELAY);
			uint32_t value = HAL_ADC_GetValue(_adc);
			HAL_ADC_Stop(_adc);

			return value;
		}

		uint32_t getSmoothValue(uint8_t deltaThreshold, double newValueFactor) {
			double newValue = getValue();

			if (_lastValue < 0) {
				_lastValue = newValue;
			}
			else {
				if (std::abs(newValue - _lastValue) > deltaThreshold)
					_lastValue = newValue * newValueFactor + _lastValue * (1 - newValueFactor);
			}

			return _lastValue;
		}

	private:
		double _lastValue = -1;
		ADC_HandleTypeDef* _adc;
		uint32_t _channel;
};
