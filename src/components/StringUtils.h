#pragma once
#include "clay.h"
#include <cstdint>
#include <string>

namespace StringUtils {
	inline Clay_String FromCString(const char* data, int32_t size) {
		return {
			.isStaticallyAllocated = true,
			.length = size,
			.chars = data
		};
	}

	inline Clay_String StrToClayString(const std::string& str) noexcept {
	    return Clay_String{ false, static_cast<int32_t>(str.size()), str.data()}; //Why is a length or size being stored in a signed value?! They can't be negative! This should really be `size_t`.
	}
}

