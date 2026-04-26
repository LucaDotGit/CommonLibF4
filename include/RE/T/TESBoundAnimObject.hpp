#pragma once

#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) TESBoundAnimObject
		: public TESBoundObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESBoundAnimObject };
		inline static constexpr auto VTABLE{ VTABLE::TESBoundAnimObject };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };
	};
	static_assert(sizeof(TESBoundAnimObject) == 0x68);
}
