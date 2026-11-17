#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class EntryData;
	class EntryPage;

	class SnapshotPage : public ListNode<SnapshotPage> // 0x00
	{
	public:
		// members
		EntryPage* entryPage;			 // 0x010
		SnapshotPage* olderSnapshotPage; // 0x018
		SnapshotPage* newerSnapshotPage; // 0x020
		std::array<EntryData*, 72> data; // 0x028
	};

	static_assert(sizeof(SnapshotPage) == 0x268);
}
