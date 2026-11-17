#pragma once

#include "RE/N/NiBackToFrontAccumulator.hpp"

namespace RE
{
	class __declspec(novtable) NiAlphaAccumulator : public NiBackToFrontAccumulator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiAlphaAccumulator;
		inline static constexpr const auto& VTABLE = VTABLE::NiAlphaAccumulator;
		inline static constexpr auto Ni_RTTI = Ni_RTTI::NiAlphaAccumulator;

		~NiAlphaAccumulator() override; // 0x00

		// members
		bool observeNoSortHint;	 // 0x50
		bool sortByClosestPoint; // 0x51
		bool interfaceSort;		 // 0x52
	};

	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
