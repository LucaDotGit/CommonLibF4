#pragma once

#include "RE/N/NiAccumulator.hpp"
#include "RE/N/NiTPointerList.hpp"

namespace RE
{
	class BSGeometry;

	class __declspec(novtable) NiBackToFrontAccumulator
		: public NiAccumulator // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiBackToFrontAccumulator };
		inline static constexpr auto VTABLE{ VTABLE::NiBackToFrontAccumulator };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiBackToFrontAccumulator };

		~NiBackToFrontAccumulator() override; // 00

		// members
		NiTPointerList<BSGeometry*> items; // 18
		std::int32_t numItems;			   // 30
		std::int32_t maxItems;			   // 34
		BSGeometry** pkItems;			   // 38
		REX::Float32* depths;			   // 40
		std::int32_t currItem;			   // 48
	};
	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);
}
