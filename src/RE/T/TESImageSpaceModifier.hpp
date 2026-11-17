#pragma once

#include "RE/B/BSString.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiColorInterpolator;
	class NiFloatInterpolator;

	class __declspec(novtable) TESImageSpaceModifier : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESImageSpaceModifier;
		inline static constexpr const auto& VTABLE = VTABLE::TESImageSpaceModifier;
		inline static constexpr auto FORM_TYPE = FormType::ImageSpaceModifier;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Operations : std::int32_t
		{
			Mult = 0,
			Add = 1,

			_Count = 2
		};

		enum class OperationParameter : std::int32_t
		{
			HDR_First = 0,
			HDR_EyeAdaptSpeed = 0,
			HDR_BloomBlurRadius = 1,
			HDR_BloomThreshold = 2,
			HDR_BloomScale = 3,
			HDR_TargetLuminanceMin = 4,
			HDR_TargetLuminanceMax = 5,
			HDR_SunlightScale = 6,
			HDR_SkyScale = 7,
			HDR_Empty08 = 8,
			HDR_Empty09 = 9,
			HDR_Empty10 = 10,
			HDR_Empty11 = 11,
			HDR_Empty12 = 12,
			HDR_Empty13 = 13,
			HDR_Last = 13,

			Bloom_First = 14,
			Bloom_Empty14 = 14,
			Bloom_Empty15 = 15,
			Bloom_Empty16 = 16,
			Bloom_Last = 16,

			Cinematic_First = 17,
			Cinematic_Saturation = 17,
			Cinematic_Brightness = 18,
			Cinematic_Contrast = 19,
			Cinematic_Empty20 = 20,
			Cinematic_Last = 20,

			_Count = 21
		};

		class ImageSpaceModifierData
		{
		public:
			enum class DepthOfFieldFlags : std::uint8_t
			{
				None = 0,
				Front = 1 << 0,
				Back = 1 << 1
			};

			// members
			bool animatable;	   // 0x00
			REX::Float32 duration; // 0x04
			std::array<
				std::array<std::uint32_t, std::to_underlying(OperationParameter::_Count)>,
				std::to_underlying(Operations::_Count)>
				keySize;													 // 0x08
			std::uint32_t tintColorKeySize;									 // 0xB0
			std::uint32_t blurKeySize;										 // 0xB4
			std::uint32_t doubleKeySize;									 // 0xB8
			std::uint32_t radialBlurStrengthKeySize;						 // 0xBC
			std::uint32_t radialBlurRampUpKeySize;							 // 0xC0
			std::uint32_t radialBlurStartKeySize;							 // 0xC4
			bool useTargetForRadialBlur;									 // 0xC8
			NiPoint2 radialBlurCenter;										 // 0xCC
			std::uint32_t depthOfFieldStrengthKeySize;						 // 0xD4
			std::uint32_t depthOfFieldDistanceKeySize;						 // 0xD8
			std::uint32_t depthOfFieldRangeKeySize;							 // 0xDC
			bool useTargetForDepthOfField;									 // 0xE0
			REX::EnumSet<DepthOfFieldFlags, std::uint8_t> depthOfFieldFlags; // 0xE1
			std::uint32_t radialBlurRampDownKeySize;						 // 0xE4
			std::uint32_t radialBlurDownStartKeySize;						 // 0xE8
			std::uint32_t fadeColorKeySize;									 // 0xEC
			std::uint32_t motionBlurStrengthKeySize;						 // 0xF0
			std::uint32_t depthOfFieldVignetteRadiusKeySize;				 // 0xF4
			std::uint32_t depthOfFieldVignetteStrengthKeySize;				 // 0xF8
		};

		static_assert(sizeof(ImageSpaceModifierData) == 0xFC);

		// members
		ImageSpaceModifierData data; // 0x020
		std::array<
			std::array<NiPointer<NiFloatInterpolator>, std::to_underlying(OperationParameter::_Count)>,
			std::to_underlying(Operations::_Count)>
			interpolator;														 // 0x120
		NiPointer<NiFloatInterpolator> blurInterpolator;						 // 0x270
		NiPointer<NiFloatInterpolator> doubleInterpolator;						 // 0x278
		NiPointer<NiColorInterpolator> tintColorInterpolator;					 // 0x280
		NiPointer<NiColorInterpolator> fadeColorInterpolator;					 // 0x288
		NiPointer<NiFloatInterpolator> radialBlurStrengthInterpolator;			 // 0x290
		NiPointer<NiFloatInterpolator> radialBlurRampUpInterpolator;			 // 0x298
		NiPointer<NiFloatInterpolator> radialBlurStartInterpolator;				 // 0x2A0
		NiPointer<NiFloatInterpolator> radialBlurRampDownInterpolator;			 // 0x2A8
		NiPointer<NiFloatInterpolator> radialBlurDownStartInterpolator;			 // 0x2B0
		NiPointer<NiFloatInterpolator> depthOfFieldStrengthInterpolator;		 // 0x2B8
		NiPointer<NiFloatInterpolator> depthOfFieldDistanceInterpolator;		 // 0x2C0
		NiPointer<NiFloatInterpolator> depthOfFieldRangeInterpolator;			 // 0x2C8
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteRadiusInterpolator;	 // 0x2D0
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteStrengthInterpolator; // 0x2D8
		NiPointer<NiFloatInterpolator> motionBlurStrengthInterpolator;			 // 0x2E0
		BSString formEditorID;													 // 0x2E8
	};

	static_assert(sizeof(TESImageSpaceModifier) == 0x2F8);
}
