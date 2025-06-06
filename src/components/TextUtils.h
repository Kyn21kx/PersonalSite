#pragma once
#include "ColorUtils.h"
#include "clay.h"
#include <cstdint>

namespace TextUtils {
	constexpr Clay_TextElementConfig Default(uint16_t fontSize, Clay_Color color = ColorUtils::White()) {
		return {
			.textColor = color,	
			.fontId = 0,
			.fontSize = fontSize,
		};
	}
}

