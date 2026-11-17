#pragma once

namespace F4SE
{
	class MessagingInterface;
}

namespace F4SE::Events
{
	class IOnMessagingRegister
	{
	public:
		IOnMessagingRegister() noexcept = default;
		virtual ~IOnMessagingRegister() noexcept = default;

		IOnMessagingRegister(const IOnMessagingRegister&) noexcept = default;
		IOnMessagingRegister(IOnMessagingRegister&&) noexcept = default;

		auto operator=(const IOnMessagingRegister&) noexcept -> IOnMessagingRegister& = default;
		auto operator=(IOnMessagingRegister&&) noexcept -> IOnMessagingRegister& = default;

		virtual void OnMessagingRegister(const F4SE::MessagingInterface* a_interface) = 0;
	};
}
