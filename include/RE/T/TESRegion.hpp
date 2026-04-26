#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class TESRegionDataList;
	class TESRegionPointList;

	class __declspec(novtable) TESRegion
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESRegion };
		inline static constexpr auto VTABLE{ VTABLE::TESRegion };
		inline static constexpr auto FORM_TYPE{ FormType::kRegion };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kBorderRegion = 1 << 6,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// add
		virtual bool Validate(); // 49

		// members
		TESRegionDataList* dataList;				   // 20
		BSSimpleList<TESRegionPointList*>* pointLists; // 28
		TESWorldSpace* worldSpace;					   // 30
		TESWeather* currentWeather;					   // 38
		NiColor emittanceColor;						   // 40
		REX::Float32 lodDistanceModifier;			   // 4C
		REX::Float32 occlusionAccuracy;				   // 50
	};
	static_assert(sizeof(TESRegion) == 0x58);
}
