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
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeSource;	// 0x00
		REX::Enum<_D3DBLENDOP, std::int32_t> textureBlendOperation; // 0x04
		REX::Enum<_D3DCMPFUNC, std::int32_t> textureZTestFunction;	// 0x08
		std::uint32_t fillColor01;									// 0x0C
		REX::Float32 fillAlphaFadeInTime;							// 0x10
		REX::Float32 fillAlphaFullTime;								// 0x14
		REX::Float32 fillAlphaFadeOutTime;							// 0x18
		REX::Float32 fillAlphaPersistentPercent;					// 0x1C
		REX::Float32 fillAlphaPulseAmplitude;						// 0x20
		REX::Float32 fillAlphaPulseFrequency;						// 0x24
		REX::Float32 fillTextureUAnimSpeed;							// 0x28
		REX::Float32 fillTextureVAnimSpeed;							// 0x2C
		REX::Float32 edgeExponentValue;								// 0x30
		std::uint32_t edgeColor;									// 0x34
		REX::Float32 edgeAlphaFadeInTime;							// 0x38
		REX::Float32 edgeAlphaFullTime;								// 0x3C
		REX::Float32 edgeAlphaFadeOutTime;							// 0x40
		REX::Float32 edgeAlphaPersistentPercent;					// 0x44
		REX::Float32 edgeAlphaPulseAmplitude;						// 0x48
		REX::Float32 edgeAlphaPulseFrequency;						// 0x4C
		REX::Float32 fillAlphaFullPercent;							// 0x50
		REX::Float32 edgeAlphaFullPercent;							// 0x54
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeDest;	// 0x58
		REX::Float32 alphaTestStartTime;							// 0x5C
		REX::Float32 alphaTestEndTime;								// 0x60
		REX::Float32 alphaTestStartValue;							// 0x64
		REX::Float32 alphaTestEndValue;								// 0x68
		BGSSoundDescriptorForm* ambientSound;						// 0x70
		std::uint32_t fillColor02;									// 0x78
		std::uint32_t fillColor03;									// 0x7C
		std::array<REX::Float32, 3> fillColorScales;				// 0x80
		std::array<REX::Float32, 3> fillColorTimes;					// 0x8C
		std::uint32_t flags;										// 0x98
		REX::Float32 fillTextureUScale;								// 0x9C
		REX::Float32 fillTextureVScale;								// 0xA0
		std::int8_t boneDepth;										// 0xA4
	};

	static_assert(sizeof(EffectShaderData) == 0xA8);
}
