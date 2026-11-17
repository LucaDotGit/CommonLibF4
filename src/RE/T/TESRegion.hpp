#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class TESRegionDataList;
	class TESRegionPointList;

	class __declspec(novtable) TESRegion : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESRegion;
		inline static constexpr const auto& VTABLE = VTABLE::TESRegion;
		inline static constexpr auto FORM_TYPE = FormType::Region;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				BorderRegion = 1 << 6,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// add
		virtual auto Validate() -> bool; // 0x49

		// members
		TESRegionDataList* dataList;				   // 0x20
		BSSimpleList<TESRegionPointList*>* pointLists; // 0x28
		TESWorldSpace* worldSpace;					   // 0x30
		TESWeather* currentWeather;					   // 0x38
		NiColor emittanceColor;						   // 0x40
		REX::Float32 lodDistanceModifier;			   // 0x4C
		REX::Float32 occlusionAccuracy;				   // 0x50
	};

	static_assert(sizeof(TESRegion) == 0x58);
}
