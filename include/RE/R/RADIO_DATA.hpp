#pragma once

namespace RE
{
	class RADIO_DATA
	{
	public:
		// members
		REX::Float32 radioStation{ 0.0_f32 };		// 00
		REX::Float32 minWeakSignalRange{ 0.0_f32 }; // 04
		REX::Float32 maxWeakSignalRange{ 0.0_f32 }; // 08
		bool ignoreDistanceCheck{ false };			// 0C
	};
	static_assert(sizeof(RADIO_DATA) == 0x10);
}
