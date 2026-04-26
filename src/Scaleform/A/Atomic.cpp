#include "Scaleform/A/Atomic.hpp"

namespace Scaleform
{
	template class AtomicValueBase<std::int8_t>;
	static_assert(sizeof(AtomicValueBase<std::int8_t>) == sizeof(std::int8_t));

	template class AtomicValueBase<std::uint8_t>;
	static_assert(sizeof(AtomicValueBase<std::uint8_t>) == sizeof(std::uint8_t));

	template class AtomicValueBase<std::int16_t>;
	static_assert(sizeof(AtomicValueBase<std::int16_t>) == sizeof(std::int16_t));

	template class AtomicValueBase<std::uint16_t>;
	static_assert(sizeof(AtomicValueBase<std::uint16_t>) == sizeof(std::uint16_t));

	template class AtomicValueBase<std::int32_t>;
	static_assert(sizeof(AtomicValueBase<std::int32_t>) == sizeof(std::int32_t));

	template class AtomicValueBase<std::uint32_t>;
	static_assert(sizeof(AtomicValueBase<std::uint32_t>) == sizeof(std::uint32_t));

	template class AtomicValueBase<std::int64_t>;
	static_assert(sizeof(AtomicValueBase<std::int64_t>) == sizeof(std::int64_t));

	template class AtomicValueBase<std::uint64_t>;
	static_assert(sizeof(AtomicValueBase<std::uint64_t>) == sizeof(std::uint64_t));

	template class AtomicValueBase<REX::Float32>;
	static_assert(sizeof(AtomicValueBase<REX::Float32>) == sizeof(REX::Float32));

	template class AtomicValueBase<REX::Float64>;
	static_assert(sizeof(AtomicValueBase<REX::Float64>) == sizeof(REX::Float64));

	template class AtomicValueBase<REX::Float128>;
	static_assert(sizeof(AtomicValueBase<REX::Float128>) == sizeof(REX::Float128));

	static_assert(AtomicValueBase<std::int8_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::uint8_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::int16_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::uint16_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::int32_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::uint32_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::int64_t>::is_always_lock_free);
	static_assert(AtomicValueBase<std::uint64_t>::is_always_lock_free);
	static_assert(AtomicValueBase<REX::Float32>::is_always_lock_free);
	static_assert(AtomicValueBase<REX::Float64>::is_always_lock_free);
	static_assert(AtomicValueBase<REX::Float128>::is_always_lock_free);

	template class AtomicInt<std::int8_t>;
	static_assert(sizeof(AtomicInt<std::int8_t>) == sizeof(std::int8_t));

	template class AtomicInt<std::uint8_t>;
	static_assert(sizeof(AtomicInt<std::uint8_t>) == sizeof(std::uint8_t));

	template class AtomicInt<std::int16_t>;
	static_assert(sizeof(AtomicInt<std::int16_t>) == sizeof(std::int16_t));

	template class AtomicInt<std::uint16_t>;
	static_assert(sizeof(AtomicInt<std::uint16_t>) == sizeof(std::uint16_t));

	template class AtomicInt<std::int32_t>;
	static_assert(sizeof(AtomicInt<std::int32_t>) == sizeof(std::int32_t));

	template class AtomicInt<std::uint32_t>;
	static_assert(sizeof(AtomicInt<std::uint32_t>) == sizeof(std::uint32_t));

	template class AtomicInt<std::int64_t>;
	static_assert(sizeof(AtomicInt<std::int64_t>) == sizeof(std::int64_t));

	template class AtomicInt<std::uint64_t>;
	static_assert(sizeof(AtomicInt<std::uint64_t>) == sizeof(std::uint64_t));

	static_assert(AtomicInt<std::int8_t>::is_always_lock_free);
	static_assert(AtomicInt<std::uint8_t>::is_always_lock_free);
	static_assert(AtomicInt<std::int16_t>::is_always_lock_free);
	static_assert(AtomicInt<std::uint16_t>::is_always_lock_free);
	static_assert(AtomicInt<std::int32_t>::is_always_lock_free);
	static_assert(AtomicInt<std::uint32_t>::is_always_lock_free);
	static_assert(AtomicInt<std::int64_t>::is_always_lock_free);
	static_assert(AtomicInt<std::uint64_t>::is_always_lock_free);
}
