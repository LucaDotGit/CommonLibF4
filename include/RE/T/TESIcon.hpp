#pragma once

#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESIcon
		: public TESTexture // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESIcon };
		inline static constexpr auto VTABLE{ VTABLE::TESIcon };
	};
	static_assert(sizeof(TESIcon) == 0x10);
}
