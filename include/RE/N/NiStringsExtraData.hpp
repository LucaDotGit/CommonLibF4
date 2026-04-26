#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiStringsExtraData
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiStringsExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiStringsExtraData };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiStringsExtraData };

		NiStringsExtraData()
		{
			REL::EmplaceVtable(this);
		}

		~NiStringsExtraData() override; // 00

		// members
		std::uint32_t size{ 0 }; // 18
		char** data{ nullptr };	 // 20
	};
	static_assert(sizeof(NiStringsExtraData) == 0x28);
}
