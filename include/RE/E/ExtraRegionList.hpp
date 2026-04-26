#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class TESRegionList;

	class __declspec(novtable) ExtraRegionList
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraRegionList };
		inline static constexpr auto VTABLE{ VTABLE::ExtraRegionList };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kRegionList };

		ExtraRegionList()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRegionList() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESRegionList* regionList{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraRegionList) == 0x20);
}
