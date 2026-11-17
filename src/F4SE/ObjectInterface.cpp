#include "F4SE/ObjectInterface.hpp"

#include "F4SE/Core.hpp"
#include "REX/Macros.hpp"

namespace F4SE::Impl
{
	namespace
	{
		class F4SEObjectInterface final
		{
		public:
			F4SEObjectInterface() = delete;
			~F4SEObjectInterface() = delete;

			F4SEObjectInterface(const F4SEObjectInterface&) = delete;
			F4SEObjectInterface(F4SEObjectInterface&&) = delete;

			auto operator=(const F4SEObjectInterface&) -> F4SEObjectInterface& = delete;
			auto operator=(F4SEObjectInterface&&) -> F4SEObjectInterface& = delete;

			F4SE::InterfaceVersion interfaceVersion;
			DelayFunctorManager&(F4SE_API* getDelayFunctorManager)();
			ObjectRegistry&(F4SE_API* getObjectRegistry)();
			PersistentObjectStorage&(F4SE_API* getPersistentObjectStorage)();
		};

		[[nodiscard]] [[REX_ALWAYS_INLINE]]
		auto GetProxy(const ObjectInterface& a_interface) noexcept -> const F4SEObjectInterface&
		{
			return reinterpret_cast<const F4SEObjectInterface&>(a_interface);
		}
	}
}

namespace F4SE
{
	auto ObjectInterface::GetVersion() const noexcept -> F4SE::InterfaceVersion
	{
		return Impl::GetProxy(*this).interfaceVersion;
	}

	auto ObjectInterface::GetDelayFunctorManager() const -> const DelayFunctorManager&
	{
		return Impl::GetProxy(*this).getDelayFunctorManager();
	}

	auto ObjectInterface::GetObjectRegistry() const -> const ObjectRegistry&
	{
		return Impl::GetProxy(*this).getObjectRegistry();
	}

	auto ObjectInterface::GetPersistentObjectStorage() const -> const PersistentObjectStorage&
	{
		return Impl::GetProxy(*this).getPersistentObjectStorage();
	}
}
