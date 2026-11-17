#include "RE/B/BSInputEnableLayer.hpp"

namespace RE
{
	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	auto BSInputEnableLayer::GetFormType() const noexcept -> FormType
	{
		return FORM_TYPE;
	}

	auto BSInputEnableLayer::IncRef() const noexcept -> std::uint32_t
	{
		const auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	auto BSInputEnableLayer::DecRef() const noexcept -> std::uint32_t
	{
		try {
			using FuncType = decltype(&BSInputEnableLayer::DecRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSInputEnableLayer::DecRef);
			return std::invoke(FUNC, this);
		}
		catch (...) {
			REX::Fail("Failed to decrement ref count."sv);
		}
	}
}
