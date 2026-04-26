#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ICachedErrorMessage.hpp"

namespace RE::BSScript::Impl
{
	class CachedErrorMessage final
		: public ICachedErrorMessage
	{
	public:
		explicit CachedErrorMessage(REX::zstring_view a_message)
			: _message(a_message)
		{
		}

		~CachedErrorMessage() override = default;

		CachedErrorMessage(const CachedErrorMessage&) = delete;
		CachedErrorMessage(CachedErrorMessage&&) = delete;

		CachedErrorMessage& operator=(const CachedErrorMessage&) = delete;
		CachedErrorMessage& operator=(CachedErrorMessage&&) = delete;

		[[nodiscard]] BSFixedString GetMessage() const noexcept { return _message; }

		void GetErrorMsg(BSFixedString& a_message) const override
		{
			a_message = _message;
		}

	private:
		BSFixedString _message;
	};
}
