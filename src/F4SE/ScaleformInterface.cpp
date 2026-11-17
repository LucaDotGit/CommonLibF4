#include "F4SE/ScaleformInterface.hpp"

#include "F4SE/Core.hpp"
#include "REX/Macros.hpp"
#include "REX/Message.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SEScaleformInterface final
		{
		public:
			F4SEScaleformInterface() = delete;
			~F4SEScaleformInterface() = delete;

			F4SEScaleformInterface(const F4SEScaleformInterface&) = delete;
			F4SEScaleformInterface(F4SEScaleformInterface&&) = delete;

			auto operator=(const F4SEScaleformInterface&) -> F4SEScaleformInterface& = delete;
			auto operator=(F4SEScaleformInterface&&) -> F4SEScaleformInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			bool(F4SE_API* doRegister)(const char*, F4SE::ScaleformInterface::RegisterCallback*);
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const ScaleformInterface& a_interface) noexcept -> const F4SEScaleformInterface&
		{
			return reinterpret_cast<const F4SEScaleformInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto ScaleformInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	void ScaleformInterface::Register(const char* a_name, REX::NotNull<REX::Observer<RegisterCallback*>> a_callback)
		const
	{
		if (!Impl::GetProxy(*this).doRegister(a_name, a_callback.get())) [[unlikely]] {
			REX::Fail(R"(Failed to register Scaleform interface with name "{}".)"sv, a_name);
		}
	}
}
