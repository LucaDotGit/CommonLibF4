#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint::Template
{
	class Group;

	class Groups
	{
	public:
		[[nodiscard]]
		auto GetGroupByID(std::uint32_t a_id) noexcept -> Group*;
		[[nodiscard]]
		auto GetGroupByID(std::uint32_t a_id) const noexcept -> const Group*;

		// members
		BSTArray<Group*> groups; // 0x00
	};

	static_assert(sizeof(Groups) == 0x18);
}
