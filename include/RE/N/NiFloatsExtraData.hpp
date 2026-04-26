#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiFloatsExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiFloatsExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiFloatsExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiFloatsExtraData };

		NiFloatsExtraData()
		{
			REL::EmplaceVtable(this);
		}

		~NiFloatsExtraData() override; // 00

		// members
		std::uint32_t size{ 0 };	   // 18
		REX::Float32* data{ nullptr }; // 20
	};
	static_assert(sizeof(NiFloatsExtraData) == 0x28);
}
