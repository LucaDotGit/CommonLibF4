#pragma once

#include "RE/N/NiProperty.hpp"

namespace RE
{
	class __declspec(novtable) NiShadeProperty : public NiProperty // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiShadeProperty;
		inline static constexpr const auto& VTABLE = VTABLE::NiShadeProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiShadeProperty;

		// add
		virtual auto SetupGeometry(BSGeometry* a_geometry) -> bool; // 0x2A - { return true; }
	};

	static_assert(sizeof(NiShadeProperty) == 0x28);
}
