#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiIntegersExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiIntegersExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiIntegersExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiIntegersExtraData };

		NiIntegersExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiIntegersExtraData(BSFixedString a_name, std::uint32_t a_size, std::int32_t* a_data)
			: NiExtraData(std::move(a_name)),
			  size(a_size),
			  data(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~NiIntegersExtraData() override; // 00

		// members
		std::uint32_t size{ 0 };	   // 18
		std::int32_t* data{ nullptr }; // 20
	};
	static_assert(sizeof(NiIntegersExtraData) == 0x28);
}
