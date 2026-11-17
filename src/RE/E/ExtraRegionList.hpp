#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class TESRegionList;

	class __declspec(novtable) ExtraRegionList : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRegionList;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRegionList;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::RegionList;

		ExtraRegionList() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRegionList() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESRegionList* regionList{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraRegionList) == 0x20);
}
