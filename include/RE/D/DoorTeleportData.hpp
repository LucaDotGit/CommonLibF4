#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class DoorTeleportData
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNoAlarm = 0,
			kInstant = 1 << 0,
			kRelative = 1 << 2
		};

		GAME_HEAP_REDEFINE_NEW(DoorTeleportData);

		// members
		TESObjectCELL* transitionCell;			 // 00
		ObjectRefHandle linkedDoor;				 // 08
		NiPoint3 position;						 // 0C
		NiPoint3 rotation;						 // 18
		REX::EnumSet<Flags, std::uint8_t> flags; // 24
	};
	static_assert(sizeof(DoorTeleportData) == 0x28);
}
