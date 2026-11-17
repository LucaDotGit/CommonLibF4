#include "RE/B/BGSCharacterTint_Template_Groups.hpp"

#include "RE/B/BGSCharacterTint_Template_Group.hpp"

namespace RE::BGSCharacterTint::Template
{
	auto Groups::GetGroupByID(std::uint32_t a_id) noexcept -> Group*
	{
		const auto* groupIt = std::ranges::find_if(groups, [a_id](const Group* a_group) noexcept -> bool {
			return a_group && a_group->id == a_id;
		});

		if (groupIt == groups.end()) {
			return nullptr;
		}

		return *groupIt;
	}

	auto Groups::GetGroupByID(std::uint32_t a_id) const noexcept -> const Group*
	{
		const auto* groupIt = std::ranges::find_if(groups, [a_id](const Group* a_group) noexcept -> bool {
			return a_group && a_group->id == a_id;
		});

		if (groupIt == groups.end()) {
			return nullptr;
		}

		return *groupIt;
	}
}
