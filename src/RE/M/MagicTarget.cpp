#include "RE/M/MagicTarget.hpp"

#include "RE/A/ActiveEffect.hpp"
#include "RE/A/ActiveEffectList.hpp"

namespace RE
{
	bool MagicTarget::IsTakingHealthDamageFromActiveEffect() const
	{
		using FuncType = decltype(&MagicTarget::IsTakingHealthDamageFromActiveEffect);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MagicTarget::IsTakingHealthDamageFromActiveEffect };
		return std::invoke(FUNC, this);
	}

	bool MagicTarget::IsTakingRadDamageFromActiveEffect() const
	{
		using FuncType = decltype(&MagicTarget::IsTakingRadDamageFromActiveEffect);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MagicTarget::IsTakingRadDamageFromActiveEffect };
		return std::invoke(FUNC, this);
	}

	BSTSmartPointer<ActiveEffect> MagicTarget::GetActiveEffectByID(std::uint16_t a_id) const
	{
		const auto* activeEffectList = const_cast<MagicTarget*>(this)->GetActiveEffectList();
		if (!activeEffectList) {
			return nullptr;
		}

		return activeEffectList->GetActiveEffectByID(a_id);
	}
}
