#pragma once

namespace F4SE
{
	class SerializationInterface;
}

namespace F4SE::Events
{
	class IOnSerializationRegister
	{
	public:
		IOnSerializationRegister() noexcept = default;
		virtual ~IOnSerializationRegister() noexcept = default;

		IOnSerializationRegister(const IOnSerializationRegister&) noexcept = default;
		IOnSerializationRegister(IOnSerializationRegister&&) noexcept = default;

		auto operator=(const IOnSerializationRegister&) noexcept -> IOnSerializationRegister& = default;
		auto operator=(IOnSerializationRegister&&) noexcept -> IOnSerializationRegister& = default;

		virtual void OnSerializationRegister(const F4SE::SerializationInterface* a_serializer) = 0;
	};
}
