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
		void* handleList;				  // 00 - TODO: `BSModelDB::HandleListHead`
		NiPointer<NiAVObject> data3D;	  // 08
		TESWaterForm* currentWaterType;	  // 10
		REX::Float32 relevantWaterHeight; // 18
		REX::Float32 cachedRadius;		  // 1C
		std::uint16_t flags;			  // 20
		std::int16_t underwaterCount;	  // 22
	};
	static_assert(sizeof(LOADED_REF_DATA) == 0x28);
}
