#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/S/SCRIPT_LOCAL.hpp"

namespace RE
{
	class ScriptVariable
	{
	public:
		// members
		SCRIPT_LOCAL data; // 00
		BSString name;	   // 10
	};
	static_assert(sizeof(ScriptVariable) == 0x20);
}
