#pragma once

#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) MenuOpenHandler
		: public BSInputEventUser // 00
	{
		inline static constexpr auto RTTI{ RTTI::MenuOpenHandler };
		inline static constexpr auto VTABLE{ VTABLE::MenuOpenHandler };
	};
	static_assert(sizeof(MenuOpenHandler) == 0x10);
}
