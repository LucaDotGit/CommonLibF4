#pragma once

#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) MenuOpenHandler : public BSInputEventUser // 0x00
	{
		inline static constexpr const auto& RTTI = RTTI::MenuOpenHandler;
		inline static constexpr const auto& VTABLE = VTABLE::MenuOpenHandler;
	};

	static_assert(sizeof(MenuOpenHandler) == 0x10);
}
