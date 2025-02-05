#pragma once

#include "RE/NetImmerse/NiProperty.hpp"

namespace RE
{
	class __declspec(novtable) NiShadeProperty
		: public NiProperty // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiShadeProperty };
		inline static constexpr auto VTABLE{ VTABLE::NiShadeProperty };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiShadeProperty };

		// add
		virtual bool SetupGeometry([[maybe_unused]] BSGeometry* a_geometry) { return true; } // 2A
	};
	static_assert(sizeof(NiShadeProperty) == 0x28);
}
