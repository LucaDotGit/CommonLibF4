#pragma once

#include "RE/D/DetectionFormulaData.hpp"
#include "RE/D/DetectionLevels.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	enum class DETECTION_TYPE : std::int32_t;

	class DetectionData : public DetectionFormulaData // 0x00
	{
	public:
		// members
		NiPoint3 detectedLocation;							   // 0x74
		DetectionLevels detectionLevel;						   // 0x80
		REX::Enum<DETECTION_TYPE, std::int32_t> detectionType; // 0x84
	};

	static_assert(sizeof(DetectionData) == 0x88);
}
