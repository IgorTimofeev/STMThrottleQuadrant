#pragma once

class Math {
	public:
		static uint32_t clamp(uint32_t value, uint32_t min, uint32_t max) {
			if (value < min)
				value = min;
			else if (value > max)
				value = max;

			return value;
		}

		static float clamp(float value, float min, float max) {
			if (value < min)
				value = min;
			else if (value > max)
				value = max;

			return value;
		}
};
