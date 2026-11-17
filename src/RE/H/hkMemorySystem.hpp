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
		inline static constexpr const auto& RTTI = RTTI::hkMemorySystem;
		inline static constexpr const auto& VTABLE = VTABLE::hkMemorySystem;

		using MemoryWalkCallback =
			void(void* a_start, std::size_t a_size, bool a_allocated, std::int32_t a_pool, void* a_param);

		enum class Flags : std::uint32_t
		{
			None = 0,
			Persistent = 1,
			Temporary = 2,

			Router = Persistent,
			Frame = Temporary
		};

		class MemoryStatistics; // To-Do
		class FrameInfo;		// To-Do

		virtual ~hkMemorySystem(); // 0x00

		// add
		virtual auto MainInit(const FrameInfo& a_info, REX::Enum<Flags, std::int32_t> a_flags)
			-> hkMemoryRouter* = 0; // 0x01 - { return nullptr; }
		virtual auto MainQuit(REX::Enum<Flags, std::int32_t> a_flags)
			-> hkResult = 0; // 0x02 - { return hkResult::Success; }
		virtual void ThreadInit(
			hkMemoryRouter& a_router,
			const char* a_name,
			REX::Enum<Flags, std::int32_t> a_flags) = 0;											   // 0x03
		virtual void ThreadQuit(hkMemoryRouter& a_router, REX::Enum<Flags, std::int32_t> a_flags) = 0; // 0x04
		virtual auto GetHeapSoftLimit(std::int32_t a_numBytes) -> hkResult;		 // 0x05 - { return hkResult::Failure; }
		virtual auto GetHeapSoftLimit() const -> std::int32_t;					 // 0x06 - { return -1; }
		virtual auto SolverCanAllocSingleBlock(std::int32_t a_numBytes) -> bool; // 0x07 - { return true; }
		virtual auto HeapCanAllocTotal(std::int32_t a_numBytes) -> bool;		 // 0x08 - { return true; }
		virtual void PrintStatistics(hkOstream& a_stream) const = 0;			 // 0x09
		virtual void GetMemoryStatistics(MemoryStatistics&) = 0;				 // 0x0A
		virtual auto GetUncachedLockedHeapAllocator() -> hkMemoryAllocator* = 0; // 0x0B
		virtual void GarbageCollectThread(hkMemoryRouter& a_router);			 // 0x0C - { return; }
		virtual void GarbageCollectShared();									 // 0x0D - { return; }
		virtual void GarbageCollect();											 // 0x0E - { return; }
		virtual void AdvanceFrame();											 // 0x0F - { return; }
		virtual auto GetDebugInterface() -> hkDebugMemorySystem*;				 // 0x10 - { return nullptr; }
		virtual auto GetMemorySnapshot(hkMemorySnapshot& a_snapshot) const
			-> hkResult; // 0x11 - { return hkResult::Failure; }
		virtual auto GetAllocationCallStack(
			const void* a_ptr,
			std::uint64_t* a_callStack,
			std::int32_t& a_stackSize,
			std::size_t& a_allocSize) -> hkResult; // 0x12 - { return hkResult::Failure; }
		virtual void SetHeapScrubValues(std::uint32_t a_allocValue, std::uint32_t a_freeValue); // 0x13 - { return; }
		virtual auto IsOk() const -> std::uint32_t;												// 0x14 - { return 1; }
	};

	static_assert(sizeof(hkMemorySystem) == 0x08);
}
