#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ICachedErrorMessage.hpp"

namespace RE::BSScript
{
	class ErrorMessage final : public ICachedErrorMessage
	{
	public:
		explicit ErrorMessage(std::string_view a_message) :
			_message(a_message)
		{
		}

		~ErrorMessage() noexcept override = default;

		ErrorMessage(const ErrorMessage&) = delete;
		ErrorMessage(ErrorMessage&&) = delete;

		auto operator=(const ErrorMessage&) -> ErrorMessage& = delete;
		auto operator=(ErrorMessage&&) -> ErrorMessage& = delete;

		[[nodiscard]]
		auto GetMessage() const noexcept -> std::string_view
		{
			return _message;
		}

		void GetErrorMsg(BSFixedString& a_message) const override
		{
			a_message = BSFixedString(_message);
		}

	private:
		std::string_view _message;
	};
}
