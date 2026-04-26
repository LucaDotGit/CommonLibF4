#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/M/MapMarkerSubCategories.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	enum class MARKER_TYPE : std::int32_t;
	enum class MarkerIconTypes : std::int32_t;
	enum class RelativeMarkerHeight : std::int32_t;

	class HUDMarkerData
	{
	public:
		// members
		ObjectRefHandle markerTarget;											// 00
		NiPoint3 markerLocation;												// 04
		NiPoint2 movieCoords;													// 10
		REX::Float32 heading;													// 18
		REX::Float32 distanceToPlayerSqr;										// 1C
		REX::Float32 markerDisplayDistance;										// 20
		REX::Enum<MarkerIconTypes, std::int32_t> markerIconType;				// 24
		REX::Enum<RelativeMarkerHeight, std::int32_t> relativeMarkerHeight;		// 28
		REX::Enum<MapMarkerSubCategories, std::int32_t> mapMarkerSubCategories; // 2C
		REX::Enum<MARKER_TYPE, std::int32_t> mapMarkerType;						// 30
		bool showFloatingQuestMarker;											// 34
		bool hostile;															// 35
	};
	static_assert(sizeof(HUDMarkerData) == 0x38);
}
