#pragma once

namespace RE
{
	class QUEST_STAGE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kDone = 1 << 0,
			kStartUp = 1 << 1,
			kShutDown = 1 << 2,
			kKeepInstance = 1 << 3
		};

		// members
		std::uint16_t index;					 // 00
		REX::EnumSet<Flags, std::uint8_t> flags; // 02
	};
	static_assert(sizeof(QUEST_STAGE_DATA) == 0x04);
}
