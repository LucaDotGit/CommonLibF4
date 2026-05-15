#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiBooleanExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiBooleanExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiBooleanExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiBooleanExtraData };

		NiBooleanExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiBooleanExtraData(BSFixedString a_name, bool a_value)
			: NiExtraData(std::move(a_name)),
			  value(a_value)
		{
			REL::EmplaceVtable(this);
		}

		~NiBooleanExtraData() override; // 00

		// members
		bool value{ false }; // 18
	};
	static_assert(sizeof(NiBooleanExtraData) == 0x20);
}
