#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class ParentSpaceNode;
	class TeleportLink;

	class TeleportPath
	{
	public:
		GAME_HEAP_REDEFINE_NEW(TeleportPath);

		// members
		BSTArray<ParentSpaceNode> spaces; // 0x00
		BSTArray<TeleportLink> doors;	  // 0x18
		NiPoint3 startPos;				  // 0x30
		NiPoint3 endPos;				  // 0x3C
		bool worldMapOnly;				  // 0x48
	};

	static_assert(sizeof(TeleportPath) == 0x50);
}
