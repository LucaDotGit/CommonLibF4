#pragma once

#include "RE/N/NiPoint2.hpp"

namespace RE
{
	class MeanderSettingsData
	{
	public:
		enum MeanderType : std::int32_t
		{
			None = 0,
			StartLeft = 1,
			StartRight = 2
		};

		// members
		REX::Enum<MeanderType, std::int32_t> type; // 0x00
		NiPoint2 amplitudeRange;				   // 0x04
		NiPoint2 wavelengthRange;				   // 0x0C
	};

	static_assert(sizeof(MeanderSettingsData) == 0x14);
}
