#pragma once
#include "ImageUtils.h"
#include "ProjectCard.h"
#include "clay.h"
#include "LayoutUtils.h"
#include "TextUtils.h"

namespace Components {
	const std::string TILES_TITLE = "3D Tiles For Godot";
	const std::string TILES_DESC = "A Godot extension made in C++ to render 3D tiles that allow you to build 1:1 scale virtual replicas of the real world using geospatial data";
	const std::string HUSH_TITLE = "Hush Engine";
	const std::string HUSH_DESC = "Hush is a 3D and 2D game engine designed from the ground up for swift development and scalable projects. It delivers a user-friendly, versatile, and high-performance platform, offering a fast and responsive interface for game design without compromising resource efficiency.";
	const std::string GRIPSHOT_TITLE = "Gripshot";
	const std::string GRIPSHOT_DESC = "Multiplayer First Person Arena Shooter with physics grapling movement mechanics";

	inline float tilesAnimationBlend = 0.f;
	inline float hushAnimationBlend = 0.f;
	inline float gripshotAnimationBlend = 0.f;

	inline void PopularProjects() {
		Clay_Sizing sizing = {
            .width = CLAY_SIZING_GROW(0),
            .height = { .type = CLAY__SIZING_TYPE_FIT}
        };

		Clay_LayoutConfig layout = {
			.layoutDirection = CLAY_LEFT_TO_RIGHT,
			.sizing = sizing,
			.padding = CLAY_PADDING_ALL(72)
		};
		CLAY({ .id = CLAY_ID("ProjectsContainer"), .layout = layout }) {
			ProjectCard(ResourceLoader::g_tilesIcon, TILES_TITLE, TILES_DESC, &tilesAnimationBlend);
			ProjectCard(ImageUtils::g_imageResources.hushImageIdx, HUSH_TITLE, HUSH_DESC, &hushAnimationBlend);
			// ProjectCard(ImageUtils::g_imageResources.gripshotImageIdx, GRIPSHOT_TITLE, GRIPSHOT_DESC, &gripshotAnimationBlend);
		}
	}
	
	inline void WorkExperience() {
		CLAY_TEXT(CLAY_STRING("Professional Background"), CLAY_TEXT_CONFIG(TextUtils::Default(72)));
	}
	
	inline void IntroBody() {
		Clay_Sizing sizing = {
	        .width = CLAY_SIZING_GROW(0),
	        .height = { .type = CLAY__SIZING_TYPE_FIT}
	    };
	    // Clay_Color bgColor = ColorUtils::Black();
	    CLAY({ .id = CLAY_ID("IntroBody"), .layout = { .sizing = sizing, .childGap = 24, .childAlignment = LayoutUtils::ChildAlignCenterAll(), .layoutDirection = CLAY_TOP_TO_BOTTOM}}) {
            CLAY_TEXT(CLAY_STRING("Hi! My name is Nef"), CLAY_TEXT_CONFIG(TextUtils::Default(72)));
            CLAY_TEXT(CLAY_STRING("Systems Engineer with experience in the gaming industry and a focus on performance effective software"), CLAY_TEXT_CONFIG(TextUtils::Default(48)));
	        PopularProjects();
	        WorkExperience();
	    }
    }
}

