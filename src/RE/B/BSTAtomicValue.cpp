#include "RE/B/BSTAtomicValue.hpp"

namespace RE
{
	template class BSTAtomicValue<std::int8_t>;
	static_assert(sizeof(BSTAtomicValue<std::int8_t>) == sizeof(std::int8_t));

	template class BSTAtomicValue<std::uint8_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint8_t>) == sizeof(std::uint8_t));

	template class BSTAtomicValue<std::int16_t>;
	static_assert(sizeof(BSTAtomicValue<std::int16_t>) == sizeof(std::int16_t));

	template class BSTAtomicValue<std::uint16_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint16_t>) == sizeof(std::uint16_t));

	template class BSTAtomicValue<std::int32_t>;
	static_assert(sizeof(BSTAtomicValue<std::int32_t>) == sizeof(std::int32_t));

	template class BSTAtomicValue<std::uint32_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint32_t>) == sizeof(std::uint32_t));

	template class BSTAtomicValue<std::int64_t>;
	static_assert(sizeof(BSTAtomicValue<std::int64_t>) == sizeof(std::int64_t));

	template class BSTAtomicValue<std::uint64_t>;
	static_assert(sizeof(BSTAtomicValue<std::uint64_t>) == sizeof(std::uint64_t));

	template class BSTAtomicValue<REX::Float32>;
	static_assert(sizeof(BSTAtomicValue<REX::Float32>) == sizeof(REX::Float32));

	template class BSTAtomicValue<REX::Float64>;
	static_assert(sizeof(BSTAtomicValue<REX::Float64>) == sizeof(REX::Float64));

	template class BSTAtomicValue<REX::Float128>;
	static_assert(sizeof(BSTAtomicValue<REX::Float128>) == sizeof(REX::Float128));

	static_assert(BSTAtomicValue<std::int8_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::uint8_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::int16_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::uint16_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::int32_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::uint32_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::int64_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<std::uint64_t>::is_always_lock_free);
	static_assert(BSTAtomicValue<REX::Float32>::is_always_lock_free);
	static_assert(BSTAtomicValue<REX::Float64>::is_always_lock_free);
	static_assert(BSTAtomicValue<REX::Float128>::is_always_lock_free);
}
