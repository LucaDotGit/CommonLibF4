#include "F4SE/PapyrusInterface.hpp"

namespace F4SE::Impl
{
	struct F4SEPapyrusInterface final
	{
		std::uint32_t interfaceVersion;
		bool(F4SE_API* Register)(void*);
		void(F4SE_API* GetExternalEventRegistrations)(const char*, void*, void*);
	};

	[[nodiscard]] static const F4SEPapyrusInterface& GetProxy(const PapyrusInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SEPapyrusInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t PapyrusInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	bool PapyrusInterface::Register(REX::NotNull<REX::Observer<RegisterFunctions*>> a_callback) const
	{
		const auto result = Impl::GetProxy(this).Register(reinterpret_cast<void*>(a_callback.get()));
		if (!result) [[unlikely]] {
			REX::Fail("Failed to register papyrus callback."sv);
		}

		return result;
	}

	void PapyrusInterface::GetExternalEventRegistrations(const char* a_eventName, void* a_data, REX::NotNull<REX::Observer<RegistrantFunctor*>> a_functor) const
	{
		Impl::GetProxy(this).GetExternalEventRegistrations(a_eventName, a_data, reinterpret_cast<void*>(a_functor.get()));
	}
}
