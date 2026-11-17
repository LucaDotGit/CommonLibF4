#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiFloatExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiFloatExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiFloatExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiFloatExtraData;

		NiFloatExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiFloatExtraData(BSFixedString a_name, REX::Float32 a_value) :
			NiExtraData(std::move(a_name)),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~NiFloatExtraData() override; // 0x00

		// members
		REX::Float32 value{static_cast<REX::Float32>(0.0)}; // 0x18
	};

	static_assert(sizeof(NiFloatExtraData) == 0x20);
}
