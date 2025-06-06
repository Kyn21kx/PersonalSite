#pragma once
#include "clay.h"

namespace LayoutUtils {
	inline Clay_Sizing SizeAutoGrowXY() {
		return Clay_Sizing { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() };
	}
}


