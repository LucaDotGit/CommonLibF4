#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiStringExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiStringExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiStringExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiStringExtraData };

		NiStringExtraData()
		{
			REL::EmplaceVtable(this);
		}

		~NiStringExtraData() override; // 00

		// members
		BSFixedString data; // 18
	};
	static_assert(sizeof(NiStringExtraData) == 0x20);
}
