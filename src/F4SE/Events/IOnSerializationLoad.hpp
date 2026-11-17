#pragma once

namespace F4SE
{
	class SerializationInterface;
}

namespace F4SE::Events
{
	class IOnSerializationLoad
	{
	public:
		IOnSerializationLoad() noexcept = default;
		virtual ~IOnSerializationLoad() noexcept = default;

		IOnSerializationLoad(const IOnSerializationLoad&) noexcept = default;
		IOnSerializationLoad(IOnSerializationLoad&&) noexcept = default;

		auto operator=(const IOnSerializationLoad&) noexcept -> IOnSerializationLoad& = default;
		auto operator=(IOnSerializationLoad&&) noexcept -> IOnSerializationLoad& = default;

		virtual void OnSerializationLoad(const F4SE::SerializationInterface* a_serializer) = 0;
	};
}
