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
		Context* context;						   // 00
		MemoryHeap* heap;						   // 08
		List<EntryPage, EntryPageBase> entryPages; // 10
		List2<Entry, EntryListAccessor> freeNodes; // 20
		Snapshot* activeSnapshot;				   // 58
	};
	static_assert(sizeof(EntryTable) == 0x60);
}
