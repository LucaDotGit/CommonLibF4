#pragma once

namespace RE
{
	class QUEST_STAGE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			Done = 1 << 0,
			StartUp = 1 << 1,
			ShutDown = 1 << 2,
			KeepInstance = 1 << 3
		};

		// members
		std::uint16_t index;					 // 0x00
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x02
	};

	static_assert(sizeof(QUEST_STAGE_DATA) == 0x04);
}
