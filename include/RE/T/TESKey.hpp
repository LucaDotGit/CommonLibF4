#pragma once

#include "RE/T/TESObjectMISC.hpp"

namespace RE
{
	class __declspec(novtable) TESKey
		: public TESObjectMISC // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESKey };
		inline static constexpr auto VTABLE{ VTABLE::TESKey };
		inline static constexpr auto FORM_TYPE{ FormType::kKey };
	};
	static_assert(sizeof(TESKey) == 0x168);
}
