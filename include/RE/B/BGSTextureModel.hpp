#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) BGSTextureModel
		: public TESModel // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTextureModel };
		inline static constexpr auto VTABLE{ VTABLE::BGSTextureModel };
	};
	static_assert(sizeof(BGSTextureModel) == 0x30);
}
