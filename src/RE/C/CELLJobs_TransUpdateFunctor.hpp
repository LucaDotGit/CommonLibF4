#pragma once

namespace RE
{
	class NiUpdateData;
}

namespace RE::CELLJobs
{
	class AnimatedRefJobData;

	class TransUpdateFunctor
	{
	public:
		// members
		AnimatedRefJobData* data; // 0x00
		NiUpdateData* updateData; // 0x08
	};

	static_assert(sizeof(TransUpdateFunctor) == 0x10);
};
