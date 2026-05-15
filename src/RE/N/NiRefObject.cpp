#include "RE/N/NiRefObject.hpp"

namespace RE
{
	NiRefObject::NiRefObject()
	{
		REL::EmplaceVtable(this);

		auto atomicObjectCount = REX::AtomicRef(GetTotalObjectCount());
		atomicObjectCount.fetch_add(1, std::memory_order_acq_rel);
	}

	NiRefObject::~NiRefObject()
	{
		auto atomicObjectCount = REX::AtomicRef(GetTotalObjectCount());
		atomicObjectCount.fetch_sub(1, std::memory_order_acq_rel);
	}

	std::uint32_t& NiRefObject::GetTotalObjectCount()
	{
		static const auto TOTAL_OBJECT_COUNT = REL::Relocation<std::uint32_t*>{ ID::NiRefObject::TotalObjectCount };
		return *TOTAL_OBJECT_COUNT;
	}

	std::uint32_t NiRefObject::QRefCount() const noexcept
	{
		return refCount;
	}

	std::uint32_t NiRefObject::IncRefCount() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	std::uint32_t NiRefObject::DecRefCount() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		auto newRefCount = atomicRefCount.fetch_sub(1, std::memory_order_acq_rel) - 1;

		if (newRefCount != 0) {
			return newRefCount;
		}

		try {
			DeleteThis();
		}
		catch (...) {
			REX::Fail("Failed to delete ref object."sv);
		}

		return 0;
	}
}
