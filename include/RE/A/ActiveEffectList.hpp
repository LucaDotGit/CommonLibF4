#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class ActiveEffectList
	{
	public:
		GAME_HEAP_REDEFINE_NEW(ActiveEffectList);

		[[nodiscard]] BSTSmartPointer<ActiveEffect> GetActiveEffectByID(std::uint16_t a_id) const;

		BSContainer::ForEachResult ForEachActiveEffect(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const BSTSmartPointer<ActiveEffect>&)>>& a_predicate) const;

		// members
		BSTArray<BSTSmartPointer<ActiveEffect>> activeEffects; // 00
		mutable std::uint8_t iterating;						   // 18 - In Skyrim VR, this is used as some kind of spin lock, but it seems to be unused in FO4.
	};
	static_assert(sizeof(ActiveEffectList) == 0x20);
}
