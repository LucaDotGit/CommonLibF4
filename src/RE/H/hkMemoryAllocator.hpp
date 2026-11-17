#pragma once

namespace RE
{
	enum class hkResult : std::int32_t;

	class __declspec(novtable) hkMemoryAllocator
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkMemoryAllocator;
		inline static constexpr const auto& VTABLE = VTABLE::hkMemoryAllocator;

		using MemoryWalkCallback =
			void(void* a_start, std::size_t a_size, bool a_allocated, std::int32_t a_pool, void* a_param);

		enum class MemoryState : std::int32_t
		{
			Ok = 0,
			OutOfMemory = 1
		};

		class MemoryStatistics
		{
		public:
			// members
			std::int64_t allocated;		 // 0x00
			std::int64_t inUse;			 // 0x08
			std::int64_t peakInUse;		 // 0x10
			std::int64_t available;		 // 0x18
			std::int64_t totalAvailable; // 0x20
			std::int64_t largestBlock;	 // 0x28
		};

		static_assert(sizeof(MemoryStatistics) == 0x30);

		class ExtendedInterface
		{
		public:
			virtual ~ExtendedInterface(); // 0x00

			// add
			virtual void GarbageCollect() = 0;														// 0x01
			virtual void IncrementalGarbageCollect(std::int32_t a_numBlocks) = 0;					// 0x02
			virtual auto SetMemorySoftLimit(std::size_t a_maxMemory) -> hkResult = 0;				// 0x03
			virtual auto GetMemorySoftLimit() const -> std::size_t = 0;								// 0x04
			virtual auto CanAllocTotal(std::int32_t a_numBytes) -> bool = 0;						// 0x05
			virtual auto WalkMemory(MemoryWalkCallback* a_callback, void* a_param) -> hkResult = 0; // 0x06
		};

		static_assert(sizeof(ExtendedInterface) == 0x08);

		virtual ~hkMemoryAllocator(); // 0x00

		// add
		virtual auto BlockAlloc(std::int32_t a_numBytes) -> void*;		  // 0x01
		virtual void BlockFree(void* a_ptr, std::int32_t a_numBytes);	  // 0x02
		virtual auto BufAlloc(std::int32_t& a_reqNumBytesInOut) -> void*; // 0x03
		virtual void BufFree(void* a_ptr, std::int32_t a_numBytes);		  // 0x04
		virtual auto BufRealloc(void* a_ptrOld, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut)
			-> void*;																					  // 0x05
		virtual void BlockAllocBatch(void** a_ptrsOut, std::int32_t a_numPtrs, std::int32_t a_blockSize); // 0x06
		virtual void BlockFreeBatch(void** a_ptrsIn, std::int32_t a_numPtrs, std::int32_t a_blockSize);	  // 0x07
		virtual void GetMemoryStatistics(MemoryStatistics& a_stats) const;								  // 0x08
		virtual auto GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) const -> std::int32_t;  // 0x09
		virtual void ResetPeakMemoryStatistics();														  // 0x0A
		virtual auto GetExtendedInterface() -> ExtendedInterface*;										  // 0x0B

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto malloc(std::size_t a_size) noexcept -> void*;

		template <class T>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto malloc(std::size_t a_count) noexcept -> T*
		{
			return static_cast<T*>(malloc(a_count * sizeof(T)));
		}

		template <class T>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto malloc() noexcept -> T*
		{
			return static_cast<T*>(malloc(sizeof(T)));
		}

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto calloc(std::size_t a_count, std::size_t a_size) noexcept
			-> void*;

		template <class T>
		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto calloc(std::size_t a_count) noexcept -> T*
		{
			return static_cast<T*>(calloc(a_count, sizeof(T)));
		}

		__declspec(noalias) void free(void* a_ptr, std::size_t a_size) noexcept;
	};

	static_assert(sizeof(hkMemoryAllocator) == 0x08);
}
