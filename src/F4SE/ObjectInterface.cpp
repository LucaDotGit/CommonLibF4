#include "F4SE/ObjectInterface.hpp"

#include "F4SE/Core.hpp"

namespace F4SE::Impl
{
	struct F4SEObjectInterface final
	{
		std::uint32_t interfaceVersion;
		DelayFunctorManager&(F4SE_API* GetDelayFunctorManager)();
		ObjectRegistry&(F4SE_API* GetObjectRegistry)();
		PersistentObjectStorage&(F4SE_API* GetPersistentObjectStorage)();
	};

	[[nodiscard]] __forceinline static const F4SEObjectInterface& GetProxy(const ObjectInterface* a_interface) noexcept
	{
		return reinterpret_cast<const F4SEObjectInterface&>(*a_interface);
	}
}

namespace F4SE
{
	std::uint32_t ObjectInterface::GetVersion() const noexcept
	{
		return Impl::GetProxy(this).interfaceVersion;
	}

	const DelayFunctorManager& ObjectInterface::GetDelayFunctorManager() const
	{
		return Impl::GetProxy(this).GetDelayFunctorManager();
	}

	const ObjectRegistry& ObjectInterface::GetObjectRegistry() const
	{
		return Impl::GetProxy(this).GetObjectRegistry();
	}

	const PersistentObjectStorage& ObjectInterface::GetPersistentObjectStorage() const
	{
		return Impl::GetProxy(this).GetPersistentObjectStorage();
	}
}
