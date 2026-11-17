#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraPoison : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraPoison;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraPoison;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Poison;

		ExtraPoison() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraPoison() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		std::uint32_t count{0};		  // 0x18
		AlchemyItem* poison{nullptr}; // 0x20
	};

	static_assert(sizeof(ExtraPoison) == 0x28);
}
