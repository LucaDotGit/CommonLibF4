#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSModelMaterialSwap : public TESModel // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSModelMaterialSwap;
		inline static constexpr const auto& VTABLE = VTABLE::BGSModelMaterialSwap;

		~BGSModelMaterialSwap() override; // 0x00

		// members
		BGSMaterialSwap* swapForm;		  // 0x30
		REX::Float32 colorRemappingIndex; // 0x38
	};

	static_assert(sizeof(BGSModelMaterialSwap) == 0x40);
}
