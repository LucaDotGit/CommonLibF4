#pragma once

namespace RE::GameScript::Internal
{
	class MagicEffectApplyFilter
	{
	public:
		// members
		BSScript::ObjectHandle casterHandle; // 00
		TESFormID effectFormID;				 // 08
		bool matchFilter;					 // 0C
	};
	static_assert(sizeof(MagicEffectApplyFilter) == 0x10);
}
