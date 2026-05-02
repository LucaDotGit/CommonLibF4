#include "RE/B/BGSCharacterTint_Template_Groups.hpp"

#include "RE/B/BGSCharacterTint_Template_Group.hpp"

namespace RE::BGSCharacterTint::Template
{
	Group* Groups::GetGroupByID(std::uint32_t a_id) noexcept
	{
		const auto* groupIt = std::ranges::find_if(groups, [a_id](const Group* a_group) {
			return a_group && a_group->id == a_id;
		});

		if (groupIt == groups.end()) {
			return nullptr;
		}

		return *groupIt;
	}

	const Group* Groups::GetGroupByID(std::uint32_t a_id) const noexcept
	{
		const auto* groupIt = std::ranges::find_if(groups, [a_id](const Group* a_group) {
			return a_group && a_group->id == a_id;
		});

		if (groupIt == groups.end()) {
			return nullptr;
		}

		return *groupIt;
	}
}
