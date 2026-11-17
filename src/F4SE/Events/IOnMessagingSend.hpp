#pragma once

#include "F4SE/MessagingInterface.hpp"

namespace F4SE::Events
{
	class IOnMessagingSend
	{
	public:
		IOnMessagingSend() noexcept = default;
		virtual ~IOnMessagingSend() noexcept = default;

		IOnMessagingSend(const IOnMessagingSend&) noexcept = default;
		IOnMessagingSend(IOnMessagingSend&&) noexcept = default;

		auto operator=(const IOnMessagingSend&) noexcept -> IOnMessagingSend& = default;
		auto operator=(IOnMessagingSend&&) noexcept -> IOnMessagingSend& = default;

		virtual void OnMessagingSend(const F4SE::MessagingInterface::Message& a_message) = 0;
	};
}
