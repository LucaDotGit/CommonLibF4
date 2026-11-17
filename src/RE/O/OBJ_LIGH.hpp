#pragma once

namespace RE
{
	class OBJ_LIGH
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			Dynamic = 1 << 0,
			CanCarry = 1 << 1,
			Negative = 1 << 2,
			Flicker = 1 << 3,
			DeepCopy = 1 << 4,
			OffByDefault = 1 << 5,
			FlickerSlow = 1 << 6,
			Pulse = 1 << 7,
			PulseSlow = 1 << 8,
			Spotlight = 1 << 9,
			SpotShadow = 1 << 10,
			HemiShadow = 1 << 11,
			OmniShadow = 1 << 12,
			PortalStrict = 1 << 13,
			NonShadowSpot = 1 << 14,
			NonSpecular = 1 << 15,
			AttenuationOnly = 1 << 16,
			NonShadowBox = 1 << 17,
			IgnoreRoughness = 1 << 18,
			NoRimLighting = 1 << 19,
			AmbientOnly = 1 << 20,
			Unknown01 = 1 << 21, // only in [001C7F0C] <RandomSpot01GR>

			Type = NonShadowBox | NonShadowSpot | OmniShadow | HemiShadow | SpotShadow
		};

		// members
		std::int32_t time;						  // 0x00
		std::uint32_t radius;					  // 0x04
		std::uint32_t color;					  // 0x08
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x0C
		REX::Float32 falloffExponent;			  // 0x10
		REX::Float32 fov;						  // 0x14
		REX::Float32 nearDistance;				  // 0x18
		REX::Float32 flickerPeriodRecip;		  // 0x1C
		REX::Float32 flickerIntensityAmplitude;	  // 0x20
		REX::Float32 flickerMovementAmplitude;	  // 0x24
		REX::Float32 attenuationConstant;		  // 0x28
		REX::Float32 attenuationScalar;			  // 0x2C
		REX::Float32 attenuationExponent;		  // 0x30
		REX::Float32 godraysNearDistance;		  // 0x34
	};

	static_assert(sizeof(OBJ_LIGH) == 0x38);
}
