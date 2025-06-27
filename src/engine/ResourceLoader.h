#pragma once
// We're gonna go the route of modern C++ for this one, it does truly fit the problem

#include "raylib.h"
#include <cstddef>
#include <string_view>
#include <vector>

namespace ResourceLoader {
	class Loader {
	public:
		inline size_t LoadImageIntoCache(const std::string_view& path) {
			Image img = LoadImage(path.data());
			this->m_loadedImages.emplace_back(LoadTextureFromImage(img));
			UnloadImage(img);
			return this->m_loadedImages.size() - 1;
		}

		inline Texture2D* GetLoadedImage(size_t idx) {
			return &this->m_loadedImages.at(idx);
		}

		inline void InitializeFonts(const char* path, Font* outFonts, size_t count) {
        	for (size_t i = 0; i < count; i++) {
        	  outFonts[i] = LoadFontEx(path, (i + 1) * 72, 0, 0);        	  
              SetTextureFilter(outFonts[i].texture, TEXTURE_FILTER_POINT);
        	}
		}
	
	private:
		std::vector<Texture2D> m_loadedImages;
	};

	inline Loader g_resourceLoader;
	inline size_t g_tilesIcon;
}


