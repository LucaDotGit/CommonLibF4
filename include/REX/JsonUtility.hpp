#pragma once

#if COMMONLIB_OPTION_JSON == 1

namespace REX::Json
{
	inline constexpr auto KEY_SEPARATOR = '/';

	inline constexpr auto ALLOW_EXCEPTIONS = true;
	inline constexpr auto IGNORE_COMMENTS = true;
	inline constexpr auto ENSURE_ASCII = false;

	template <class T>
	[[nodiscard]] const T::parser_callback_t& GetParserCallback() noexcept
	{
		static const auto INSTANCE = typename T::parser_callback_t();
		return INSTANCE;
	}

	template <class T>
	inline constexpr auto ERROR_HANDLER = T::error_handler_t::replace;

	inline constexpr auto INDENT_COUNT = 1;
	inline constexpr auto INDENT_CHAR = '\t';
}

#endif
