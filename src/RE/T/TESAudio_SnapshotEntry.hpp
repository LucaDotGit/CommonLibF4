#pragma once

namespace RE::TESAudio
{
	class SnapshotEntry
	{
	public:
		// members
		BGSSoundCategorySnapshot* snapForm; // 0x00
		REX::Float32 transitionSecs;		// 0x08
	};

	static_assert(sizeof(SnapshotEntry) == 0x10);
}
