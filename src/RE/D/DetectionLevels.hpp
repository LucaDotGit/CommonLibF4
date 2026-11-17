#pragma once

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;

	class DetectionLevels
	{
	public:
		// members
		std::int16_t visualLevel;						 // 0x00 - To-Do
		REX::Enum<SOUND_LEVEL, std::int16_t> soundLevel; // 0x02
	};

	static_assert(sizeof(DetectionLevels) == 0x04);
}
