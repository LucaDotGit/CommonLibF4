#pragma once

namespace RE
{
	class ExtraLightDataStruct
	{
	public:
		// members
		REX::Float32 fov{static_cast<REX::Float32>(0.0)};				  // 0x00
		REX::Float32 fade{static_cast<REX::Float32>(0.0)};				  // 0x04
		REX::Float32 endDistanceCap{static_cast<REX::Float32>(0.0)};	  // 0x08
		REX::Float32 shadowDepthBias{static_cast<REX::Float32>(0.0)};	  // 0x0C
		REX::Float32 spotNear{static_cast<REX::Float32>(0.0)};			  // 0x10
		REX::Float32 volumetricIntensity{static_cast<REX::Float32>(0.0)}; // 0x14
	};

	static_assert(sizeof(ExtraLightDataStruct) == 0x18);
}
