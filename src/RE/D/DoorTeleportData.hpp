#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class DoorTeleportData
	{
	public:
		inline static constexpr auto DEFAULT_POINT = NiPoint3(
			static_cast<REX::Float32>(999.0),
			static_cast<REX::Float32>(999.0),
			static_cast<REX::Float32>(999.0));

		enum class Flags : std::uint8_t
		{
			NoAlarm = 0,
			Instant = 1 << 0,
			Relative = 1 << 2
		};

		GAME_HEAP_REDEFINE_NEW(DoorTeleportData);

		// members
		TESObjectCELL* transitionCell;			 // 0x00
		ObjectRefHandle linkedDoor;				 // 0x08
		NiPoint3 position;						 // 0x0C
		NiPoint3 rotation;						 // 0x18
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x24
	};

	static_assert(sizeof(DoorTeleportData) == 0x28);
}
