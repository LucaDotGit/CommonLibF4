#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Snapshot;
	class SnapshotPage;

	class EntryPageBase : public ListNode<EntryPageBase> // 0x00
	{
	public:
		// members
		std::uint32_t useCount;			   // 0x10
		Snapshot* snapshot;				   // 0x18
		SnapshotPage* snapshotPage;		   // 0x20
		SnapshotPage* displaySnapshotPage; // 0x28
		SnapshotPage* tempPage;			   // 0x30
	};

	static_assert(sizeof(EntryPageBase) == 0x38);
}
