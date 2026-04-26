#pragma once

#include "RE/N/NiPoint.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSZoomData
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSZoomData };
		inline static constexpr auto VTABLE{ VTABLE::BGSZoomData };
		inline static constexpr auto FORM_TYPE{ FormType::kZoomData };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			enum class OverlayType : std::int32_t
			{
				kDefault = 0,
				kFine = 1,
				kDuplex = 2,
				kGerman = 3,
				kDot = 4,
				kMilitaryDot = 5,
				kCircle = 6,
				kOldRangefind = 7,
				kModernRangefind = 8,
				kSVD = 9,
				kHandPainted = 10,
				kBinoculars = 11,
				kCross = 12,
				kDoubleZero = 13,
				kRangefinder01 = 14,
				kRangefinder02 = 15,
				kRectangle = 16,

				kTotal = 17
			};

			// members
			REX::Float32 fovMult;						  // 00
			REX::Enum<OverlayType, std::int32_t> overlay; // 04
			TESFormID isModFormID;						  // 08
			NiPoint3 cameraOffset;						  // 0C
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data zoomData;				  // 20
		TESImageSpaceModifier* isMod; // 38
	};
	static_assert(sizeof(BGSZoomData) == 0x40);
}
