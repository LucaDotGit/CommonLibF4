#pragma once

#include "RE/N/NiBackToFrontAccumulator.hpp"

namespace RE
{
	class __declspec(novtable) NiAlphaAccumulator
		: public NiBackToFrontAccumulator // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiAlphaAccumulator };
		inline static constexpr auto VTABLE{ VTABLE::NiAlphaAccumulator };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiAlphaAccumulator };

		~NiAlphaAccumulator() override; // 00

		// members
		bool observeNoSortHint;	 // 50
		bool sortByClosestPoint; // 51
		bool interfaceSort;		 // 52
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
