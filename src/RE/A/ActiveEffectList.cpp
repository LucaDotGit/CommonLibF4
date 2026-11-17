#include "RE/A/ActiveEffectList.hpp"

#include "RE/A/ActiveEffect.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	auto ActiveEffectList::GetActiveEffectByID(std::uint16_t a_id) const -> BSTSmartPointer<ActiveEffect>
	{
		auto result = BSTSmartPointer<ActiveEffect>();
		ForEachActiveEffect(
			[&result,
			 a_id](const BSTSmartPointer<ActiveEffect>& a_activeEffect) noexcept -> BSContainer::ForEachResult {
				if (a_activeEffect && a_activeEffect->GetUniqueID() == a_id) {
					result = a_activeEffect;
					return BSContainer::ForEachResult::Stop;
				}

				return BSContainer::ForEachResult::Continue;
			});

		return result;
	}

	auto ActiveEffectList::ForEachActiveEffect(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const BSTSmartPointer<ActiveEffect>&)
													   const>>& a_predicate) const -> BSContainer::ForEachResult
	{
		const auto currentIterating = ++iterating;

		auto result = BSContainer::ForEachResult::Continue;
		for (const auto& activeEffect : activeEffects) {
			if (std::invoke(a_predicate.get(), activeEffect) == BSContainer::ForEachResult::Stop) {
				result = BSContainer::ForEachResult::Stop;
				break;
			}
		}

		iterating = currentIterating - 1;
		return result;
	}
}
