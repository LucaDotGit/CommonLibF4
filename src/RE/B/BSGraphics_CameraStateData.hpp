#pragma once

#include "RE/B/BSGraphics_ViewData.hpp"
#include "RE/N/NiPoint3.hpp"

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
		ViewData camViewData;		// 0x000
		NiPoint3 posAdjust;			// 0x210
		NiPoint3 currentPosAdjust;	// 0x21C
		NiPoint3 previousPosAdjust; // 0x228
		NiCamera* referenceCamera;	// 0x238
		bool useJitter;				// 0x240
	};

	static_assert(sizeof(CameraStateData) == 0x250);
}
