#pragma once
#include "ColorUtils.h"
#include "TextUtils.h"
#include "clay.h"
#include <cstdio>

namespace Buttons {
	
	inline void RawButton(Clay_String buttonText, Clay_Color color, Clay_Color hoveredColor) {
		CLAY({ .layout = { .padding = CLAY_PADDING_ALL(18) }, .backgroundColor = Clay_Hovered() ?  color : hoveredColor}) {
	        CLAY_TEXT(buttonText, CLAY_TEXT_CONFIG(TextUtils::Default(24, Clay_Hovered() ? ColorUtils::White() : ColorUtils::LightGray())));
	    }
		
	}
	
	inline void HeaderButton(Clay_String buttonText) {
	    // Red box button with 8px of padding
	    RawButton(buttonText, ColorUtils::Transparent(), ColorUtils::Transparent());    
	}
}
