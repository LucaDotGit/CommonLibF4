#pragma once

namespace RE
{
	class ExtraLightDataStruct
	{
	public:
		// members
		REX::Float32 fov{ 0.0_f32 };				 // 00
		REX::Float32 fade{ 0.0_f32 };				 // 04
		REX::Float32 endDistanceCap{ 0.0_f32 };		 // 08
		REX::Float32 shadowDepthBias{ 0.0_f32 };	 // 0C
		REX::Float32 spotNear{ 0.0_f32 };			 // 10
		REX::Float32 volumetricIntensity{ 0.0_f32 }; // 14
	};
	static_assert(sizeof(ExtraLightDataStruct) == 0x18);
}
