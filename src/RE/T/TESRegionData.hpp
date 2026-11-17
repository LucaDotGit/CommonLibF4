#pragma once

#include "RE/R/REGION_DATA_ID.hpp"

namespace RE
{
	class REGION_DATA_BASE;
	class TESRegion;

	class __declspec(novtable) TESRegionData
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESRegionData;
		inline static constexpr const auto& VTABLE = VTABLE::TESRegionData;

		virtual ~TESRegionData(); // 0x00

		// add
		virtual auto LoadRegionData(REGION_DATA_BASE* a_data) -> bool;							  // 0x01
		virtual void Initialize(TESRegion* a_formal);											  // 0x02
		virtual auto GetID() -> REGION_DATA_ID;													  // 0x03
		virtual auto Copy() -> TESRegionData*;													  // 0x04
		virtual auto Blend() -> TESRegionData*;													  // 0x04
		virtual void BlendInto(const TESRegionData* a_regionData, std::uint32_t a_totalBlending); // 0x05
		virtual auto Validate() -> bool;														  // 0x06

		// members
		bool override{false};	  // 0x08
		bool ignore{false};		  // 0x09
		std::uint8_t priority{0}; // 0x0A
	};

	static_assert(sizeof(TESRegionData) == 0x10);
}
