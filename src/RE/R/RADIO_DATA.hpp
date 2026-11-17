#pragma once

namespace RE
{
	class RADIO_DATA
	{
	public:
		// members
		REX::Float32 radioStation{static_cast<REX::Float32>(0.0)};		 // 0x00
		REX::Float32 minWeakSignalRange{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 maxWeakSignalRange{static_cast<REX::Float32>(0.0)}; // 0x08
		bool ignoreDistanceCheck{false};								 // 0x0C
	};

	static_assert(sizeof(RADIO_DATA) == 0x10);
}
