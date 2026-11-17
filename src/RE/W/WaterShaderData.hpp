#pragma once

namespace RE
{
	class WaterShaderData
	{
	public:
		// members
		REX::Float32 maxDepth;							 // 0x00
		std::uint32_t shallowWaterColor;				 // 0x04
		std::uint32_t deepWaterColor;					 // 0x08
		REX::Float32 shallowFogColorRange;				 // 0x0C
		REX::Float32 deepFogColorRange;					 // 0x10
		REX::Float32 shallowAlpha;						 // 0x14
		REX::Float32 deepAlpha;							 // 0x18
		REX::Float32 shallowFogAlphaRange;				 // 0x1C
		REX::Float32 deepFogAlphaRange;					 // 0x20
		std::uint32_t underwaterFogColor;				 // 0x24
		REX::Float32 underwaterFogAmount;				 // 0x28
		REX::Float32 underwaterFogDistNear;				 // 0x2C
		REX::Float32 underwaterFogDistFar;				 // 0x30
		REX::Float32 normalMagnitude;					 // 0x34
		REX::Float32 normalFalloffShallow;				 // 0x38
		REX::Float32 normalFalloffDeep;					 // 0x3C
		REX::Float32 reflectionAmount;					 // 0x40
		REX::Float32 fresnelAmount;						 // 0x44
		REX::Float32 surfaceEffectFalloff;				 // 0x48
		REX::Float32 displacementForce;					 // 0x4C
		REX::Float32 displacementVelocity;				 // 0x50
		REX::Float32 displacementFalloff;				 // 0x54
		REX::Float32 displacementDampener;				 // 0x58
		REX::Float32 displacementSize;					 // 0x5C
		std::uint32_t reflectionWaterColor;				 // 0x60
		REX::Float32 sunSpecularPower;					 // 0x64
		REX::Float32 sunSpecularMagnitude;				 // 0x68
		REX::Float32 sunSparklePower;					 // 0x6C
		REX::Float32 sunSparkleMagnitude;				 // 0x70
		REX::Float32 lightRadius;						 // 0x74
		REX::Float32 lightBrightness;					 // 0x78
		REX::Float32 shininess;							 // 0x7C
		std::array<REX::Float32, 3> noiseWindDirections; // 0x80
		std::array<REX::Float32, 3> noiseWindSpeeds;	 // 0x8C
		std::array<REX::Float32, 3> amplitude;			 // 0x98
		std::array<REX::Float32, 3> uvScales;			 // 0xA4
		std::array<REX::Float32, 3> noiseFalloff;		 // 0xB0
		REX::Float32 siltAmount;						 // 0xBC
		std::uint32_t lightSiltColor;					 // 0xC0
		std::uint32_t darkSiltColor;					 // 0xC4
		bool ssrEnabled;								 // 0xC8
	};

	static_assert(sizeof(WaterShaderData) == 0xCC);
}
