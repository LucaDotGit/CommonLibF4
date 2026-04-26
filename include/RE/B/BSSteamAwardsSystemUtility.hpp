#pragma once

#include "RE/B/BSAwardsSystemUtility.hpp"

namespace RE
{
	class __declspec(novtable) BSSteamAwardsSystemUtility
		: public BSAwardsSystemUtility // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSSteamAwardsSystemUtility };
		inline static constexpr auto VTABLE{ VTABLE::BSSteamAwardsSystemUtility };

		virtual ~BSSteamAwardsSystemUtility() = default; // 00
	};
	static_assert(sizeof(BSSteamAwardsSystemUtility) == 0x08);
}
