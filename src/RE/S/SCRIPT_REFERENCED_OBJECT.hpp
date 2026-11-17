#pragma once

#include "RE/B/BSString.hpp"

namespace RE
{
	class SCRIPT_REFERENCED_OBJECT
	{
	public:
		// members
		BSString editorID;		  // 0x00
		TESForm* form;			  // 0x10
		std::uint32_t variableID; // 0x18
	};

	static_assert(sizeof(SCRIPT_REFERENCED_OBJECT) == 0x20);
}
