#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;
}

namespace RE::CELLJobs
{
	class AnimatedRefJobData
	{
	public:
		// members
		NiPointer<NiAVObject> object3D; // 0x00
		ObjectRefHandle ref;			// 0x08
		REX::Float32 time;				// 0x0C
		std::uint32_t flags;			// 0x10
		bool allowTransformUpdates;		// 0x14
	};

	static_assert(sizeof(AnimatedRefJobData) == 0x18);
};
