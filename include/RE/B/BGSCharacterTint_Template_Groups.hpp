#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint::Template
{
	class Group;

	class Groups
	{
	public:
		[[nodiscard]] Group* GetGroupByID(std::uint32_t a_id) noexcept;
		[[nodiscard]] const Group* GetGroupByID(std::uint32_t a_id) const noexcept;

		// members
		BSTArray<Group*> groups; // 00
	};
	static_assert(sizeof(Groups) == 0x18);
}
