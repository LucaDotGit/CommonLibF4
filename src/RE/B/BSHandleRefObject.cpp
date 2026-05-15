#include "RE/B/BSHandleRefObject.hpp"

namespace RE
{
	std::uint32_t BSHandleRefObject::QRefCount() const noexcept
	{
		return refCount & REF_COUNT_MASK;
	}

	bool BSHandleRefObject::IsValid() const noexcept
	{
		return (refCount & IS_VALID_BIT) != 0;
	}

	std::uint32_t BSHandleRefObject::IncRefCount() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return (atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1) & REF_COUNT_MASK;
	}

	std::uint32_t BSHandleRefObject::DecRefCount() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		auto newRefCount = ((atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1) & REF_COUNT_MASK);

		if (newRefCount != 0) {
			return newRefCount;
		}

		try {
			DeleteThis();
			return 0;
		}
		catch (...) {
			REX::Fail("Failed to delete ref object."sv);
		}
	}
}
