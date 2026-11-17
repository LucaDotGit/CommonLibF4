#pragma once

namespace F4SE
{
	class SerializationInterface;
}

namespace F4SE::Events
{
	class IOnSerializationSave
	{
	public:
		IOnSerializationSave() noexcept = default;
		virtual ~IOnSerializationSave() noexcept = default;

		IOnSerializationSave(const IOnSerializationSave&) noexcept = default;
		IOnSerializationSave(IOnSerializationSave&&) noexcept = default;

		auto operator=(const IOnSerializationSave&) noexcept -> IOnSerializationSave& = default;
		auto operator=(IOnSerializationSave&&) noexcept -> IOnSerializationSave& = default;

		virtual void OnSerializationSave(const F4SE::SerializationInterface* a_serializer) = 0;
	};
}
