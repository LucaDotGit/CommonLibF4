#pragma once

namespace RE
{
	class VOICE_TYPE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kAllowDefaultDialogue = 1 << 0,
			kFemale = 1 << 1
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 00
	};
	static_assert(sizeof(VOICE_TYPE_DATA) == 0x01);
}
