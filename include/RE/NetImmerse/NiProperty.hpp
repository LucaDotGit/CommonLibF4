#pragma once

#include "RE/NetImmerse/NiObjectNET.hpp"

namespace RE
{
	class NiUpdateData;

	class __declspec(novtable) NiProperty
		: public NiObjectNET // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiProperty };
		inline static constexpr auto VTABLE{ VTABLE::NiProperty };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiProperty };

		// add
		virtual std::int32_t Type() = 0;				 // 28
		virtual void Update(NiUpdateData& a_updateData); // 29
	};
	static_assert(sizeof(NiProperty) == 0x28);
}
