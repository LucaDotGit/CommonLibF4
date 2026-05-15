#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiIntegerExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiIntegerExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiIntegerExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiIntegerExtraData };

		NiIntegerExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiIntegerExtraData(BSFixedString a_name, std::int32_t a_value)
			: NiExtraData(std::move(a_name)),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~NiIntegerExtraData() override; // 00

		// members
		std::int32_t value{ 0 }; // 18
	};
	static_assert(sizeof(NiIntegerExtraData) == 0x20);
}
