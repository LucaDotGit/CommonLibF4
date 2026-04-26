#pragma once

#include "RE/B/BSGFxShaderFXTarget.hpp"

namespace RE
{
	class __declspec(novtable) HUDCompassMarkerBase
		: public BSGFxShaderFXTarget
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDCompassMarkerBase };
		inline static constexpr auto VTABLE{ VTABLE::HUDCompassMarkerBase };

		~HUDCompassMarkerBase() override; // 00

		// members
		bool showHudWarningColor; // B0
	};
	static_assert(sizeof(HUDCompassMarkerBase) == 0xB8);
}
