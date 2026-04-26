#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class EntryData;
	class EntryPage;

	class SnapshotPage
		: public ListNode<SnapshotPage> // 00
	{
	public:
		// members
		EntryPage* entryPage;			 // 010
		SnapshotPage* olderSnapshotPage; // 018
		SnapshotPage* newerSnapshotPage; // 020
		std::array<EntryData*, 72> data; // 028
	};
	static_assert(sizeof(SnapshotPage) == 0x268);
}
