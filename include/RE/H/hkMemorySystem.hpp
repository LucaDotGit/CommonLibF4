#pragma once

namespace RE
{
	enum class hkResult : std::int32_t;

	class hkDebugMemorySystem;
	class hkMemoryAllocator;
	class hkMemoryRouter;
	class hkMemorySnapshot;
	class hkOstream;

	class __declspec(novtable) hkMemorySystem
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkMemorySystem };
		inline static constexpr auto VTABLE{ VTABLE::hkMemorySystem };

		using MemoryWalkCallback = void(void* a_start, std::size_t a_size, bool a_allocated, std::int32_t a_pool, void* a_param);

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kPersistent = 1,
			kTemporary = 2,

			kAll = kPersistent | kTemporary,

			kRouter = kPersistent,
			kFrame = kTemporary
		};

		class MemoryStatistics; // TODO
		class FrameInfo;		// TODO

		virtual ~hkMemorySystem(); // 00

		// add
		virtual hkMemoryRouter* MainInit(const FrameInfo& a_info, REX::Enum<Flags, std::int32_t> a_flags) = 0;										 // 01 - { return nullptr; }
		virtual hkResult MainQuit(REX::Enum<Flags, std::int32_t> a_flags) = 0;																		 // 02 - { return hkResult::kSuccess; }
		virtual void ThreadInit(hkMemoryRouter& a_router, const char* a_name, REX::Enum<Flags, std::int32_t> a_flags) = 0;							 // 03
		virtual void ThreadQuit(hkMemoryRouter& a_router, REX::Enum<Flags, std::int32_t> a_flags) = 0;												 // 04
		virtual hkResult GetHeapSoftLimit(std::int32_t a_numBytes);																					 // 05 - { return hkResult::kFailure; }
		virtual std::int32_t GetHeapSoftLimit() const;																								 // 06 - { return -1; }
		virtual bool SolverCanAllocSingleBlock(std::int32_t a_numBytes);																			 // 07 - { return true; }
		virtual bool HeapCanAllocTotal(std::int32_t a_numBytes);																					 // 08 - { return true; }
		virtual void PrintStatistics(hkOstream& a_stream) const = 0;																				 // 09
		virtual void GetMemoryStatistics(MemoryStatistics&) = 0;																					 // 0A
		virtual hkMemoryAllocator* GetUncachedLockedHeapAllocator() = 0;																			 // 0B
		virtual void GarbageCollectThread(hkMemoryRouter& a_router);																				 // 0C - { return; }
		virtual void GarbageCollectShared();																										 // 0D - { return; }
		virtual void GarbageCollect();																												 // 0E - { return; }
		virtual void AdvanceFrame();																												 // 0F - { return; }
		virtual hkDebugMemorySystem* GetDebugInterface();																							 // 10 - { return nullptr; }
		virtual hkResult GetMemorySnapshot(hkMemorySnapshot& a_snapshot) const;																		 // 11 - { return hkResult::kFailure; }
		virtual hkResult GetAllocationCallStack(const void* a_ptr, std::uint64_t* a_callStack, std::int32_t& a_stackSize, std::size_t& a_allocSize); // 12 - { return hkResult::kFailure; }
		virtual void SetHeapScrubValues(std::uint32_t a_allocValue, std::uint32_t a_freeValue);														 // 13 - { return; }
		virtual std::uint32_t IsOk() const;																											 // 14 - { return 1; }
	};
	static_assert(sizeof(hkMemorySystem) == 0x08);
}
