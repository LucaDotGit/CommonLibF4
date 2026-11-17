#pragma once

#include "Scaleform/P/Ptr.hpp"
#include "Scaleform/R/Render_ContextImpl_EntryTable.hpp"
#include "Scaleform/R/Render_ContextImpl_RTHandle.hpp"
#include "Scaleform/R/Render_ContextImpl_RenderNotify.hpp"
#include "Scaleform/T/ThreadId.hpp"

namespace Scaleform
{
	class Event;
	class MemoryHeap;
}

namespace Scaleform::Render::ContextImpl
{
	class ContextCaptureNotify;
	class ContextLock;
	class Snapshot;

	class Context
	{
	public:
		// members
		MemoryHeap* heap;							   // 0x000
		ThreadId createThreadID;					   // 0x008
		EntryTable table;							   // 0x010
		Ptr<ContextLock> captureLock;				   // 0x070
		List<ContextCaptureNotify> captureNotifyList;  // 0x078
		RenderNotify* renderer;						   // 0x088
		bool multiThreadedUse;						   // 0x090
		bool nextCaptureCalledInFrame;				   // 0x091
		volatile bool captureCalled;				   // 0x092
		volatile bool diChangesRequired;			   // 0x093
		volatile bool shutdownRequested;			   // 0x094
		Event* volatile shutdownEvent;				   // 0x098
		RenderNotify::ContextNode renderNode;		   // 0x0A0
		List<RTHandle::HandleData> rtHandleList;	   // 0x0B8
		std::array<Snapshot*, 4> snapshots;			   // 0x0C8
		std::array<std::uint64_t, 4> snapshotFrameIDs; // 0x0E8
		std::uint64_t finalizedFrameID;				   // 0x108
	};

	static_assert(sizeof(Context) == 0x110);
}
