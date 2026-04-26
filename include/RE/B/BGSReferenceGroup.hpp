#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSReferenceGroup
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSReferenceGroup };
		inline static constexpr auto VTABLE{ VTABLE::BGSReferenceGroup };
		inline static constexpr auto FORM_TYPE{ FormType::kReferenceGroup };
	};
	static_assert(sizeof(BGSReferenceGroup) == 0x20);
}
