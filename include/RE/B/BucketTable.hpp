#pragma once

#include "RE/B/BSSpinLockPolicy.hpp"
#include "RE/B/BSStringPool.hpp"

namespace RE
{
	class BucketTable
	{
	public:
		inline static constexpr auto ENTRY_INDEX_MASK = 0xFFFFui32;
		inline static constexpr auto LOCK_INDEX_MASK = 0x7Fui32;

		class AlignedLock
		{
		public:
			AlignedLock() noexcept = default;
			~AlignedLock() noexcept = default;

			AlignedLock(const AlignedLock&) = delete;
			AlignedLock(AlignedLock&&) = delete;

			AlignedLock& operator=(const AlignedLock&) = delete;
			AlignedLock& operator=(AlignedLock&&) = delete;

			bool try_lock_shared() noexcept;
			bool try_lock() noexcept;

			void lock_shared() noexcept;
			void lock() noexcept;

			void unlock_shared() noexcept;
			void unlock() noexcept;

		private:
			inline static constexpr auto READ_WRITE_LOCK_ACQUIRED_VALUE = 0x80000000ui32;

			// members
			alignas(0x10) volatile std::uint32_t _lock; // 00
		};
		static_assert(sizeof(AlignedLock) == 0x10);

		[[nodiscard]] static BucketTable& GetSingleton();

		// members
		std::array<BSStringPool::Entry*, 0x10000> buckets;		// 00000 - the Index is determined by `hash & ENTRY_INDEX_MASK`
		mutable std::array<AlignedLock, 0x10000 / 0x200> locks; // 80000 - the Index is determined by `hash & LOCK_INDEX_MASK`
		bool initialized;										// 80800
	};
	static_assert(sizeof(BucketTable) == 0x80810);

	extern template class BSAutoLockReadLockPolicy<BucketTable::AlignedLock>;
	extern template class BSAutoLockWriteLockPolicy<BucketTable::AlignedLock>;
}
