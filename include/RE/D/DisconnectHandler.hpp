#pragma once

#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) DisconnectHandler
		: public BSInputEventUser // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DisconnectHandler };
		inline static constexpr auto VTABLE{ VTABLE::DisconnectHandler };
	};
	static_assert(sizeof(DisconnectHandler) == 0x10);
}
