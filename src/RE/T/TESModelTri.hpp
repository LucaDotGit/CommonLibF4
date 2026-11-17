#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESModelTri : public TESModel // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESModelTri;
		inline static constexpr const auto& VTABLE = VTABLE::TESModelTri;
	};

	static_assert(sizeof(TESModelTri) == 0x30);
}
