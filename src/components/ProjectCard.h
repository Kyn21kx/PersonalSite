#pragma once
#include "ColorUtils.h"
#include "clay.h"
#include <cstddef>
#include <cstdint>
#include "LayoutUtils.h"
#include "StringUtils.h"
#include "../engine/ResourceLoader.h"
#include "raylib.h"

constexpr uint32_t PROJECT_CARD_WIDTH = 300;

inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

inline void PopOut(Clay_Sizing* sizing, float* blendTimer) {
    constexpr float max = PROJECT_CARD_WIDTH * 1.3f;
    float minHeight = sizing->height.size.minMax.min;
    float minWidth = sizing->width.size.minMax.min;
    sizing->width = CLAY_SIZING_FIT(lerp(minWidth, max, *blendTimer));
    sizing->height = CLAY_SIZING_FIT(lerp(minHeight, max, *blendTimer));
}

inline void ProjectCard(size_t imageIdx, const std::string& title, const std::string& description, float* blendTimer) {
    Clay_Sizing sizing = {
        .width = CLAY_SIZING_GROW(1), // The 1 will act as a flexbox
        .height = { .type = CLAY__SIZING_TYPE_FIT}
    };
    
    Clay_Sizing imgSizing = { CLAY_SIZING_FIT(PROJECT_CARD_WIDTH), CLAY_SIZING_FIT(PROJECT_CARD_WIDTH) }; 
    Clay_String clayTitle = StringUtils::StrToClayString(title);
    Clay_String clayDesc = StringUtils::StrToClayString(description);

    CLAY({ .id = CLAY_IDI("ProjectCard", imageIdx), 
           .layout = { .sizing = sizing, .padding = CLAY_PADDING_ALL(12), 
                       .childGap = 24, .childAlignment = LayoutUtils::ChildAlignCenterAll(), 
                       .layoutDirection = CLAY_TOP_TO_BOTTOM }}) 
    {
        Texture2D* image = ResourceLoader::g_resourceLoader.GetLoadedImage(imageIdx);

        if (Clay_Hovered()) {
            *blendTimer = std::min((*blendTimer) + GetFrameTime() * 3, 1.0f);
        }
        else {
            *blendTimer = std::max((*blendTimer) - GetFrameTime() * 3, 0.0f);
        }
        
        PopOut(&imgSizing, blendTimer);
        
        Clay_LayoutConfig titleLayout = {
            .sizing = { imgSizing.width, CLAY_SIZING_FIT(0) },
            .childAlignment = LayoutUtils::ChildAlignCenterAll()
        };

        CLAY({ .id = CLAY_IDI("TitleContainer", imageIdx),
               .layout = titleLayout}) 
        {
            CLAY_TEXT(clayTitle, CLAY_TEXT_CONFIG({ 
                .fontId = 0, 
                .fontSize = 48,
                .textColor = ColorUtils::White(),
                .textAlignment = CLAY_TEXT_ALIGN_CENTER,
                .wrapMode = CLAY_TEXT_WRAP_WORDS // Ensure wrapping on spaces
            }));
        }

        CLAY({ .id = CLAY_IDI("CardImg", imageIdx), 
               .layout = { .sizing = { imgSizing } }, 
               .cornerRadius = CLAY_CORNER_RADIUS(200), 
               .aspectRatio = { 1 }, 
               .image = { .imageData = image }}) {}


        Clay_LayoutConfig descriptionLayout = {
            .sizing = {
                .width = CLAY_SIZING_FIT(PROJECT_CARD_WIDTH),
                .height = CLAY_SIZING_FIT(0)
            },
            .childAlignment = LayoutUtils::ChildAlignCenterAll()
        };
        CLAY({ .id = CLAY_IDI("DescContainer", imageIdx), .layout = descriptionLayout }) 
        {
            CLAY_TEXT(clayDesc, CLAY_TEXT_CONFIG({ 
                .fontId = 0, 
                .fontSize = 32, 
                .textColor = ColorUtils::White(),
                .wrapMode = CLAY_TEXT_WRAP_WORDS
            }));
        }
    }
}


