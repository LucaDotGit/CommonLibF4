#pragma once

namespace RE
{
	class VOICE_TYPE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			AllowDefaultDialogue = 1 << 0,
			Female = 1 << 1
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x00
	};

	static_assert(sizeof(VOICE_TYPE_DATA) == 0x01);
}
