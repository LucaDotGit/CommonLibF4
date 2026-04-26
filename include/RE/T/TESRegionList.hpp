#pragma once

#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class __declspec(novtable) TESRegionList
		: public BSSimpleList<TESRegion*>
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESRegionList };
		inline static constexpr auto VTABLE{ VTABLE::TESRegionList };

		virtual ~TESRegionList(); // 00

		void SetRegions(std::span<TESRegion*> a_regions);
		void ClearRegions();

		// members
		bool ownsRegionMemory; // 18
	};
	static_assert(sizeof(TESRegionList) == 0x20);
}
