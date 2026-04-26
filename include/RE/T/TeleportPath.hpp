#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class ParentSpaceNode;
	class TeleportLink;

	class TeleportPath
	{
	public:
		GAME_HEAP_REDEFINE_NEW(TeleportPath);

		// members
		BSTArray<ParentSpaceNode> spaces; // 00
		BSTArray<TeleportLink> doors;	  // 18
		NiPoint3 startPos;				  // 30
		NiPoint3 endPos;				  // 3C
		bool worldMapOnly;				  // 48
	};
	static_assert(sizeof(TeleportPath) == 0x50);
}
