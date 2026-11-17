#pragma once

#include "Scaleform/L/List.hpp"
#include "Scaleform/R/Render_ContextImpl_Entry.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryListAccessor.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryPage.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryPageBase.hpp"

namespace Scaleform
{
	class MemoryHeap;
}

namespace Scaleform::Render::ContextImpl
{
	class Context;
	class Snapshot;

	class EntryTable
	{
	public:
		// members
		Context* context;						   // 0x00
		MemoryHeap* heap;						   // 0x08
		List<EntryPage, EntryPageBase> entryPages; // 0x10
		List2<Entry, EntryListAccessor> freeNodes; // 0x20
		Snapshot* activeSnapshot;				   // 0x58
	};

	static_assert(sizeof(EntryTable) == 0x60);
}
