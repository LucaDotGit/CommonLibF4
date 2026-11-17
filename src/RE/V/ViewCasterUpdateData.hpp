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
		ViewCasterData data;													// 0x00
		bool playerActivateable;												// 0x28
		BSTOptional<REX::Enum<ACTOR_LIFE_STATE, std::uint32_t>> actorLifeState; // 0x2C
	};

	static_assert(sizeof(ViewCasterUpdateData) == 0x38);
}
