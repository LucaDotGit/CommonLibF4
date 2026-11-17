#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiStringExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiStringExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiStringExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiStringExtraData;

		NiStringExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiStringExtraData(BSFixedString a_name, BSFixedString a_value) :
			NiExtraData(std::move(a_name)),
			value(std::move(a_value))
		{
			REL::EmplaceVtable(this);
		}

		~NiStringExtraData() override; // 0x00

		// members
		BSFixedString value; // 0x18
	};

	static_assert(sizeof(NiStringExtraData) == 0x20);
}
