#pragma once

#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class ACTION_OBJECT;
	class SCRIPT_EFFECT_DATA;
	class SCRIPT_LOCAL;

	class ScriptLocals
	{
	public:
		// members
		Script* masterScript;					  // 0x00
		std::int8_t flags;						  // 0x08
		BSSimpleList<ACTION_OBJECT*>* actionList; // 0x10
		BSSimpleList<SCRIPT_LOCAL*>* localList;	  // 0x18
		SCRIPT_EFFECT_DATA* scriptEffectData;	  // 0x20
	};

	static_assert(sizeof(ScriptLocals) == 0x28);
}
