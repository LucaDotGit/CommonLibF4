#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	auto BSIntrusiveRefCounted::QRefCount() const noexcept -> std::uint32_t
	{
		return refCount;
	}

	auto BSIntrusiveRefCounted::IncRef() const noexcept -> std::uint32_t
	{
		const auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	auto BSIntrusiveRefCounted::DecRef() const noexcept -> std::uint32_t
	{
		const auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
	}
}
