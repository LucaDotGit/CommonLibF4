#pragma once

#include "RE/Bethesda/BSInputEventReceiver.hpp"
#include "RE/Bethesda/BSInputEventUser.hpp"

namespace RE
{
	class BSInputEventSingleUser
		: public BSInputEventReceiver, // 00
		  public BSInputEventUser	   // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSInputEventSingleUser };
		inline static constexpr auto VTABLE{ VTABLE::BSInputEventSingleUser };
	};
	static_assert(sizeof(BSInputEventSingleUser) == 0x20);
}
