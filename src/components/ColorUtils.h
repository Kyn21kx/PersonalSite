#pragma once
#include "clay.h"

namespace ColorUtils {

	constexpr Clay_Color White() {
		return { 255, 255, 255, 255 };
	}
	
	constexpr Clay_Color LightGray() {
		return { 194, 194, 194, 255 };
	}
	
	constexpr Clay_Color Black() {
		return { 0, 0, 0, 255 };
	}
	
}

