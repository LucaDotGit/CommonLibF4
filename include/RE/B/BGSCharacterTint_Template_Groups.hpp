#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint::Template
{
	class Group;

	class Groups
	{
	public:
		// members
		BSTArray<Group*> groups; // 00
	};
	static_assert(sizeof(Groups) == 0x18);
}
