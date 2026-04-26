#pragma once

#include "RE/T/TESFullName.hpp"

namespace RE
{
	enum class MARKER_TYPE : std::int32_t;

	class MapMarkerData
	{
	public:
		enum class Flags : std::uint8_t; // TODO

		// members
		TESFullName locationName;						 // 00
		REX::EnumSet<Flags, std::uint8_t> flags;		 // 10
		REX::EnumSet<Flags, std::uint8_t> originalFlags; // 11
		REX::Enum<MARKER_TYPE, std::int16_t> type;		 // 12
	};
	static_assert(sizeof(MapMarkerData) == 0x18);
}
