#include "RE/B/BSHandleRefObject.hpp"

namespace RE
{
	auto BSHandleRefObject::QRefCount() const noexcept -> std::uint32_t
	{
		return refCount & REF_COUNT_MASK;
	}

	auto BSHandleRefObject::IsValid() const noexcept -> bool
	{
		return (refCount & IS_VALID_BIT) != 0;
	}

	auto BSHandleRefObject::IncRefCount() const noexcept -> std::uint32_t
	{
		const auto atomicRefCount = REX::AtomicRef(refCount);
		return (atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1) & REF_COUNT_MASK;
	}

	auto BSHandleRefObject::DecRefCount() const noexcept -> std::uint32_t
	{
		const auto atomicRefCount = REX::AtomicRef(refCount);

		const auto newRefCount = ((atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1) & REF_COUNT_MASK);
		if (newRefCount != 0) {
			return newRefCount;
		}

		try {
			DeleteThis();
			return 0;
		}
		catch (...) {
			REX::Fail("Failed to delete object."sv);
		}
	}
}
