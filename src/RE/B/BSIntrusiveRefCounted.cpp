#include "RE/B/BSIntrusiveRefCounted.hpp"

namespace RE
{
	std::uint32_t BSIntrusiveRefCounted::QRefCount() const noexcept
	{
		return refCount;
	}

	std::uint32_t BSIntrusiveRefCounted::IncRef() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	std::uint32_t BSIntrusiveRefCounted::DecRef() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
	}
}
