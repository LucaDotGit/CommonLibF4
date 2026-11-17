#include "F4SE/PapyrusInterface.hpp"

#include "F4SE/Core.hpp"
#include "REX/Macros.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SEPapyrusInterface final
		{
		public:
			F4SEPapyrusInterface() = delete;
			~F4SEPapyrusInterface() = delete;

			F4SEPapyrusInterface(const F4SEPapyrusInterface&) = delete;
			F4SEPapyrusInterface(F4SEPapyrusInterface&&) = delete;

			auto operator=(const F4SEPapyrusInterface&) -> F4SEPapyrusInterface& = delete;
			auto operator=(F4SEPapyrusInterface&&) -> F4SEPapyrusInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			bool(F4SE_API* doRegister)(F4SE::PapyrusInterface::RegisterCallback*);
			void(F4SE_API* getExternalEventRegistrations)(
				const char*,
				void*,
				F4SE::PapyrusInterface::ExternalEventCallback*);
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const PapyrusInterface& a_interface) noexcept -> const F4SEPapyrusInterface&
		{
			return reinterpret_cast<const F4SEPapyrusInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto PapyrusInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	void PapyrusInterface::Register(REX::NotNull<REX::Observer<RegisterCallback*>> a_callback) const
	{
		if (!Impl::GetProxy(*this).doRegister(a_callback.get())) [[unlikely]] {
			REX::Fail("Failed to register Papyrus callback."sv);
		}
	}

	void PapyrusInterface::GetExternalEventRegistrations(
		const char* a_eventName,
		void* a_data,
		REX::NotNull<REX::Observer<ExternalEventCallback*>> a_functor) const
	{
		Impl::GetProxy(*this).getExternalEventRegistrations(a_eventName, a_data, a_functor.get());
	}
}
