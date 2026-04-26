#pragma once

#include "RE/N/NiProperty.hpp"

namespace RE
{
	class __declspec(novtable) NiShadeProperty
		: public NiProperty // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiShadeProperty };
		inline static constexpr auto VTABLE{ VTABLE::NiShadeProperty };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiShadeProperty };

		// add
		virtual bool SetupGeometry(BSGeometry* a_geometry); // 2A - { return true; }
	};
	static_assert(sizeof(NiShadeProperty) == 0x28);
}
