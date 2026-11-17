#pragma once

#include "RE/T/TESFullName.hpp"

namespace RE
{
	enum class MARKER_TYPE : std::int32_t;

	class MapMarkerData
	{
	public:
		enum class Flags : std::uint8_t; // To-Do

		// members
		TESFullName locationName;						 // 0x00
		REX::EnumSet<Flags, std::uint8_t> flags;		 // 0x10
		REX::EnumSet<Flags, std::uint8_t> originalFlags; // 0x11
		REX::Enum<MARKER_TYPE, std::int16_t> type;		 // 0x12
	};

	static_assert(sizeof(MapMarkerData) == 0x18);
}
