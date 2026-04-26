#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESModelRDT
		: public TESModel // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESModelRDT };
		inline static constexpr auto VTABLE{ VTABLE::TESModelRDT };
	};
	static_assert(sizeof(TESModelRDT) == 0x30);
}
