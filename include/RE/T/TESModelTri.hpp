#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESModelTri
		: public TESModel // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESModelTri };
		inline static constexpr auto VTABLE{ VTABLE::TESModelTri };
	};
	static_assert(sizeof(TESModelTri) == 0x30);
}
