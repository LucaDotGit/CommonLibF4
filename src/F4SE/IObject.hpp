#pragma once

#include "REX/Ownership.hpp"

namespace F4SE
{
	class IDelayFunctor;
	class SerializationInterface;

	class IObject
	{
	public:
		IObject() noexcept = default;

		IObject(const IObject&) = delete;
		IObject(IObject&&) = delete;

		auto operator=(const IObject&) -> IObject& = delete;
		auto operator=(IObject&&) -> IObject& = delete;

		virtual ~IObject() noexcept = default; // 0x00

		// add
		[[nodiscard]]
		virtual auto GetName() const noexcept -> const char* = 0; // 0x01
		[[nodiscard]]
		virtual auto GetVersion() const noexcept -> std::uint32_t = 0; // 0x02

		[[nodiscard]]
		virtual auto GetAsDelayFunctor() noexcept -> REX::Observer<IDelayFunctor*> // 0x03
		{
			return nullptr;
		}

		virtual auto Save(const SerializationInterface* a_serializer) -> bool = 0;							// 0x04
		virtual auto Load(const SerializationInterface* a_serializer, std::uint32_t a_version) -> bool = 0; // 0x05
	};

	static_assert(sizeof(IObject) == 0x08);
}
