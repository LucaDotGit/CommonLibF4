#pragma once

namespace RE
{
	class OBJ_LIGH
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kDynamic = 1 << 0,
			kCanCarry = 1 << 1,
			kNegative = 1 << 2,
			kFlicker = 1 << 3,
			kDeepCopy = 1 << 4,
			kOffByDefault = 1 << 5,
			kFlickerSlow = 1 << 6,
			kPulse = 1 << 7,
			kPulseSlow = 1 << 8,
			kSpotlight = 1 << 9,
			kSpotShadow = 1 << 10,
			kHemiShadow = 1 << 11,
			kOmniShadow = 1 << 12,
			kPortalStrict = 1 << 13,
			kNonShadowSpot = 1 << 14,
			kNonSpecular = 1 << 15,
			kAttenuationOnly = 1 << 16,
			kNonShadowBox = 1 << 17,
			kIgnoreRoughness = 1 << 18,
			kNoRimLighting = 1 << 19,
			kAmbientOnly = 1 << 20,
			kUnknown01 = 1 << 21, // only in [001C7F0C] <RandomSpot01GR>

			kType = kNonShadowBox | kNonShadowSpot | kOmniShadow | kHemiShadow | kSpotShadow
		};

		// members
		std::int32_t time;						  // 00
		std::uint32_t radius;					  // 04
		std::uint32_t color;					  // 08
		REX::EnumSet<Flags, std::uint32_t> flags; // 0C
		REX::Float32 falloffExponent;			  // 10
		REX::Float32 fov;						  // 14
		REX::Float32 nearDistance;				  // 18
		REX::Float32 flickerPeriodRecip;		  // 1C
		REX::Float32 flickerIntensityAmplitude;	  // 20
		REX::Float32 flickerMovementAmplitude;	  // 24
		REX::Float32 attenuationConstant;		  // 28
		REX::Float32 attenuationScalar;			  // 2C
		REX::Float32 attenuationExponent;		  // 30
		REX::Float32 godraysNearDistance;		  // 34
	};
	static_assert(sizeof(OBJ_LIGH) == 0x38);
}
