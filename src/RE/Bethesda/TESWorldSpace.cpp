#include "RE/Bethesda/TESWorldSpace.hpp"

#include "RE/Bethesda/TESWaterForm.hpp"

namespace RE
{
	TESWaterForm* TESWorldSpace::GetWaterType() const noexcept
	{
		auto root = this;
		for (auto iter = root; iter; iter = iter->GetParentWorld(PARENT_USE_FLAGS::kWater)) {
			root = iter;
		}

		if (root->worldWater) {
			return root->worldWater;
		}
		else {
			return TESWaterForm::GetDefaultWater();
		}
	}

	TESClimate* TESWorldSpace::GetClimate() const noexcept
	{
		auto root = this;
		for (auto iter = root; iter; iter = iter->GetParentWorld(PARENT_USE_FLAGS::kClimate)) {
			root = iter;
		}

		return root->climate;
	}

	TESObjectCELL* TESWorldSpace::GetSkyCell() const noexcept
	{
		auto root = this;
		for (auto iter = root; iter; iter = iter->GetParentWorld(PARENT_USE_FLAGS::kSkyCell)) {
			root = iter;
		}

		return root->skyCell;
	}
}
