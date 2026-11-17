#pragma once

namespace RE::TESObjectACTIDefs
{
	class RadioReceiverData
	{
	public:
		// members
		BGSSoundOutput* outputOverride{nullptr};				// 0x00
		REX::Float32 frequency{static_cast<REX::Float32>(0.0)}; // 0x08
		REX::Float32 volume{static_cast<REX::Float32>(0.0)};	// 0x0C
		bool active{false};										// 0x10
		bool noStatic{false};									// 0x11
	};

	static_assert(sizeof(RadioReceiverData) == 0x18);
}
