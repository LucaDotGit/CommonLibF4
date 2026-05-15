#include "RE/A/ActiveEffectList.hpp"

#include "RE/A/ActiveEffect.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	[[nodiscard]] BSTSmartPointer<ActiveEffect> ActiveEffectList::GetActiveEffectByID(std::uint16_t a_id) const
	{
		auto result = BSTSmartPointer<ActiveEffect>();
		ForEachActiveEffect([&result, a_id](const BSTSmartPointer<ActiveEffect>& a_activeEffect) -> BSContainer::ForEachResult {
			if (a_activeEffect && a_activeEffect->GetUniqueID() == a_id) {
				result = a_activeEffect;
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	BSContainer::ForEachResult ActiveEffectList::ForEachActiveEffect(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const BSTSmartPointer<ActiveEffect>&)>>& a_predicate) const
	{
		const auto currentIterating = ++iterating;

		auto result = BSContainer::ForEachResult::kContinue;
		for (const auto& activeEffect : activeEffects) {
			if (std::invoke(*a_predicate, activeEffect) == BSContainer::ForEachResult::kStop) {
				result = BSContainer::ForEachResult::kStop;
				break;
			}
		}

		iterating = currentIterating - 1;
		return result;
	}
}
