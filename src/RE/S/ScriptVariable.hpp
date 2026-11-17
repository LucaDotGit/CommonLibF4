#pragma once

#include "RE/B/BSString.hpp"
#include "RE/S/SCRIPT_LOCAL.hpp"

namespace RE
{
	class ScriptVariable
	{
	public:
		// members
		SCRIPT_LOCAL data; // 0x00
		BSString name;	   // 0x10
	};

	static_assert(sizeof(ScriptVariable) == 0x20);
}
