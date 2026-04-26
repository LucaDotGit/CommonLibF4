#include "REX/AtomicRef.hpp"

namespace REX
{
	template class AtomicRef<std::int8_t>;
	static_assert(sizeof(AtomicRef<std::int8_t>) == sizeof(std::atomic_ref<std::int8_t>));

	template class AtomicRef<std::uint8_t>;
	static_assert(sizeof(AtomicRef<std::uint8_t>) == sizeof(std::atomic_ref<std::uint8_t>));

	template class AtomicRef<std::int16_t>;
	static_assert(sizeof(AtomicRef<std::int16_t>) == sizeof(std::atomic_ref<std::int16_t>));

	template class AtomicRef<std::uint16_t>;
	static_assert(sizeof(AtomicRef<std::uint16_t>) == sizeof(std::atomic_ref<std::uint16_t>));

	template class AtomicRef<std::int32_t>;
	static_assert(sizeof(AtomicRef<std::int32_t>) == sizeof(std::atomic_ref<std::int32_t>));

	template class AtomicRef<std::uint32_t>;
	static_assert(sizeof(AtomicRef<std::uint32_t>) == sizeof(std::atomic_ref<std::uint32_t>));

	template class AtomicRef<std::int64_t>;
	static_assert(sizeof(AtomicRef<std::int64_t>) == sizeof(std::atomic_ref<std::int64_t>));

	template class AtomicRef<std::uint64_t>;
	static_assert(sizeof(AtomicRef<std::uint64_t>) == sizeof(std::atomic_ref<std::uint64_t>));

	template class AtomicRef<REX::Float32>;
	static_assert(sizeof(AtomicRef<REX::Float32>) == sizeof(std::atomic_ref<REX::Float32>));

	template class AtomicRef<REX::Float64>;
	static_assert(sizeof(AtomicRef<REX::Float64>) == sizeof(std::atomic_ref<REX::Float64>));

	template class AtomicRef<REX::Float128>;
	static_assert(sizeof(AtomicRef<REX::Float128>) == sizeof(std::atomic_ref<REX::Float128>));

	static_assert(AtomicRef<std::int8_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint8_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int16_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint16_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int32_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint32_t>::is_always_lock_free);
	static_assert(AtomicRef<std::int64_t>::is_always_lock_free);
	static_assert(AtomicRef<std::uint64_t>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float32>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float64>::is_always_lock_free);
	static_assert(AtomicRef<REX::Float128>::is_always_lock_free);
}
