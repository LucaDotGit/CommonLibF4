#pragma once

namespace RE::NonMorphFaceManagement
{
	class InstanceData
	{
	public:
		// members
		void* instanceData; // 00
	};
	static_assert(sizeof(InstanceData) == 0x08);
}
