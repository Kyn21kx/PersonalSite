#pragma once
#include "clay.h"
#include <cstddef>

namespace MemoryUtils {
	
	typedef struct {
	    std::byte* memory;
	    uintptr_t offset;
	} Arena;

	inline Arena g_frameArena = {};
	
	// From Clay examples
	inline Clay_String* FrameAllocateString(Clay_String string, Arena frameArena) {
	    Clay_String *allocated = (Clay_String *)(frameArena.memory + frameArena.offset);
	    *allocated = string;
	    frameArena.offset += sizeof(Clay_String);
	    return allocated;
	}	

	
}
