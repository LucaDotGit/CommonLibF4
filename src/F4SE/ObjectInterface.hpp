#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class DelayFunctorManager;
	class ObjectRegistry;
	class PersistentObjectStorage;

	class ObjectInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID = QueryInterface::InterfaceID::Object;
		inline static constexpr auto INTERFACE_VERSION = static_cast<std::uint32_t>(1);

		ObjectInterface() = delete;
		~ObjectInterface() = delete;

		ObjectInterface(const ObjectInterface&) = delete;
		ObjectInterface(ObjectInterface&&) = delete;

		auto operator=(const ObjectInterface&) -> ObjectInterface& = delete;
		auto operator=(ObjectInterface&&) -> ObjectInterface& = delete;

		[[nodiscard]]
		auto GetVersion() const noexcept -> F4SE::InterfaceVersion;

		[[nodiscard]]
		auto GetDelayFunctorManager() const -> const DelayFunctorManager&;
		[[nodiscard]]
		auto GetObjectRegistry() const -> const ObjectRegistry&;
		[[nodiscard]]
		auto GetPersistentObjectStorage() const -> const PersistentObjectStorage&;
	};

	static_assert(std::is_empty_v<ObjectInterface>);
}
