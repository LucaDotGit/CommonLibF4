#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSTextureModel : public TESModel // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSTextureModel;
		inline static constexpr const auto& VTABLE = VTABLE::BGSTextureModel;
	};

	static_assert(sizeof(BGSTextureModel) == 0x30);
}
