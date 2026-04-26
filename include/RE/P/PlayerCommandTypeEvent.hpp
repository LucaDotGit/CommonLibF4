#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t;

	class PlayerCommandTypeEvent
		: public BSTValueEvent<COMMAND_TYPE> // 00
	{
	public:
	};
	static_assert(sizeof(PlayerCommandTypeEvent) == 0x08);
}
