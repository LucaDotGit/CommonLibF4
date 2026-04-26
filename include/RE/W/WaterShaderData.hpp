#pragma once

namespace RE
{
	class WaterShaderData
	{
	public:
		// members
		REX::Float32 maxDepth;							 // 00
		std::uint32_t shallowWaterColor;				 // 04
		std::uint32_t deepWaterColor;					 // 08
		REX::Float32 shallowFogColorRange;				 // 0C
		REX::Float32 deepFogColorRange;					 // 10
		REX::Float32 shallowAlpha;						 // 14
		REX::Float32 deepAlpha;							 // 18
		REX::Float32 shallowFogAlphaRange;				 // 1C
		REX::Float32 deepFogAlphaRange;					 // 20
		std::uint32_t underwaterFogColor;				 // 24
		REX::Float32 underwaterFogAmount;				 // 28
		REX::Float32 underwaterFogDistNear;				 // 2C
		REX::Float32 underwaterFogDistFar;				 // 30
		REX::Float32 normalMagnitude;					 // 34
		REX::Float32 normalFalloffShallow;				 // 38
		REX::Float32 normalFalloffDeep;					 // 3C
		REX::Float32 reflectionAmount;					 // 40
		REX::Float32 fresnelAmount;						 // 44
		REX::Float32 surfaceEffectFalloff;				 // 48
		REX::Float32 displacementForce;					 // 4C
		REX::Float32 displacementVelocity;				 // 50
		REX::Float32 displacementFalloff;				 // 54
		REX::Float32 displacementDampener;				 // 58
		REX::Float32 displacementSize;					 // 5C
		std::uint32_t reflectionWaterColor;				 // 60
		REX::Float32 sunSpecularPower;					 // 64
		REX::Float32 sunSpecularMagnitude;				 // 68
		REX::Float32 sunSparklePower;					 // 6C
		REX::Float32 sunSparkleMagnitude;				 // 70
		REX::Float32 lightRadius;						 // 74
		REX::Float32 lightBrightness;					 // 78
		REX::Float32 shininess;							 // 7C
		std::array<REX::Float32, 3> noiseWindDirections; // 80
		std::array<REX::Float32, 3> noiseWindSpeeds;	 // 8C
		std::array<REX::Float32, 3> amplitude;			 // 98
		std::array<REX::Float32, 3> uvScales;			 // A4
		std::array<REX::Float32, 3> noiseFalloff;		 // B0
		REX::Float32 siltAmount;						 // BC
		std::uint32_t lightSiltColor;					 // C0
		std::uint32_t darkSiltColor;					 // C4
		bool ssrEnabled;								 // C8
	};
	static_assert(sizeof(WaterShaderData) == 0xCC);
}
