#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform
{
	std::int32_t RefCountImpl::GetRefCount() const noexcept
	{
		return refCount;
	}

	void RefCountImpl::AddRef() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		atomicRefCount.fetch_add(1, std::memory_order_acq_rel);
	}

	void RefCountImpl::Release() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);

		if ((atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1) != 0) {
			return;
		}

		try {
			delete this;
		}
		catch (...) {
			REX::Fail("Failed to delete ref object."sv);
		}
	}
}
