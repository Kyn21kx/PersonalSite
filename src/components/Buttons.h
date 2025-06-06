#pragma once
#include "ColorUtils.h"
#include "TextUtils.h"
#include "clay.h"

namespace Buttons {
	
	void ButtonComponent(Clay_String buttonText) {
	    // Red box button with 8px of padding
	    CLAY({ .layout = { .padding = CLAY_PADDING_ALL(8) }, .backgroundColor = ColorUtils::White(100) }) {
	    	Clay_Color color = Clay_Hovered() ? ColorUtils::Red() : ColorUtils::White();
	        CLAY_TEXT(buttonText, CLAY_TEXT_CONFIG(TextUtils::Default(18, color)));
	    }
	}
}
