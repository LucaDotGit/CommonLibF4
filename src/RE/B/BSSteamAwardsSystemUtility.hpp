#pragma once

#include "RE/B/BSAwardsSystemUtility.hpp"

namespace RE
{
	class __declspec(novtable) BSSteamAwardsSystemUtility : public BSAwardsSystemUtility // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSSteamAwardsSystemUtility;
		inline static constexpr const auto& VTABLE = VTABLE::BSSteamAwardsSystemUtility;

		~BSSteamAwardsSystemUtility() override = default; // 0x00
	};

	static_assert(sizeof(BSSteamAwardsSystemUtility) == 0x08);
}
