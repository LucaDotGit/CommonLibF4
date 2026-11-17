#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class LOADED_REF_DATA
	{
	public:
		GAME_HEAP_REDEFINE_NEW(LOADED_REF_DATA);

		// members
		void* handleList;				  // 0x00 - To-Do: `BSModelDB::HandleListHead`
		NiPointer<NiAVObject> data3D;	  // 0x08
		TESWaterForm* currentWaterType;	  // 0x10
		REX::Float32 relevantWaterHeight; // 0x18
		REX::Float32 cachedRadius;		  // 0x1C
		std::uint16_t flags;			  // 0x20
		std::int16_t underwaterCount;	  // 0x22
	};

	static_assert(sizeof(LOADED_REF_DATA) == 0x28);
}
