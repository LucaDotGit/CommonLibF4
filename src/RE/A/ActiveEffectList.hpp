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

		[[nodiscard]]
		auto GetActiveEffectByID(std::uint16_t a_id) const -> BSTSmartPointer<ActiveEffect>;

		auto ForEachActiveEffect(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const BSTSmartPointer<ActiveEffect>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		// members
		BSTArray<BSTSmartPointer<ActiveEffect>> activeEffects; // 0x00
		mutable std::uint8_t
			iterating; // 0x18 - In Skyrim VR, this is used as some kind of spin lock, but it seems to be unused in FO4.
	};

	static_assert(sizeof(ActiveEffectList) == 0x20);
}
