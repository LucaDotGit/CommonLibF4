#pragma once

#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class __declspec(novtable) TESRegionList : public BSSimpleList<TESRegion*>
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESRegionList;
		inline static constexpr const auto& VTABLE = VTABLE::TESRegionList;

		virtual ~TESRegionList(); // 0x00

		void SetRegions(std::span<TESRegion*> a_regions);
		void ClearRegions();

		// members
		bool ownsRegionMemory; // 0x18
	};

	static_assert(sizeof(TESRegionList) == 0x20);
}
