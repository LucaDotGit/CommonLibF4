#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;
	class NiUpdateData;
}

namespace RE::CELLJobs
{
	class AnimatedRefJobData
	{
	public:
		// members
		NiPointer<NiAVObject> p3d;	// 00
		ObjectRefHandle ref;		// 08
		REX::Float32 time;			// 0C
		std::uint32_t uiFlags;		// 10
		bool allowTransformUpdates; // 14
	};
	static_assert(sizeof(AnimatedRefJobData) == 0x18);

	class TransUpdateFunctor
	{
	public:
		// members
		AnimatedRefJobData* data; // 00
		NiUpdateData* updateData; // 08
	};
	static_assert(sizeof(TransUpdateFunctor) == 0x10);
};
