#pragma once

namespace REX
{
#if FMT_VERSION > 0l
	using FormatError = fmt::format_error;

	template <class T, class CharT = char>
	using Formatter = fmt::formatter<T, CharT>;

	template <class CharT, class... Args>
	using BasicFormatString =
		std::conditional_t<std::same_as<CharT, char>, fmt::format_string<Args...>,
			std::conditional_t<std::same_as<CharT, wchar_t>, fmt::wformat_string<Args...>, void>>;

	template <class... Args>
	using FormatString = fmt::format_string<Args...>;

	template <class... Args>
	using WFormatString = fmt::wformat_string<Args...>;

	using FormatArgs = fmt::format_args;
	using WFormatArgs = fmt::wformat_args;

	template <class OutputIt, class CharT>
	using BasicFormatContext = fmt::basic_format_context<OutputIt, CharT>;

	using FormatContext = fmt::format_context;
	using WFormatContext = fmt::wformat_context;

	template <class CharT>
	using BasicFormatParseContext = fmt::basic_format_parse_context<CharT>;

	using FormatParseContext = fmt::format_parse_context;
	using WFormatParseContext = fmt::wformat_parse_context;

	template <class T, class CharT = char>
	concept formattable = fmt::formattable<T, CharT>;

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateFormatArgs(Args&&... a_args)
	{
		return fmt::make_format_args(std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateWFormatArgs(Args&&... a_args)
	{
		return fmt::make_wformat_args(std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		return fmt::format(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(WFormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, wchar_t> && ...))
	{
		return fmt::format(a_format, std::forward<Args>(a_args)...);
	}

	[[nodiscard]] __forceinline inline auto VFormat(std::string_view a_format, FormatArgs a_args)
	{
		return fmt::vformat(static_cast<fmt::string_view>(a_format), a_args);
	}

	[[nodiscard]] __forceinline inline auto VFormat(std::wstring_view a_format, WFormatArgs a_args)
	{
		return fmt::vformat(static_cast<fmt::wstring_view>(a_format), a_args);
	}

	[[nodiscard]] __forceinline inline auto RuntimeFormat(std::string_view a_format)
	{
		return fmt::runtime(a_format);
	}

	[[nodiscard]] __forceinline inline auto RuntimeFormat(std::wstring_view a_format)
	{
		return fmt::runtime(a_format);
	}

	template <std::output_iterator<char> OutputIt>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, std::string_view a_format)
	{
		return fmt::format_to(a_out, a_format);
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		return fmt::format_to(a_out, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, std::wstring_view a_format)
	{
		return fmt::format_to(a_out, a_format);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, WFormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, wchar_t> && ...))
	{
		return fmt::format_to(a_out, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<char> OutputIt>
	[[nodiscard]] __forceinline auto VFormatTo(OutputIt a_out, std::string_view a_format, FormatArgs a_args)
	{
		return fmt::vformat_to(a_out, a_format, a_args);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	[[nodiscard]] __forceinline auto VFormatTo(OutputIt a_out, std::wstring_view a_format, WFormatArgs a_args)
	{
		return fmt::vformat_to(a_out, a_format, a_args);
	}

	__forceinline void PrintLine()
	{
		fmt::println(""sv);
	}

	__forceinline void PrintLine(std::ostream& a_stream)
	{
		fmt::println(a_stream, ""sv);
	}

	__forceinline void PrintLine(std::FILE* a_file)
	{
		fmt::println(a_file, ""sv);
	}

	template <class... Args>
	__forceinline void Print(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::print(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::println(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void Print(std::ostream& a_stream, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::print(a_stream, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(std::ostream& a_stream, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::println(a_stream, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void Print(std::FILE* a_file, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::print(a_file, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(std::FILE* a_file, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::println(a_file, a_format, std::forward<Args>(a_args)...);
	}

	template <class CharT, class... Args>
	class BasicFormatStringLocation final
	{
	public:
		template <class T>
		consteval BasicFormatStringLocation(const T& a_format, std::source_location a_location = std::source_location::current()) noexcept
			requires(std::is_constructible_v<BasicFormatString<CharT, Args...>, const T&>)
			: _format(a_format),
			  _location(a_location)
		{
		}

		constexpr ~BasicFormatStringLocation() noexcept = default;

		constexpr BasicFormatStringLocation(const BasicFormatStringLocation&) noexcept = default;
		constexpr BasicFormatStringLocation(BasicFormatStringLocation&&) noexcept = default;

		constexpr BasicFormatStringLocation& operator=(const BasicFormatStringLocation&) noexcept = default;
		constexpr BasicFormatStringLocation& operator=(BasicFormatStringLocation&&) noexcept = default;

		[[nodiscard]] constexpr const auto& format() const noexcept { return _format; }
		[[nodiscard]] constexpr const auto& location() const noexcept { return _location; }

	private:
		BasicFormatString<CharT, Args...> _format;
		std::source_location _location;
	};

	template <class... Args>
	using FormatStringLocation = BasicFormatStringLocation<char, std::type_identity_t<Args>...>;

	template <class... Args>
	using WFormatStringLocation = BasicFormatStringLocation<wchar_t, std::type_identity_t<Args>...>;
#else
	using FormatError = std::format_error;

	template <class T, class CharT = char>
	using Formatter = std::formatter<T, CharT>;

	template <class CharT, class... Args>
	using BasicFormatString = std::basic_format_string<CharT, Args...>;

	template <class... Args>
	using FormatString = std::format_string<Args...>;

	template <class... Args>
	using WFormatString = std::wformat_string<Args...>;

	using FormatArgs = std::format_args;
	using WFormatArgs = std::wformat_args;

	template <class OutputIt, class CharT>
	using BasicFormatContext = std::basic_format_context<OutputIt, CharT>;

	using FormatContext = std::format_context;
	using WFormatContext = std::wformat_context;

	template <class CharT>
	using BasicFormatParseContext = std::basic_format_parse_context<CharT>;

	using FormatParseContext = std::format_parse_context;
	using WFormatParseContext = std::wformat_parse_context;

	template <class T, class CharT = char>
	concept formattable = std::formattable<T, CharT>;

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateFormatArgs(Args&&... a_args)
	{
		return std::make_format_args(std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateWFormatArgs(Args&&... a_args)
	{
		return std::make_wformat_args(std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		return std::format(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(WFormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::format(a_format, std::forward<Args>(a_args)...);
	}

	[[nodiscard]] __forceinline inline auto VFormat(std::string_view a_format, FormatArgs a_args)
	{
		return std::vformat(a_format, a_args);
	}

	[[nodiscard]] __forceinline inline auto VFormat(std::wstring_view a_format, WFormatArgs a_args)
	{
		return std::vformat(a_format, a_args);
	}

#if __cpp_lib_format >= 202311l
	[[nodiscard]] __forceinline inline auto RuntimeFormat(std::string_view a_format)
	{
		return std::runtime_format(a_format);
	}

	[[nodiscard]] __forceinline inline auto RuntimeFormat(std::wstring_view a_format)
	{
		return std::runtime_format(a_format);
	}
#endif

	template <std::output_iterator<char> OutputIt>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, std::string_view a_format)
	{
		return std::format_to(a_out, a_format);
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		return std::format_to(a_out, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, std::wstring_view a_format)
	{
		return std::format_to(a_out, a_format);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	[[nodiscard]] __forceinline constexpr auto FormatTo(OutputIt a_out, WFormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::format_to(a_out, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<char> OutputIt>
	[[nodiscard]] __forceinline auto VFormatTo(OutputIt a_out, std::string_view a_format, FormatArgs a_args)
	{
		return std::vformat_to(a_out, a_format, a_args);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	[[nodiscard]] __forceinline auto VFormatTo(OutputIt a_out, std::wstring_view a_format, WFormatArgs a_args)
	{
		return std::vformat_to(a_out, a_format, a_args);
	}

	__forceinline void PrintLine()
	{
		std::println();
	}

	__forceinline void PrintLine(std::ostream& a_stream)
	{
		std::println(a_stream);
	}

	__forceinline void PrintLine(std::FILE* a_file)
	{
		std::println(a_file);
	}

	template <class... Args>
	__forceinline void Print(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		std::print(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		std::println(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void Print(std::ostream& a_stream, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		fmt::print(a_stream, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(std::ostream& a_stream, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		std::println(a_stream, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void Print(std::FILE* a_file, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		std::print(a_file, a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline void PrintLine(std::FILE* a_file, FormatString<Args...> a_format, Args&&... a_args)
		requires((formattable<Args, char> && ...))
	{
		std::println(a_file, a_format, std::forward<Args>(a_args)...);
	}

	template <class CharT, class... Args>
	class BasicFormatStringLocation final
	{
	public:
		template <class T>
		consteval BasicFormatStringLocation(const T& a_format, std::source_location a_location = std::source_location::current()) noexcept
			requires(std::is_constructible_v<BasicFormatString<CharT, Args...>, const T&>)
			: _format(a_format),
			  _location(a_location)
		{
		}

		constexpr ~BasicFormatStringLocation() noexcept = default;

		constexpr BasicFormatStringLocation(const BasicFormatStringLocation&) noexcept = default;
		constexpr BasicFormatStringLocation(BasicFormatStringLocation&&) noexcept = default;

		constexpr BasicFormatStringLocation& operator=(const BasicFormatStringLocation&) noexcept = default;
		constexpr BasicFormatStringLocation& operator=(BasicFormatStringLocation&&) noexcept = default;

		[[nodiscard]] constexpr const auto& format() const noexcept { return _format; }
		[[nodiscard]] constexpr const auto& location() const noexcept { return _location; }

	private:
		BasicFormatString<CharT, Args...> _format;
		std::source_location _location;
	};

	template <class... Args>
	using FormatStringLocation = BasicFormatStringLocation<char, std::type_identity_t<Args>...>;

	template <class... Args>
	using WFormatStringLocation = BasicFormatStringLocation<wchar_t, std::type_identity_t<Args>...>;
#endif

	template <class... Args>
	[[nodiscard]] constexpr auto SafeFormat(FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::expected<std::string, std::exception>
		requires((formattable<Args, char> && ...))
	{
		try {
			return Format(a_format, std::forward<Args>(a_args)...);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	template <class... Args>
	[[nodiscard]] constexpr auto SafeFormat(WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::expected<std::wstring, std::exception>
		requires((formattable<Args, wchar_t> && ...))
	{
		try {
			return Format(a_format, std::forward<Args>(a_args)...);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	[[nodiscard]] inline auto SafeVFormat(std::string_view a_format, FormatArgs a_args) noexcept
		-> std::expected<std::string, std::exception>
	{
		try {
			return VFormat(a_format, a_args);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	[[nodiscard]] inline auto SafeVFormat(std::wstring_view a_format, WFormatArgs a_args) noexcept
		-> std::expected<std::wstring, std::exception>
	{
		try {
			return VFormat(a_format, a_args);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	template <class... Args>
	[[nodiscard]] constexpr auto SafeFormatTo(std::back_insert_iterator<std::string> a_out, FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::expected<std::back_insert_iterator<std::string>, std::exception>
		requires((formattable<Args, char> && ...))
	{
		try {
			return FormatTo(a_out, a_format, std::forward<Args>(a_args)...);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	template <class... Args>
	[[nodiscard]] constexpr auto SafeFormatTo(std::back_insert_iterator<std::wstring> a_out, WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::expected<std::back_insert_iterator<std::wstring>, std::exception>
		requires((formattable<Args, wchar_t> && ...))
	{
		try {
			return FormatTo(a_out, a_format, std::forward<Args>(a_args)...);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	[[nodiscard]] inline auto SafeVFormatTo(std::back_insert_iterator<std::string> a_out, std::string_view a_format, FormatArgs a_args) noexcept
		-> std::expected<std::back_insert_iterator<std::string>, std::exception>
	{
		try {
			return VFormatTo(a_out, a_format, a_args);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}

	[[nodiscard]] inline auto SafeVFormatTo(std::back_insert_iterator<std::wstring> a_out, std::wstring_view a_format, WFormatArgs a_args) noexcept
		-> std::expected<std::back_insert_iterator<std::wstring>, std::exception>
	{
		try {
			return VFormatTo(a_out, a_format, a_args);
		}
		catch (std::exception& error) {
			return std::unexpected(std::move(error));
		}
	}
}
