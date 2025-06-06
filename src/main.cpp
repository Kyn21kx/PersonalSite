#include "components/ColorUtils.h"
#include "components/Header.h"
#include "components/LayoutUtils.h"
#include <cstdint>
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "raylib.h"
#include "renderer/clay_renderer_raylib.c"
#include <cstdio>

void HandleClayErrors(Clay_ErrorData error) {
    printf("%s", error.errorText.chars);
}

int main(void)
{
    uint32_t memorySize = Clay_MinMemorySize();
    Clay_Arena clayArena = Clay_CreateArenaWithCapacityAndMemory(memorySize, malloc(memorySize));
    
    
    Clay_Raylib_Initialize(1920, 1080, "Nef's professional showcase", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI );

    Clay_Initialize(clayArena, (Clay_Dimensions){1920, 1080}, (Clay_ErrorHandler){HandleClayErrors});

    Font f = LoadFont("assets/fonts/PlayfairDisplay.ttf");

    Clay_SetMeasureTextFunction(Raylib_MeasureText, &f);
    
    while (!WindowShouldClose())
    {
        Vector2 windowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
        
        Clay_SetLayoutDimensions({.width = windowSize.x, .height = windowSize.y});
        Clay_BeginLayout();

        CLAY({.id = CLAY_ID("MainContainer"), .layout = { .sizing = LayoutUtils::SizeAutoGrowXY(), .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = ColorUtils::LightGray()})
        {
            Components::Header();
        	CLAY_TEXT(CLAY_STRING("Hey there claaay"), CLAY_TEXT_CONFIG({ .textColor = ColorUtils::Black(), .fontId = 0, .fontSize = 24 }));
        }
        
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();
        Clay_Raylib_Render(renderCommands, &f); // This nullptr should be a font ptr
        
        EndDrawing();
    }
    
    CloseWindow();
    free(clayArena.memory);
    return 0;
}
