#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSModelMaterialSwap
		: public TESModel // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSModelMaterialSwap };
		inline static constexpr auto VTABLE{ VTABLE::BGSModelMaterialSwap };

		~BGSModelMaterialSwap() override; // 00

		// members
		BGSMaterialSwap* swapForm;		  // 30
		REX::Float32 colorRemappingIndex; // 38
	};
	static_assert(sizeof(BGSModelMaterialSwap) == 0x40);
}
