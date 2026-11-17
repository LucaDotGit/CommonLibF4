#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSSoundHandle.hpp"

namespace RE::TESAudio
{
	class RepeaterData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSSoundHandle currSound; // 0x04
		TESSound* soundBase;	 // 0x10
		REX::Float32 countdown;	 // 0x18
	};

	static_assert(sizeof(RepeaterData) == 0x20);
}
