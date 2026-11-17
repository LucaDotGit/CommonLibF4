#pragma once

#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESIcon : public TESTexture // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESIcon;
		inline static constexpr const auto& VTABLE = VTABLE::TESIcon;
	};

	static_assert(sizeof(TESIcon) == 0x10);
}
