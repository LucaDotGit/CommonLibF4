#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/M/MapMarkerSubCategories.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	enum class MARKER_TYPE : std::int32_t;
	enum class MarkerIconTypes : std::int32_t;
	enum class RelativeMarkerHeight : std::int32_t;

	class HUDMarkerData
	{
	public:
		// members
		ObjectRefHandle markerTarget;											// 0x00
		NiPoint3 markerLocation;												// 0x04
		NiPoint2 movieCoords;													// 0x10
		REX::Float32 heading;													// 0x18
		REX::Float32 distanceToPlayerSqr;										// 0x1C
		REX::Float32 markerDisplayDistance;										// 0x20
		REX::Enum<MarkerIconTypes, std::int32_t> markerIconType;				// 0x24
		REX::Enum<RelativeMarkerHeight, std::int32_t> relativeMarkerHeight;		// 0x28
		REX::Enum<MapMarkerSubCategories, std::int32_t> mapMarkerSubCategories; // 0x2C
		REX::Enum<MARKER_TYPE, std::int32_t> mapMarkerType;						// 0x30
		bool showFloatingQuestMarker;											// 0x34
		bool hostile;															// 0x35
	};

	static_assert(sizeof(HUDMarkerData) == 0x38);
}
