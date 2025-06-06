#pragma once
#include "clay.h"
#include <cstdint>

namespace StringUtils {
	inline Clay_String FromCString(const char* data, int32_t size) {
		return {
			.length = size,
			.chars = data
		};
	}
}

