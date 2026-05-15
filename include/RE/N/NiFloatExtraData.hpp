#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiFloatExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiFloatExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiFloatExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiFloatExtraData };

		NiFloatExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiFloatExtraData(BSFixedString a_name, REX::Float32 a_value)
			: NiExtraData(std::move(a_name)),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~NiFloatExtraData() override; // 00

		// members
		REX::Float32 value{ 0.0_f32 }; // 18
	};
	static_assert(sizeof(NiFloatExtraData) == 0x20);
}
