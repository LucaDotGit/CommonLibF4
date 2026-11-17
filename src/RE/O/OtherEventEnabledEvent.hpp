#pragma once

namespace RE::UserEvents
{
	enum class SENDER_ID : std::int32_t;
}

namespace RE::OtherInputEvents
{
	enum class OTHER_EVENT_FLAG : std::uint32_t;
}

namespace RE
{
	class OtherEventEnabledEvent
	{
	public:
		// members
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> newOtherEventFlag; // 0x00
		REX::EnumSet<OtherInputEvents::OTHER_EVENT_FLAG, std::uint32_t> oldOtherEventFlag; // 0x04
		REX::Enum<UserEvents::SENDER_ID, std::int32_t> senderID;						   // 0x08
	};

	static_assert(sizeof(OtherEventEnabledEvent) == 0x0C);
}
