#pragma once

namespace RE
{
	class ActorStance
	{
	public:
		// members
		std::uint8_t stance;		 // 0x00
		std::uint8_t stanceModifier; // 0x01
		bool mirrored;				 // 0x02
	};

	static_assert(sizeof(ActorStance) == 0x03);
}
