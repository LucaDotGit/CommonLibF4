#pragma once

#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) TESBoundAnimObject : public TESBoundObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESBoundAnimObject;
		inline static constexpr const auto& VTABLE = VTABLE::TESBoundAnimObject;
		inline static constexpr auto FORM_TYPE = FormType::None;
	};

	static_assert(sizeof(TESBoundAnimObject) == 0x68);
}
