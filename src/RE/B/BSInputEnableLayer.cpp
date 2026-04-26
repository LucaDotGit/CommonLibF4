#include "RE/B/BSInputEnableLayer.hpp"

namespace RE
{
	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	FormType BSInputEnableLayer::GetFormType() const noexcept
	{
		return FORM_TYPE;
	}

	std::uint32_t BSInputEnableLayer::IncRef() noexcept
	{
		auto atomicRefCount = REX::AtomicRef(refCount);
		return atomicRefCount.fetch_add(1, std::memory_order_acq_rel) + 1;
	}

	std::uint32_t BSInputEnableLayer::DecRef() noexcept
	{
		try {
			using FuncType = decltype(&BSInputEnableLayer::DecRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSInputEnableLayer::DecRef };
			return std::invoke(FUNC, this);
		}
		catch (...) {
			REX::QuickFail("Failed to decrement input enable layer ref count."sv);
		}
	}
}
