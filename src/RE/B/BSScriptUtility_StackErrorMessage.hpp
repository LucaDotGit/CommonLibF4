#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ICachedErrorMessage.hpp"

namespace RE::BSScript
{
	class StackErrorMessage final : public ICachedErrorMessage
	{
	public:
		StackErrorMessage(std::string_view a_message, StackID a_stackID) noexcept :
			_message(a_message),
			_stackID(a_stackID)
		{
		}

		~StackErrorMessage() noexcept override = default;

		StackErrorMessage(const StackErrorMessage&) = delete;
		StackErrorMessage(StackErrorMessage&&) = delete;

		auto operator=(const StackErrorMessage&) -> StackErrorMessage& = delete;
		auto operator=(StackErrorMessage&&) -> StackErrorMessage& = delete;

		[[nodiscard]]
		auto GetMessage() const noexcept -> std::string_view
		{
			return _message;
		}

		[[nodiscard]]
		auto GetStackID() const noexcept -> StackID
		{
			return _stackID;
		}

		void GetErrorMsg(BSFixedString& a_message) const override
		{
			a_message = BSFixedString(_message);
		}

	private:
		std::string_view _message;
		StackID _stackID;
	};
}
