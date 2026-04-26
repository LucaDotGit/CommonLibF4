#pragma once

#include "RE/B/BSTOptional.hpp"
#include "RE/V/ViewCasterData.hpp"

namespace RE
{
	enum class ACTOR_LIFE_STATE : std::uint32_t;

	class ViewCasterUpdateData
	{
	public:
		// members
		ViewCasterData data;													// 00
		bool playerActivateable;												// 28
		BSTOptional<REX::Enum<ACTOR_LIFE_STATE, std::uint32_t>> actorLifeState; // 2C
	};
	static_assert(sizeof(ViewCasterUpdateData) == 0x38);
}
