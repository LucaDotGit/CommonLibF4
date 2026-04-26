#pragma once

namespace RE::TESAudio
{
	class SnapshotEntry
	{
	public:
		// members
		BGSSoundCategorySnapshot* snapForm; // 00
		REX::Float32 transitionSecs;		// 08
	};
	static_assert(sizeof(SnapshotEntry) == 0x10);
}
