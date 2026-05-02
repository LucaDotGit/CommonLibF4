#pragma once

#include "RE/D/DetectionFormulaData.hpp"
#include "RE/D/DetectionLevels.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	enum class DETECTION_TYPE : std::int32_t;

	class DetectionData
		: public DetectionFormulaData // 00
	{
	public:
		// members
		NiPoint3 detectedLocation;							   // 74
		DetectionLevels detectionLevel;						   // 80
		REX::Enum<DETECTION_TYPE, std::int32_t> detectionType; // 84
	};
	static_assert(sizeof(DetectionData) == 0x88);
}
