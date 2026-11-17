#pragma once

#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) DisconnectHandler : public BSInputEventUser // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::DisconnectHandler;
		inline static constexpr const auto& VTABLE = VTABLE::DisconnectHandler;
	};

	static_assert(sizeof(DisconnectHandler) == 0x10);
}
