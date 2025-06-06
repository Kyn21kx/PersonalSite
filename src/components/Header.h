#pragma once
#include "Buttons.h"
#include "ColorUtils.h"
#include "StringUtils.h"
#include "TextUtils.h"
#include "clay.h"
#include "raylib.h"
#include <cstdint>
#include <string>

namespace Components {
    inline void Header() {
        // Create a container that grows automatically on the x axis
        Clay_Sizing sizing = {
            .width = CLAY_SIZING_GROW(0),
            .height = { .type = CLAY__SIZING_TYPE_FIT}
        };
        CLAY(
            { .id = CLAY_ID("Header"), .layout = { .sizing = sizing, .layoutDirection = CLAY_LEFT_TO_RIGHT }, .backgroundColor = ColorUtils::Black()}
        ) {
            CLAY({.layout = { .layoutDirection = CLAY_TOP_TO_BOTTOM}}) {
                CLAY_TEXT(CLAY_STRING("Leonidas Neftali (Kyn21kx)"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
                CLAY_TEXT(CLAY_STRING("Game Engine & Software Developer"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
            }
            // Some spacing or maybe a flexbox
            Buttons::ButtonComponent(CLAY_STRING("Test change"));
            // std::string timeStr = "Current time: ";
            // timeStr += std::to_string(static_cast<int32_t>(GetTime()));
            // Clay_String str = StringUtils::FromCString(timeStr.c_str(), timeStr.size());
            // CLAY_TEXT(str, CLAY_TEXT_CONFIG(TextUtils::Default(32)));
        }  
    }
}

