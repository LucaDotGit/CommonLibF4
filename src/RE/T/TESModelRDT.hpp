#pragma once

#include "RE/T/TESModel.hpp"

namespace RE
{
	class __declspec(novtable) TESModelRDT : public TESModel // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESModelRDT;
		inline static constexpr const auto& VTABLE = VTABLE::TESModelRDT;
	};

	static_assert(sizeof(TESModelRDT) == 0x30);
}
