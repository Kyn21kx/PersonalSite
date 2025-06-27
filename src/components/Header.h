#pragma once
#include "Buttons.h"
#include "../engine/StateManager.h"
#include "../engine/ResourceLoader.h"
#include "../engine/MemoryUtils.h"
#include "../Models/Pages.h"
#include "ColorUtils.h"
#include "LayoutUtils.h"
#include "TextUtils.h"
#include "clay.h"
#include "raylib.h"

namespace Components {
    // This will only scroll down to the projects section, hopefully that's straightfoward
    inline void OnProjectsClick(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
        if (pointerData.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME) return;
        StateManager::g_currentPage = EPages::Projects;
    }

    inline void OnHomeClick(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
        if (pointerData.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME) return;
        StateManager::g_currentPage = EPages::Home;
    }

    inline void OnBlogClick(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
        if (pointerData.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME) return;
        StateManager::g_currentPage = EPages::Blog;
    }
    
    inline void OnContactClick(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
        if (pointerData.state != CLAY_POINTER_DATA_PRESSED_THIS_FRAME) return;
        StateManager::g_currentPage = EPages::Contact;
    }
    
    inline void HeaderPicture(size_t pictureId, Clay_Sizing sizing = { CLAY_SIZING_FIT(100), CLAY_SIZING_FIT(100) }) {
        // A Circular container with an image
        Texture2D* image = ResourceLoader::g_resourceLoader.GetLoadedImage(pictureId);
        CLAY({ .id = CLAY_IDI("Profile", pictureId), .layout = { .sizing = { sizing } }, .cornerRadius = CLAY_CORNER_RADIUS(200), .aspectRatio = { 1 }, .image = { .imageData = image}}) {}
    }
    
    inline void Header(size_t headerProfilePictureIdx, size_t githubImage, size_t linkedInImage, size_t emailImage) {
        // Create a container that grows automatically on the x axis
        Clay_Sizing sizing = {
            .width = CLAY_SIZING_GROW(0),
            .height = { .type = CLAY__SIZING_TYPE_FIT}
        };
        Clay_Color bgColor = ColorUtils::Green();
        CLAY({ .id = CLAY_ID("Header"), .layout = { .sizing = sizing, .padding = CLAY_PADDING_ALL(12), .childGap = 24, .childAlignment = LayoutUtils::ChildAlignCenterY(), .layoutDirection = CLAY_LEFT_TO_RIGHT}, .backgroundColor = bgColor}) {
            CLAY({.layout = { .sizing = LayoutUtils::SizeFlexHorizontal(1), .childGap = 24, .layoutDirection = CLAY_LEFT_TO_RIGHT }}) {
                HeaderPicture(headerProfilePictureIdx);
                CLAY({.layout = { .sizing = LayoutUtils::SizeAutoGrowXY(), .layoutDirection = CLAY_TOP_TO_BOTTOM }}) {
                    CLAY_TEXT(CLAY_STRING("Leonidas Neftali (Kyn21kx)"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
                    CLAY_TEXT(CLAY_STRING("- Game Engine Developer"), CLAY_TEXT_CONFIG(TextUtils::Default(24)));
                    CLAY_TEXT(CLAY_STRING("- Fullstack Software Engineer"), CLAY_TEXT_CONFIG(TextUtils::Default(24)));
                }
            }
            // Some spacing or maybe a flexbox
            CLAY({ .id = { CLAY_ID("ButtonsHeader") }, .layout = { .sizing = LayoutUtils::SizeFlexHorizontal(1), .childAlignment = LayoutUtils::ChildAlignCenterAll() } , .backgroundColor = ColorUtils::White(50), .cornerRadius = CLAY_CORNER_RADIUS(65) }) {
                Buttons::HeaderButton(CLAY_STRING("Home"), { .fontSize = 32, .active = StateManager::g_currentPage == EPages::Home, .onClick = OnHomeClick});
                Buttons::HeaderButton(CLAY_STRING("Projects"), { .fontSize = 32, .active = StateManager::g_currentPage == EPages::Projects, .onClick = OnProjectsClick });
                Buttons::HeaderButton(CLAY_STRING("Blog"), { .fontSize = 32, .active = StateManager::g_currentPage == EPages::Blog,  .onClick = OnBlogClick});
                Buttons::HeaderButton(CLAY_STRING("Contact"), { .fontSize = 32, .active = StateManager::g_currentPage == EPages::Contact,  .onClick = OnContactClick});
            }
            CLAY({ .id = { CLAY_ID("RightHeader")}, .layout = { .layoutDirection = CLAY_TOP_TO_BOTTOM, .childGap = 12, .sizing = LayoutUtils::SizeFlexHorizontal(1), .childAlignment = LayoutUtils::ChildAlignRightX() } }) {
                CLAY_TEXT(CLAY_STRING("Where to find me"), CLAY_TEXT_CONFIG(TextUtils::Default(32)));
                CLAY({.id = CLAY_ID("SocialsContainer"), .layout = { .childGap = 12, .layoutDirection = CLAY_LEFT_TO_RIGHT }}) {
                    Clay_Sizing sizing = { CLAY_SIZING_FIT(50), CLAY_SIZING_FIT(50) };
                    HeaderPicture(githubImage, sizing);
                    HeaderPicture(emailImage, sizing);
                    HeaderPicture(linkedInImage, sizing);
                }
            }
        }  
    }
}

