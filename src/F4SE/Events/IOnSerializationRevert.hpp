#pragma once

namespace F4SE
{
	class SerializationInterface;
}

namespace F4SE::Events
{
	class IOnSerializationRevert
	{
	public:
		IOnSerializationRevert() noexcept = default;
		virtual ~IOnSerializationRevert() noexcept = default;

		IOnSerializationRevert(const IOnSerializationRevert&) noexcept = default;
		IOnSerializationRevert(IOnSerializationRevert&&) noexcept = default;

		auto operator=(const IOnSerializationRevert&) noexcept -> IOnSerializationRevert& = default;
		auto operator=(IOnSerializationRevert&&) noexcept -> IOnSerializationRevert& = default;

		virtual void OnSerializationRevert(const F4SE::SerializationInterface* a_serializer) = 0;
	};
}
