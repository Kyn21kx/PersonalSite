#pragma once
#include "Buttons.h"
#include "ColorUtils.h"
#include "LayoutUtils.h"
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
        CLAY({ .id = CLAY_ID("Header"), .layout = { .sizing = sizing, .padding = CLAY_PADDING_ALL(12), .childGap = 24, .childAlignment = LayoutUtils::ChildAlignCenterY(), .layoutDirection = CLAY_LEFT_TO_RIGHT}, .backgroundColor = ColorUtils::Black()}) {
            CLAY({.layout = { .sizing = LayoutUtils::SizeFlexHorizontal(1), .layoutDirection = CLAY_TOP_TO_BOTTOM }}) {
                CLAY_TEXT(CLAY_STRING("Leonidas Neftali (Kyn21kx)"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
                CLAY_TEXT(CLAY_STRING("Game Engine & Software Developer"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
            }
            // Some spacing or maybe a flexbox
            CLAY({ .id = { CLAY_ID("ButtonsHeader") }, .layout = { .sizing = LayoutUtils::SizeFlexHorizontal(1), .childAlignment = LayoutUtils::ChildAlignCenterAll() } , .backgroundColor = ColorUtils::White(50), .cornerRadius = CLAY_CORNER_RADIUS(65) }) {
                Buttons::HeaderButton(CLAY_STRING("Home"));
                Buttons::HeaderButton(CLAY_STRING("Projects"));
                Buttons::HeaderButton(CLAY_STRING("Blog"));
                Buttons::HeaderButton(CLAY_STRING("Contact"));
            }
            CLAY({ .id = { CLAY_ID("RightHeader")}, .layout = { .sizing = LayoutUtils::SizeFlexHorizontal(1), .childAlignment = LayoutUtils::ChildAlignRightX() } }) {
                CLAY_TEXT(CLAY_STRING("GitHub Profile"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
            }
        }  
    }
}

