#pragma once

namespace RE::TESObjectACTIDefs
{
	class RadioReceiverData
	{
	public:
		// members
		BGSSoundOutput* outputOverride{ nullptr }; // 00
		REX::Float32 frequency{ 0.0_f32 };		   // 08
		REX::Float32 volume{ 0.0_f32 };			   // 0C
		bool active{ false };					   // 10
		bool noStatic{ false };					   // 11
	};
	static_assert(sizeof(RadioReceiverData) == 0x18);
}
