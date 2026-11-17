#pragma once

#include "RE/N/NiAccumulator.hpp"
#include "RE/N/NiTPointerList.hpp"

namespace RE
{
	class BSGeometry;

	class __declspec(novtable) NiBackToFrontAccumulator : public NiAccumulator // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiBackToFrontAccumulator;
		inline static constexpr const auto& VTABLE = VTABLE::NiBackToFrontAccumulator;
		inline static constexpr auto Ni_RTTI = Ni_RTTI::NiBackToFrontAccumulator;

		~NiBackToFrontAccumulator() override; // 0x00

		// members
		NiTPointerList<BSGeometry*> items; // 0x18
		std::int32_t numItems;			   // 0x30
		std::int32_t maxItems;			   // 0x34
		BSGeometry** pkItems;			   // 0x38
		REX::Float32* depths;			   // 0x40
		std::int32_t currItem;			   // 0x48
	};

	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);
}
