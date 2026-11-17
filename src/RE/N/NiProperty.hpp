#pragma once

#include "RE/N/NiObjectNET.hpp"

namespace RE
{
	class NiUpdateData;

	class __declspec(novtable) NiProperty : public NiObjectNET // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiProperty;
		inline static constexpr const auto& VTABLE = VTABLE::NiProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiProperty;

		// add
		virtual auto Type() -> std::int32_t = 0;		 // 0x28
		virtual void Update(NiUpdateData& a_updateData); // 0x29
	};

	static_assert(sizeof(NiProperty) == 0x28);
}
