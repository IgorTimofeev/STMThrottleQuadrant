#pragma once

#include "stm32f4xx_hal.h"

class DigitalPin {
	public:
		DigitalPin(GPIO_TypeDef* port, uint32_t pin) :
			_port(port),
			_pin(pin)
		{

		}

		void begin(uint32_t mode, uint32_t pull, uint32_t speed) {
			GPIO_InitTypeDef gpio;
			gpio.Pin = _pin;
			gpio.Mode = mode;
			gpio.Pull = pull;
			gpio.Speed = speed;
			HAL_GPIO_Init(_port, &gpio);
		}

		void begin(uint32_t mode, uint32_t pull) {
			begin(mode, pull, GPIO_SPEED_FREQ_MEDIUM);
		}

		void beginInput() {
			begin(GPIO_MODE_INPUT, GPIO_PULLUP);
		}

		void beginOutput() {
			begin(GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
		}

		void setValue(bool value) {
			// Wtf, "set" means "no signal"? OK
			HAL_GPIO_WritePin(_port, _pin, value ? GPIO_PIN_RESET : GPIO_PIN_SET);
		}

		bool getValue() {
			// Same shit
			return HAL_GPIO_ReadPin(_port, _pin) == GPIO_PIN_RESET;
		}

		void toggleValue() {
			setValue(!getValue());
		}

		GPIO_TypeDef* getPort() {
			return _port;
		}

		uint32_t getPin() {
			return _pin;
		}

	private:
		GPIO_TypeDef* _port;
		uint32_t _pin;
};
