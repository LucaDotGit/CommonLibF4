#pragma once

#include "RE/B/BSStringPool.hpp"

namespace RE
{
	class BucketTable
	{
	public:
		inline static constexpr auto ENTRY_INDEX_MASK = static_cast<std::uint32_t>(0xFFFF);
		inline static constexpr auto LOCK_INDEX_MASK = static_cast<std::uint32_t>(0x7F);

		class AlignedLock
		{
		public:
			AlignedLock() noexcept = default;
			~AlignedLock() noexcept = default;

			AlignedLock(const AlignedLock&) = delete;
			AlignedLock(AlignedLock&&) = delete;

			auto operator=(const AlignedLock&) -> AlignedLock& = delete;
			auto operator=(AlignedLock&&) -> AlignedLock& = delete;

			auto try_lock_shared() noexcept -> bool;
			auto try_lock() noexcept -> bool;

			void lock_shared() noexcept;
			void lock() noexcept;

			void unlock_shared() noexcept;
			void unlock() noexcept;

		private:
			inline static constexpr auto READ_WRITE_LOCK_ACQUIRED_VALUE = static_cast<std::uint32_t>(0x8000'0000);

			// members
			alignas(0x10) volatile std::uint32_t _lock; // 0x00
		};

		static_assert(sizeof(AlignedLock) == 0x10);

		[[nodiscard]]
		static auto GetSingleton() -> BucketTable&;

		// members
		std::array<BSStringPool::Entry*, 0x1'0000>
			buckets; // 0x00000 - the index is determined by `hash & ENTRY_INDEX_MASK`
		mutable std::array<AlignedLock, 0x1'0000 / 0x200>
			locks;		  // 0x80000 - the index is determined by `hash & LOCK_INDEX_MASK`
		bool initialized; // 0x80800
	};

	static_assert(sizeof(BucketTable) == 0x8'0810);
}
