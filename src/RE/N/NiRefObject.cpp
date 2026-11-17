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

	void NiRefObject::DeleteThis() const
	{
		delete this;
	}

	auto NiRefObject::GetTotalObjectCount() noexcept -> std::uint32_t&
	{
		static const auto TOTAL_OBJECT_COUNT = REL::Relocation<std::uint32_t*>(ID::NiRefObject::TotalObjectCount);
		return *TOTAL_OBJECT_COUNT;
	}

	auto NiRefObject::QRefCount() const noexcept -> std::uint32_t
	{
		return refCount;
	}

	auto NiRefObject::IncRefCount() const noexcept -> std::uint32_t
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	auto NiRefObject::DecRefCount() const noexcept -> std::uint32_t
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
			REX::Fail("Failed to delete object."sv);
		}

		return 0;
	}
}
