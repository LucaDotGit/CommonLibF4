#pragma once

#include "RE/N/NiExtraData.hpp"

namespace RE
{
	class __declspec(novtable) NiStringsExtraData : public NiExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiStringsExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::NiStringsExtraData;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiStringsExtraData;

		NiStringsExtraData()
		{
			REL::EmplaceVtable(this);
		}

		NiStringsExtraData(BSFixedString a_name, std::uint32_t a_size, char** a_data) :
			NiExtraData(std::move(a_name)),
			size(a_size),
			data(a_data)
		{
			REL::EmplaceVtable(this);
		}

		~NiStringsExtraData() override; // 0x00

		// members
		std::uint32_t size{0}; // 0x18
		char** data{nullptr};  // 0x20
	};

	static_assert(sizeof(NiStringsExtraData) == 0x28);
}
