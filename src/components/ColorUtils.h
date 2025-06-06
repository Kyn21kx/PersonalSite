#pragma once
#include "clay.h"

namespace ColorUtils {

	constexpr Clay_Color Transparent() {
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}
	
	constexpr Clay_Color White(float opacity = 255.0f) {
		return { 255, 255, 255, opacity };
	}
	
	constexpr Clay_Color LightGray(float opacity = 255.0f) {
		return { 194, 194, 194, opacity };
	}
	
	constexpr Clay_Color Black(float opacity = 255.0f) {
		return { 0, 0, 0, opacity };
	}
	
	constexpr Clay_Color Red(float opacity = 255.0f) {
		return { 255, 0, 0, opacity };
	}
	
}

