#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSSoundHandle.hpp"

namespace RE::TESAudio
{
	class RepeaterData
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSSoundHandle currSound; // 04
		TESSound* soundBase;	 // 10
		REX::Float32 countdown;	 // 18
	};
	static_assert(sizeof(RepeaterData) == 0x20);
}
