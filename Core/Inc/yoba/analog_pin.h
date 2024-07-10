#pragma once

#include "math.h"
#include "stm32f4xx_hal.h"

class AnalogPin {
	public:
		AnalogPin(ADC_HandleTypeDef* adc, uint32_t channel) :
			_adc(adc),
			_channel(channel)
		{

		}

		void begin() {

		}

		uint32_t getValue() const {
			// Changing channel
			ADC_ChannelConfTypeDef channelConfig = {0};
			channelConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
			// Hmmm, seems like it some sort of polling priority
			// See https://stackoverflow.com/questions/73696752/how-are-ranks-interpreted-in-stm32-adc-multi-channel-scan-mode
			channelConfig.Rank = _channel + 1;
			channelConfig.Channel = _channel;
			HAL_ADC_ConfigChannel(&hadc1, &channelConfig);

			// Reading value
			HAL_ADC_Start(_adc);
			HAL_ADC_PollForConversion(_adc, 1);
			auto value = HAL_ADC_GetValue(_adc);
			HAL_ADC_Stop(_adc);

			return value;
		}

	private:
		ADC_HandleTypeDef* _adc;
		uint32_t _channel;
};
