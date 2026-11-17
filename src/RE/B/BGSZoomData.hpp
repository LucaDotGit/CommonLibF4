#pragma once

#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSZoomData : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSZoomData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSZoomData;
		inline static constexpr auto FORM_TYPE = FormType::ZoomData;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Data
		{
		public:
			enum class OverlayType : std::int32_t
			{
				Default = 0,
				Fine = 1,
				Duplex = 2,
				German = 3,
				Dot = 4,
				MilitaryDot = 5,
				Circle = 6,
				OldRangefind = 7,
				ModernRangefind = 8,
				SVD = 9,
				HandPainted = 10,
				Binoculars = 11,
				Cross = 12,
				DoubleZero = 13,
				Rangefinder01 = 14,
				Rangefinder02 = 15,
				Rectangle = 16,

				_Count = 17
			};

			// members
			REX::Float32 fovMult;						  // 0x00
			REX::Enum<OverlayType, std::int32_t> overlay; // 0x04
			TESFormID isModFormID;						  // 0x08
			NiPoint3 cameraOffset;						  // 0x0C
		};

		static_assert(sizeof(Data) == 0x18);

		// members
		Data zoomData;				  // 0x20
		TESImageSpaceModifier* isMod; // 0x38
	};

	static_assert(sizeof(BGSZoomData) == 0x40);
}
