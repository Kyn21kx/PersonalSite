#include "raylib.h"

namespace Fonts {
	enum class ESize : size_t {
		Small,
		Medium,
		Big,
		Subtitle,
		Title,
		ESizeMax
	};

	constexpr size_t FONT_COUNT = 5; 

	static_assert(FONT_COUNT == static_cast<size_t>(ESize::ESizeMax), "Font enum does not match exposed size!");
	
	inline Font g_fonts[FONT_COUNT];
	
}
