#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"

namespace RE
{
	class __declspec(novtable) ButtonHintBar : public BSGFxShaderFXTarget // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ButtonHintBar;
		inline static constexpr const auto& VTABLE = VTABLE::ButtonHintBar;

		// members
		Scaleform::GFx::Value sourceButtons; // 0xB0
		bool redirectToButtonBarMenu;		 // 0xD0
		bool isTopButtonBar;				 // 0xD1
	};

	static_assert(sizeof(ButtonHintBar) == 0xD8);
}
