#include "components/ColorUtils.h"
#include "components/Header.h"
#include "components/LayoutUtils.h"
#include <cstdint>
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "raylib.h"
#include "renderer/clay_renderer_raylib.c"
#include <cstdio>

constexpr int32_t INIT_WIDTH = 3840; 
constexpr int32_t INIT_HEIGHT = 2160; 

void HandleClayErrors(Clay_ErrorData error) {
    printf("%s", error.errorText.chars);
}

void Update(Font* fonts) 
{
    Vector2 windowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    

    Clay_Vector2 mousePosition = {GetMousePosition().x, GetMousePosition().y};
    Clay_SetPointerState(mousePosition, IsMouseButtonDown(0));    
    Clay_SetLayoutDimensions({.width = windowSize.x, .height = windowSize.y});
    Clay_BeginLayout();

    CLAY({.id = CLAY_ID("MainContainer"), .layout = { .sizing = LayoutUtils::SizeAutoGrowXY(), .layoutDirection = CLAY_TOP_TO_BOTTOM }, .backgroundColor = {23, 23, 23, 255}})
    {
        Components::Header();
    	// CLAY_TEXT(CLAY_STRING("Hey there claaay"), CLAY_TEXT_CONFIG({ .textColor = ColorUtils::Black(), .fontId = 0, .fontSize = 24 }));
    }
    
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    Clay_Raylib_Render(renderCommands, fonts); // This nullptr should be a font ptr
    
    EndDrawing();
}

int main(void)
{
    uint32_t memorySize = Clay_MinMemorySize();
    Clay_Arena clayArena = Clay_CreateArenaWithCapacityAndMemory(memorySize, malloc(memorySize));
    
    
    Clay_Raylib_Initialize(INIT_WIDTH, INIT_HEIGHT, "Nef's professional showcase", FLAG_WINDOW_RESIZABLE);

    Clay_Initialize(clayArena, (Clay_Dimensions){INIT_WIDTH, INIT_HEIGHT}, (Clay_ErrorHandler){HandleClayErrors});

    Font f = LoadFont("assets/fonts/PlayfairDisplay.ttf");

    Clay_SetMeasureTextFunction(Raylib_MeasureText, &f);
    
    while (!WindowShouldClose()) {
        Update(&f);
    }
    
    CloseWindow();
    free(clayArena.memory);
    return 0;
}
