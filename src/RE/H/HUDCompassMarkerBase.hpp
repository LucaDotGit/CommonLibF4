#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"

namespace RE
{
	class __declspec(novtable) HUDCompassMarkerBase : public BSGFxShaderFXTarget // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDCompassMarkerBase;
		inline static constexpr const auto& VTABLE = VTABLE::HUDCompassMarkerBase;

		~HUDCompassMarkerBase() override; // 0x00

		// members
		bool showHudWarningColor; // 0xB0
	};

	static_assert(sizeof(HUDCompassMarkerBase) == 0xB8);
}
