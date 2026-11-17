#pragma once

namespace RE::GameScript::Internal
{
	class MagicEffectApplyFilter
	{
	public:
		// members
		BSScript::ObjectHandle casterHandle; // 0x00
		TESFormID effectFormID;				 // 0x08
		bool matchFilter;					 // 0x0C
	};

	static_assert(sizeof(MagicEffectApplyFilter) == 0x10);
}
