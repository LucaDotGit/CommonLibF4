#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSBehaviorGraphModel
		: public TESModel // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBehaviorGraphModel };
		inline static constexpr auto VTABLE{ VTABLE::BGSBehaviorGraphModel };
	};
	static_assert(sizeof(BGSBehaviorGraphModel) == 0x30);
}
