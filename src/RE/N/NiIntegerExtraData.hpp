#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiIntegerExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiIntegerExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiIntegerExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiIntegerExtraData;

		NiIntegerExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiIntegerExtraData(BSFixedString a_name, std::int32_t a_value) :
			NiExtraData(std::move(a_name)),
			value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~NiIntegerExtraData() override; // 0x00

		// members
		std::int32_t value{0}; // 0x18
	};

	static_assert(sizeof(NiIntegerExtraData) == 0x20);
}
