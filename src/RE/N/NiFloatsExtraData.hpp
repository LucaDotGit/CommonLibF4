#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiFloatsExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiFloatsExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiFloatsExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiFloatsExtraData;

		NiFloatsExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiFloatsExtraData(BSFixedString a_name, std::uint32_t a_size, REX::Float32* a_data) :
			NiExtraData(std::move(a_name)),
			size(a_size),
			data(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~NiFloatsExtraData() override; // 0x00

		// members
		std::uint32_t size{0};		 // 0x18
		REX::Float32* data{nullptr}; // 0x20
	};

	static_assert(sizeof(NiFloatsExtraData) == 0x28);
}
