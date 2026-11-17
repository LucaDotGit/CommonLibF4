#pragma once

#include "RE/P/PlayerAmmoCountEvent.hpp"

namespace RE
{
	enum class ExplosiveAmmoType : std::int32_t;

	class HUDAmmoCountModel
	{
	public:
		// members
		BSTValueEventSource<PlayerAmmoCountEvent> nextAmmoCount;  // 0x00
		std::uint32_t explosiveCount;							  // 0x20
		REX::Enum<ExplosiveAmmoType, std::int32_t> explosiveType; // 0x24
	};

	static_assert(sizeof(HUDAmmoCountModel) == 0x28);
}
