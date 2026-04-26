#pragma once

namespace RE
{
	enum class _D3DBLEND : std::int32_t;
	enum class _D3DBLENDOP : std::int32_t;
	enum class _D3DCMPFUNC : std::int32_t;

	class EffectShaderData
	{
	public:
		// members
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeSource;	// 00
		REX::Enum<_D3DBLENDOP, std::int32_t> textureBlendOperation; // 04
		REX::Enum<_D3DCMPFUNC, std::int32_t> textureZTestFunction;	// 08
		std::uint32_t fillColor01;									// 0C
		REX::Float32 fillAlphaFadeInTime;							// 10
		REX::Float32 fillAlphaFullTime;								// 14
		REX::Float32 fillAlphaFadeOutTime;							// 18
		REX::Float32 fillAlphaPersistentPercent;					// 1C
		REX::Float32 fillAlphaPulseAmplitude;						// 20
		REX::Float32 fillAlphaPulseFrequency;						// 24
		REX::Float32 fillTextureUAnimSpeed;							// 28
		REX::Float32 fillTextureVAnimSpeed;							// 2C
		REX::Float32 edgeExponentValue;								// 30
		std::uint32_t edgeColor;									// 34
		REX::Float32 edgeAlphaFadeInTime;							// 38
		REX::Float32 edgeAlphaFullTime;								// 3C
		REX::Float32 edgeAlphaFadeOutTime;							// 40
		REX::Float32 edgeAlphaPersistentPercent;					// 44
		REX::Float32 edgeAlphaPulseAmplitude;						// 48
		REX::Float32 edgeAlphaPulseFrequency;						// 4C
		REX::Float32 fillAlphaFullPercent;							// 50
		REX::Float32 edgeAlphaFullPercent;							// 54
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeDest;	// 58
		REX::Float32 alphaTestStartTime;							// 5C
		REX::Float32 alphaTestEndTime;								// 60
		REX::Float32 alphaTestStartValue;							// 64
		REX::Float32 alphaTestEndValue;								// 68
		BGSSoundDescriptorForm* ambientSound;						// 70
		std::uint32_t fillColor02;									// 78
		std::uint32_t fillColor03;									// 7C
		std::array<REX::Float32, 3> fillColorScales;				// 80
		std::array<REX::Float32, 3> fillColorTimes;					// 8C
		std::uint32_t flags;										// 98
		REX::Float32 fillTextureUScale;								// 9C
		REX::Float32 fillTextureVScale;								// A0
		std::int8_t boneDepth;										// A4
	};
	static_assert(sizeof(EffectShaderData) == 0xA8);
}
