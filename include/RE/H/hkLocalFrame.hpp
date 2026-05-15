#pragma once

#include "RE/H/hkReferencedObject.hpp"

namespace RE
{
	class __declspec(novtable) hkLocalFrame
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkLocalFrame };
		inline static constexpr auto VTABLE{ VTABLE::hkLocalFrame };

		~hkLocalFrame() override; // 00
	};
	static_assert(sizeof(hkLocalFrame) == 0x10);
}
