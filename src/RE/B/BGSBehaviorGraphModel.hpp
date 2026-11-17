#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSBehaviorGraphModel : public TESModel // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSBehaviorGraphModel;
		inline static constexpr const auto& VTABLE = VTABLE::BGSBehaviorGraphModel;
	};

	static_assert(sizeof(BGSBehaviorGraphModel) == 0x30);
}
