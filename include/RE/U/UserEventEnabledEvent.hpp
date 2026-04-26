#pragma once

namespace RE::UserEvents
{
	enum class SENDER_ID : std::int32_t;
	enum class USER_EVENT_FLAG : std::uint32_t;
}

namespace RE
{
	class UserEventEnabledEvent
	{
	public:
		// members
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> newUserEventFlag; // 00
		REX::EnumSet<UserEvents::USER_EVENT_FLAG, std::uint32_t> oldUserEventFlag; // 04
		REX::Enum<UserEvents::SENDER_ID, std::int32_t> senderID;				   // 08
	};
	static_assert(sizeof(UserEventEnabledEvent) == 0x0C);
}
