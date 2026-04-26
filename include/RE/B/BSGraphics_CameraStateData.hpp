#pragma once

#include "RE/B/BSGraphics_ViewData.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiCamera;
}

namespace RE::BSGraphics
{
	class CameraStateData
	{
	public:
		// members
		ViewData camViewData;		// 000
		NiPoint3 posAdjust;			// 210
		NiPoint3 currentPosAdjust;	// 21C
		NiPoint3 previousPosAdjust; // 228
		NiCamera* referenceCamera;	// 238
		bool useJitter;				// 240
	};
	static_assert(sizeof(CameraStateData) == 0x250);
}
