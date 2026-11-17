#pragma once

#include "Scaleform/L/List.hpp"
#include "Scaleform/L/Lock.hpp"

namespace Scaleform::Heap
{
	class MemVisitor;
	class SegVisitor;
}

namespace Scaleform
{
	class StatBag;
	class SysAllocPaged;
	class AllocInfo;

	class __declspec(novtable) MemoryHeap : public ListNode<MemoryHeap> // 0x08
	{
	public:
		enum class HeapFlags : std::uint32_t
		{
			None = 0,
			ThreadUnsafe = 1 << 0,
			FastTinyBlocks = 1 << 1,
			FixedGranularity = 1 << 2,
			Root = 1 << 3,
			NoDebugInfo = 1 << 4,
			UserDebug = 1 << 12
		};

		enum class RootHeapParameters : std::int32_t
		{
			MinAlign = 1 << 4,
			Granularity = 1 << 14,
			Reserve = 1 << 14,
			Threshold = 1 << 18,
			Limit = 0
		};

		using ChildListType = List<MemoryHeap>;

		class HeapDesc
		{
		public:
			// members
			std::uint32_t flags{0};											 // 0x00
			std::size_t minAlign{0x10};										 // 0x08
			std::size_t granularity{static_cast<std::size_t>(0x08) * 0x400}; // 0x10
			std::size_t reserve{static_cast<std::size_t>(0x08) * 0x400};	 // 0x18
			std::size_t threshold{static_cast<std::size_t>(-1)};			 // 0x20
			std::size_t limit{0};											 // 0x28
			std::size_t heapID{0};											 // 0x30
			std::size_t arena{0};											 // 0x38
		};

		static_assert(sizeof(HeapDesc) == 0x40);

		class HeapInfo
		{
		public:
			// members
			HeapDesc desc;		// 0x00
			MemoryHeap* parent; // 0x40
			char* name;			// 0x48
		};

		static_assert(sizeof(HeapInfo) == 0x50);

		class __declspec(novtable) HeapVisitor
		{
		public:
			virtual ~HeapVisitor() = default; // 0x00

			// add
			virtual void Visit(MemoryHeap* a_parentHeap, MemoryHeap* a_childHeap) = 0; // 0x01
		};

		static_assert(sizeof(HeapVisitor) == 0x08);

		class __declspec(novtable) LimitHandler
		{
		public:
			virtual ~LimitHandler() = default; // 0x00

			// add
			virtual auto OnExceedLimit(MemoryHeap* a_heap, std::size_t a_overLimit) -> bool = 0; // 0x01
			virtual void OnFreeSegment(MemoryHeap* a_heap, std::size_t a_freeingSize) = 0;		 // 0x02
		};

		static_assert(sizeof(LimitHandler) == 0x08);

		class __declspec(novtable) HeapTracer
		{
		public:
			virtual ~HeapTracer() = default; // 0x00

			// add
			virtual void OnCreateHeap(const MemoryHeap* a_heap) = 0;  // 0x01
			virtual void OnDestroyHeap(const MemoryHeap* a_heap) = 0; // 0x02
			virtual void OnAlloc(
				const MemoryHeap* a_heap,
				std::size_t a_size,
				std::align_val_t a_align,
				std::uint32_t a_sid,
				const void* a_ptr) = 0; // 0x03
			virtual void OnRealloc(
				const MemoryHeap* a_heap,
				const void* a_oldPtr,
				std::size_t a_newSize,
				const void* a_newPtr) = 0;										  // 0x04
			virtual void OnFree(const MemoryHeap* a_heap, const void* a_ptr) = 0; // 0x05
		};

		static_assert(sizeof(HeapTracer) == 0x08);

		class RootStats
		{
		public:
			// members
			std::size_t sysMemFootprint;	  // 0x00
			std::size_t sysMemUsedSpace;	  // 0x08
			std::size_t pageMapFootprint;	  // 0x10
			std::size_t pageMapUsedSpace;	  // 0x18
			std::size_t bookkeepingFootprint; // 0x20
			std::size_t bookkeepingUsedSpace; // 0x28
			std::size_t debugInfoFootprint;	  // 0x30
			std::size_t debugInfoUsedSpace;	  // 0x38
			std::size_t userDebugFootprint;	  // 0x40
			std::size_t userDebugUsedSpace;	  // 0x48
		};

		static_assert(sizeof(RootStats) == 0x50);

		virtual ~MemoryHeap() = default; // 0x00

		// add
		virtual void CreateArena(std::size_t a_arena, SysAllocPaged* a_sysAlloc) = 0;			// 0x01
		virtual void DestroyArena(std::size_t a_arena) = 0;										// 0x02
		virtual auto ArenaIsEmpty(std::size_t a_arena) -> bool = 0;								// 0x03
		virtual auto CreateHeap(const char* a_name, const HeapDesc& a_desc) -> MemoryHeap* = 0; // 0x04
		virtual void SetLimitHandler(LimitHandler* a_handler) = 0;								// 0x05
		virtual void SetLimit(std::size_t a_newLimit) = 0;										// 0x06
		virtual void AddRef() = 0;																// 0x07
		virtual void Release() = 0;																// 0x08
		virtual auto Alloc(std::size_t a_size, const AllocInfo* a_info = nullptr) -> void* = 0; // 0x09
		virtual auto Alloc(
			std::size_t a_size,
			std::align_val_t a_align,
			const AllocInfo* a_info = nullptr) -> void* = 0;					  // 0x0A
		virtual auto Realloc(void* a_oldPtr, std::size_t a_newSize) -> void* = 0; // 0x0B
		virtual void Free(void* a_ptr) = 0;										  // 0x0C
		virtual auto AllocAutoHeap(
			const void* a_thisPtr,
			std::size_t a_size,
			const AllocInfo* a_info = nullptr) -> void* = 0; // 0x0D
		virtual auto AllocAutoHeap(
			const void* a_thisPtr,
			std::size_t a_size,
			std::align_val_t a_align,
			const AllocInfo* a_info = nullptr) -> void* = 0;						   // 0x0E
		virtual auto GetAllocHeap(const void* a_thisPtr) -> MemoryHeap* = 0;		   // 0x0F
		virtual auto GetUsableSize(const void* a_ptr) -> std::size_t = 0;			   // 0x10
		virtual auto AllocSysDirect(std::size_t a_size) -> void* = 0;				   // 0x11
		virtual void FreeSysDirect(void* a_ptr, std::size_t a_size) = 0;			   // 0x12
		virtual auto GetStats(StatBag* a_bag) -> bool = 0;							   // 0x13
		virtual auto GetFootprint() const -> std::size_t = 0;						   // 0x14
		virtual auto GetTotalFootprint() const -> std::size_t = 0;					   // 0x15
		virtual auto GetUsedSpace() const -> std::size_t = 0;						   // 0x16
		virtual auto GetTotalUsedSpace() const -> std::size_t = 0;					   // 0x17
		virtual void GetRootStats(RootStats* a_stats) = 0;							   // 0x18
		virtual void VisitMem(Heap::MemVisitor* a_visitor, std::uint32_t a_flags) = 0; // 0x19
		virtual void VisitRootSegments(Heap::SegVisitor* a_visitor) = 0;			   // 0x1A
		virtual void VisitHeapSegments(Heap::SegVisitor* a_visitor) const = 0;		   // 0x1B
		virtual void SetTracer(HeapTracer* a_tracer) = 0;							   // 0x1C
		virtual void DestroyItself() = 0;											   // 0x1D
		virtual void UltimateCheck() = 0;											   // 0x1E
		virtual void ReleaseCachedMem() = 0;										   // 0x1F
		virtual auto DumpMemoryLeaks() -> bool = 0;									   // 0x20
		virtual void CheckIntegrity() const = 0;									   // 0x21
		virtual void GetUserDebugStats(RootStats* a_stats) const = 0;				   // 0x22

		void AssignToCurrentThread() noexcept
		{
			ownerThreadID = REX::W32::GetCurrentThreadId();
		}

		// members
		std::size_t selfSize;			 // 0x18
		volatile std::uint32_t refCount; // 0x20
		std::size_t ownerThreadID;		 // 0x28
		void* autoRelease;				 // 0x30
		HeapInfo info;					 // 0x38
		ChildListType childHeaps;		 // 0x88
		mutable Lock heapLock;			 // 0x98
		bool useLocks;					 // 0xC0
		bool trackDebugInfo;			 // 0xC1
	};

	static_assert(sizeof(MemoryHeap) == 0xC8);
}
