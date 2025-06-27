#include "components/ColorUtils.h"
#include "components/Header.h"
#include "components/ImageUtils.h"
#include "components/IntroBody.h"
#include "components/Fonts.h"
#include "components/LayoutUtils.h"
#include "engine/MemoryUtils.h"
#include "engine/ResourceLoader.h"
#include <cstddef>
#include <cstdint>
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "raylib.h"
#include "renderer/clay_renderer_raylib.c"
#include <cstdio>

constexpr int32_t INIT_WIDTH = 1080; 
constexpr int32_t INIT_HEIGHT = 720; 


void HandleClayErrors(Clay_ErrorData error) {
    printf("%s", error.errorText.chars);
}

void Update()
{
    Vector2 windowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    

    Clay_Vector2 mousePosition = {GetMousePosition().x, GetMousePosition().y};
    Clay_Vector2 mouseScroll = {GetMouseWheelMoveV().x, GetMouseWheelMoveV().y};
    if (mouseScroll.y != 0) {
        printf("MouseWheelV: (%.2f, %.2f)\n", mouseScroll.x, mouseScroll.y);
    }
    Clay_SetPointerState(mousePosition, IsMouseButtonDown(0));
    Clay_UpdateScrollContainers(true, mouseScroll, GetFrameTime());
    Clay_SetLayoutDimensions({.width = windowSize.x, .height = windowSize.y});
    Clay_BeginLayout();

    Clay_Color bgColor = ColorUtils::Black();
    
    CLAY({.id = CLAY_ID("MainContainer"), .layout = { .sizing = LayoutUtils::SizeAutoGrowXY(), .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = bgColor})
    {
        Components::Header(ImageUtils::g_imageResources.headerProfileIdx, ImageUtils::g_imageResources.githubLogoIdx, ImageUtils::g_imageResources.linkedInIdx, ImageUtils::g_imageResources.emailLogoIdx);
        Clay_ClipElementConfig scrollClipping = {
            .vertical = true,
            .childOffset = Clay_GetScrollOffset()
        };
        Clay_LayoutConfig scrollLayout = {
            .sizing = {
                .width = CLAY_SIZING_FIXED(900)
            }
        };
        CLAY({ .id = CLAY_ID("ScrollContainer"), .clip = scrollClipping }) {
            Components::IntroBody();
        }
    }
    
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    Clay_Raylib_Render(renderCommands, Fonts::g_fonts); // This nullptr should be a font ptr
    
    EndDrawing();
}

void LoadResources() {
    ImageUtils::g_imageResources.headerProfileIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/profile.jpg");
    ImageUtils::g_imageResources.githubLogoIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/github.png");
    ImageUtils::g_imageResources.emailLogoIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/email.png");
    ImageUtils::g_imageResources.linkedInIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/linkedin.png");
    ImageUtils::g_imageResources.hushImageIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/Hush.png");
    ImageUtils::g_imageResources.gripshotImageIdx = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/Gripshot.jpg");
    ResourceLoader::g_tilesIcon = ResourceLoader::g_resourceLoader.LoadImageIntoCache("assets/images/3DTiles.png");
    ResourceLoader::g_resourceLoader.InitializeFonts("assets/fonts/PlayfairDisplay.ttf", reinterpret_cast<Font*>(&Fonts::g_fonts), 1);
}

int main(void)
{
    uint32_t memorySize = Clay_MinMemorySize();
    Clay_Arena clayArena = Clay_CreateArenaWithCapacityAndMemory(memorySize, malloc(memorySize));
    MemoryUtils::g_frameArena = {
        .memory = new std::byte[1024],
        .offset = 0
    };
    
    
    Clay_Raylib_Initialize(INIT_WIDTH, INIT_HEIGHT, "Nef's professional showcase", FLAG_WINDOW_RESIZABLE);

    Clay_Initialize(clayArena, (Clay_Dimensions){INIT_WIDTH, INIT_HEIGHT}, (Clay_ErrorHandler){HandleClayErrors});

    LoadResources();

    // Clay_SetDebugModeEnabled(true);
    
    Clay_SetMeasureTextFunction(Raylib_MeasureText, Fonts::g_fonts);
    
    while (!WindowShouldClose()) {
        Update();
    }
    
    CloseWindow();
    free(clayArena.memory);
    return 0;
}
