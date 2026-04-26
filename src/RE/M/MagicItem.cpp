#include "RE/M/MagicItem.hpp"

#include "RE/E/EffectItem.hpp"

namespace RE
{
	void MagicItem::SetEffects(std::span<std::unique_ptr<EffectItem>> a_effects)
	{
		ClearEffects();

		for (auto& effect : a_effects) {
			if (!effect) {
				continue;
			}

			listOfEffects.push_back(effect.release());
		}
	}

	void MagicItem::ClearEffects()
	{
		for (auto*& effect : listOfEffects) {
			if (!effect) {
				continue;
			}

			delete effect;
			effect = nullptr;
		}

		listOfEffects.clear();
	}
}
