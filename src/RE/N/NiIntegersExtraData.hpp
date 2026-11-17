#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiIntegersExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiIntegersExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiIntegersExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiIntegersExtraData;

		NiIntegersExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiIntegersExtraData(BSFixedString a_name, std::uint32_t a_size, std::int32_t* a_data) :
			NiExtraData(std::move(a_name)),
			size(a_size),
			data(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~NiIntegersExtraData() override; // 0x00

		// members
		std::uint32_t size{0};		 // 0x18
		std::int32_t* data{nullptr}; // 0x20
	};

	static_assert(sizeof(NiIntegersExtraData) == 0x28);
}
