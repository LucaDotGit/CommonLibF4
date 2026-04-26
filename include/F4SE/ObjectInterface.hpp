#pragma once

#include "F4SE/QueryInterface.hpp"

namespace F4SE
{
	class DelayFunctorManager;
	class ObjectRegistry;
	class PersistentObjectStorage;

	class ObjectInterface final
	{
	public:
		inline static constexpr auto INTERFACE_ID{ QueryInterface::InterfaceID::kObject };
		inline static constexpr auto INTERFACE_VERSION{ 1ui32 };

		ObjectInterface() = delete;
		~ObjectInterface() = delete;

		ObjectInterface(const ObjectInterface&) = delete;
		ObjectInterface(ObjectInterface&&) = delete;

		ObjectInterface& operator=(const ObjectInterface&) = delete;
		ObjectInterface& operator=(ObjectInterface&&) = delete;

		[[nodiscard]] std::uint32_t GetVersion() const noexcept;

		[[nodiscard]] const DelayFunctorManager& GetDelayFunctorManager() const;
		[[nodiscard]] const ObjectRegistry& GetObjectRegistry() const;
		[[nodiscard]] const PersistentObjectStorage& GetPersistentObjectStorage() const;
	};
	static_assert(std::is_empty_v<ObjectInterface>);
}
