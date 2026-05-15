#pragma once

#include "REX/Concepts.hpp"
#include "REX/SourceLocation.hpp"

namespace REX
{
#if FMT_VERSION > 0l
	using FormatError = fmt::format_error;

	template <class T, REX::win32_character CharT = char>
	using Formatter = fmt::formatter<T, CharT>;

	template <class T, REX::win32_character CharT = char>
	using RangeFormatter = fmt::range_formatter<T, CharT>;

	using RangeFormat = fmt::range_format;

	template <REX::win32_character CharT, class... Args>
	using BasicFormatString =
		std::conditional_t<std::same_as<CharT, char>, fmt::format_string<Args...>,
			std::conditional_t<std::same_as<CharT, wchar_t>, fmt::wformat_string<Args...>, std::false_type>>;

	template <class... Args>
	using FormatString = fmt::format_string<Args...>;

	template <class... Args>
	using WFormatString = fmt::wformat_string<Args...>;

	template <class Context>
	using BasicFormatArgs = fmt::basic_format_args<Context>;

	using FormatArgs = fmt::format_args;
	using WFormatArgs = fmt::wformat_args;

	template <class OutputIt, REX::win32_character CharT>
	using BasicFormatContext = fmt::basic_format_context<OutputIt, CharT>;

	using FormatContext = fmt::format_context;
	using WFormatContext = fmt::wformat_context;

	template <REX::win32_character CharT>
	using BasicFormatParseContext = fmt::basic_format_parse_context<CharT>;

	using FormatParseContext = fmt::format_parse_context;
	using WFormatParseContext = fmt::wformat_parse_context;

	template <class OutputIt>
	using FormatToNResult = fmt::format_to_n_result<OutputIt>;

	template <class T, class CharT = char>
	concept formattable = REX::win32_character<CharT> && fmt::formattable<T, CharT>;

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateFormatArgs(Args&... a_args) noexcept
	{
		return fmt::make_format_args(a_args...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateWFormatArgs(Args&... a_args) noexcept
	{
		return fmt::make_wformat_args(a_args...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(FormatString<Args...> a_format, Args&&... a_args)
		-> std::string
		requires((formattable<Args, char> && ...))
	{
		return fmt::format(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(WFormatString<Args...> a_format, Args&&... a_args)
		-> std::wstring
		requires((formattable<Args, wchar_t> && ...))
	{
		return fmt::format(a_format, std::forward<Args>(a_args)...);
	}

	[[nodiscard]] __forceinline auto VFormat(std::string_view a_format, FormatArgs a_args)
		-> std::string
	{
		return fmt::vformat(fmt::string_view(a_format), a_args);
	}

	[[nodiscard]] __forceinline auto VFormat(std::wstring_view a_format, WFormatArgs a_args)
		-> std::wstring
	{
		return fmt::vformat(fmt::wstring_view(a_format), a_args);
	}

	[[nodiscard]] __forceinline auto DynamicFormat(std::string_view a_format)
	{
		return fmt::runtime(fmt::string_view(a_format));
	}

	[[nodiscard]] __forceinline auto DynamicFormat(std::wstring_view a_format)
	{
		return fmt::runtime(fmt::wstring_view(a_format));
	}

	template <std::output_iterator<char> OutputIt>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, std::string_view a_format)
		-> OutputIt
	{
		return fmt::format_to(std::move(a_outIt), fmt::string_view(a_format));
	}

	template <std::output_iterator<wchar_t> OutputIt>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, std::wstring_view a_format)
		-> OutputIt
	{
		return fmt::format_to(std::move(a_outIt), fmt::wstring_view(a_format));
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, FormatString<Args...> a_format, Args&&... a_args)
		-> OutputIt
		requires((formattable<Args, char> && ...))
	{
		return fmt::format_to(std::move(a_outIt), a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, WFormatString<Args...> a_format, Args&&... a_args)
		-> OutputIt
		requires((formattable<Args, wchar_t> && ...))
	{
		return fmt::format_to(std::move(a_outIt), a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<char> OutputIt>
	__forceinline auto VFormatTo(OutputIt a_outIt, std::string_view a_format, FormatArgs a_args)
		-> OutputIt
	{
		return fmt::vformat_to(std::move(a_outIt), fmt::string_view(a_format), a_args);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	__forceinline auto VFormatTo(OutputIt a_outIt, std::wstring_view a_format, WFormatArgs a_args)
		-> OutputIt
	{
		return fmt::vformat_to(std::move(a_outIt), fmt::wstring_view(a_format), a_args);
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	__forceinline auto FormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> FormatToNResult<OutputIt>
		requires((formattable<Args, char> && ...))
	{
		return fmt::format_to_n(std::move(a_outIt), a_size, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	auto FormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, WFormatString<Args...> a_format, Args&&... a_args) noexcept // NOLINT(cppcoreguidelines-missing-std-forward)
		-> FormatToNResult<OutputIt>
		requires((formattable<Args, wchar_t> && ...))
	{
		// workaround for `fmt::format_to_n` having a defect in its wide character implementation
		auto buffer = fmt::detail::iterator_buffer<OutputIt, wchar_t>(std::move(a_outIt), a_size);
		fmt::detail::vformat_to(buffer, a_format.get(), fmt::make_wformat_args(a_args...));
		return { buffer.out(), buffer.size() }; // `buffer.count()` is not accessible, for some reason
	}

	template <std::output_iterator<char> OutputIt>
	__forceinline auto VFormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, std::string_view a_format, FormatArgs a_args)
		-> FormatToNResult<OutputIt>
	{
		return fmt::vformat_to_n(std::move(a_outIt), a_size, fmt::string_view(a_format), a_args);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	__forceinline auto VFormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, std::wstring_view a_format, WFormatArgs a_args)
		-> FormatToNResult<OutputIt>
	{
		return fmt::vformat_to_n(std::move(a_outIt), a_size, fmt::wstring_view(a_format), a_args);
	}

	template <class... Args>
	__forceinline auto FormattedSize(FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::size_t
		requires((formattable<Args, char> && ...))
	{
		return fmt::formatted_size(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline auto FormattedSize(WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::size_t
		requires((formattable<Args, wchar_t> && ...))
	{
		return fmt::formatted_size(a_format, std::forward<Args>(a_args)...);
	}

	__forceinline void PrintLine()
	{
		fmt::println(fmt::string_view(""sv));
	}

	__forceinline void PrintLine(std::ostream& a_stream)
	{
		fmt::println(a_stream, fmt::string_view(""sv));
	}

	__forceinline void PrintLine(std::FILE* a_file)
	{
		fmt::println(a_file, fmt::string_view(""sv));
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

	template <REX::win32_character CharT, class... Args>
	class BasicFormatStringLocation final
	{
	public:
		template <class T>
		consteval BasicFormatStringLocation(const T& a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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
		REX::SourceLocation _location;
	};

	template <class... Args>
	using FormatStringLocation = BasicFormatStringLocation<char, std::type_identity_t<Args>...>;

	template <class... Args>
	using WFormatStringLocation = BasicFormatStringLocation<wchar_t, std::type_identity_t<Args>...>;
#else
	static_assert(std::enable_nonlocking_formatter_optimization<char>);
	static_assert(std::enable_nonlocking_formatter_optimization<wchar_t>);

	using FormatError = std::format_error;

	template <class T, REX::win32_character CharT = char>
	using Formatter = std::formatter<T, CharT>;

	template <class T, REX::win32_character CharT = char>
	using RangeFormatter = std::range_formatter<T, CharT>;

	using RangeFormat = std::range_format;

	template <REX::win32_character CharT, class... Args>
	using BasicFormatString = std::basic_format_string<CharT, Args...>;

	template <class... Args>
	using FormatString = std::format_string<Args...>;

	template <class... Args>
	using WFormatString = std::wformat_string<Args...>;

	template <class Context>
	using BasicFormatArgs = std::basic_format_args<Context>;

	using FormatArgs = std::format_args;
	using WFormatArgs = std::wformat_args;

	template <class OutputIt, REX::win32_character CharT>
	using BasicFormatContext = std::basic_format_context<OutputIt, CharT>;

	using FormatContext = std::format_context;
	using WFormatContext = std::wformat_context;

	template <REX::win32_character CharT>
	using BasicFormatParseContext = std::basic_format_parse_context<CharT>;

	using FormatParseContext = std::format_parse_context;
	using WFormatParseContext = std::wformat_parse_context;

	template <class OutputIt>
	using FormatToNResult = std::format_to_n_result<OutputIt>;

	template <class T, class CharT = char>
	concept formattable = REX::win32_character<CharT> && std::formattable<T, CharT>;

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateFormatArgs(Args&... a_args) noexcept
	{
		return std::make_format_args(a_args...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto CreateWFormatArgs(Args&... a_args) noexcept
	{
		return std::make_wformat_args(a_args...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(FormatString<Args...> a_format, Args&&... a_args)
		-> std::string
		requires((formattable<Args, char> && ...))
	{
		return std::format(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[nodiscard]] __forceinline constexpr auto Format(WFormatString<Args...> a_format, Args&&... a_args)
		-> std::wstring
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::format(a_format, std::forward<Args>(a_args)...);
	}

	[[nodiscard]] __forceinline auto VFormat(std::string_view a_format, FormatArgs a_args)
		-> std::string
	{
		return std::vformat(a_format, a_args);
	}

	[[nodiscard]] __forceinline auto VFormat(std::wstring_view a_format, WFormatArgs a_args)
		-> std::wstring
	{
		return std::vformat(a_format, a_args);
	}

#if __cpp_lib_format >= 202603l
	[[nodiscard]] __forceinline auto DynamicFormat(std::string_view a_format)
	{
		return std::dynamic_format(a_format);
	}

	[[nodiscard]] __forceinline auto DynamicFormat(std::wstring_view a_format)
	{
		return std::dynamic_format(a_format);
	}
#endif

	template <std::output_iterator<char> OutputIt>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, std::string_view a_format)
		-> OutputIt
	{
		return std::format_to(std::move(a_outIt), a_format);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, std::wstring_view a_format)
		-> OutputIt
	{
		return std::format_to(std::move(a_outIt), a_format);
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, FormatString<Args...> a_format, Args&&... a_args)
		-> OutputIt
		requires((formattable<Args, char> && ...))
	{
		return std::format_to(std::move(a_outIt), a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	__forceinline constexpr auto FormatTo(OutputIt a_outIt, WFormatString<Args...> a_format, Args&&... a_args)
		-> OutputIt
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::format_to(std::move(a_outIt), a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<char> OutputIt>
	__forceinline auto VFormatTo(OutputIt a_outIt, std::string_view a_format, FormatArgs a_args)
		-> OutputIt
	{
		return std::vformat_to(std::move(a_outIt), a_format, a_args);
	}

	template <std::output_iterator<wchar_t> OutputIt>
	__forceinline auto VFormatTo(OutputIt a_outIt, std::wstring_view a_format, WFormatArgs a_args)
		-> OutputIt
	{
		return std::vformat_to(std::move(a_outIt), a_format, a_args);
	}

	template <std::output_iterator<char> OutputIt, class... Args>
	__forceinline auto FormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> FormatToNResult<OutputIt>
		requires((formattable<Args, char> && ...))
	{
		return std::format_to_n(std::move(a_outIt), a_size, a_format, std::forward<Args>(a_args)...);
	}

	template <std::output_iterator<wchar_t> OutputIt, class... Args>
	__forceinline auto FormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> FormatToNResult<OutputIt>
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::format_to_n(std::move(a_outIt), a_size, a_format, std::forward<Args>(a_args)...);
	}

#if _MSC_VER > 0l
	template <std::output_iterator<char> OutputIt>
	auto VFormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, std::string_view a_format, FormatArgs a_args)
		-> FormatToNResult<OutputIt>
	{
		// this is a custom implementation of fmt's `vformat_to_n`, due to it never being specified in the standard library
		auto buffer = std::_Fmt_iterator_buffer<OutputIt, char, std::_Fmt_fixed_buffer_traits>(std::move(a_outIt), a_size);
		std::vformat_to(std::_Fmt_wit(buffer), a_format, a_args);
		return { .out = buffer._Out(), .size = buffer._Count() };
	}

	template <std::output_iterator<wchar_t> OutputIt>
	auto VFormatToN(OutputIt a_outIt, std::iter_difference_t<OutputIt> a_size, std::wstring_view a_format, WFormatArgs a_args)
		-> FormatToNResult<OutputIt>
	{
		// this is a custom implementation of fmt's `vformat_to_n`, due to it never being specified in the standard library
		auto buffer = std::_Fmt_iterator_buffer<OutputIt, wchar_t, std::_Fmt_fixed_buffer_traits>(std::move(a_outIt), a_size);
		std::vformat_to(std::_Fmt_wit(buffer), a_format, a_args);
		return { .out = buffer._Out(), .size = buffer._Count() };
	}
#endif

	template <class... Args>
	__forceinline auto FormattedSize(FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::size_t
		requires((formattable<Args, char> && ...))
	{
		return std::formatted_size(a_format, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	__forceinline auto FormattedSize(WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::size_t
		requires((formattable<Args, wchar_t> && ...))
	{
		return std::formatted_size(a_format, std::forward<Args>(a_args)...);
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
		std::print(a_stream, a_format, std::forward<Args>(a_args)...);
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

	template <REX::win32_character CharT, class... Args>
	class BasicFormatStringLocation final
	{
	public:
		template <class T>
		consteval BasicFormatStringLocation(const T& a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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
		REX::SourceLocation _location;
	};

	template <class... Args>
	using FormatStringLocation = BasicFormatStringLocation<char, std::type_identity_t<Args>...>;

	template <class... Args>
	using WFormatStringLocation = BasicFormatStringLocation<wchar_t, std::type_identity_t<Args>...>;
#endif

	template <REX::win32_character CharT, std::size_t N>
	class FixedFormatData final
	{
	public:
		std::array<CharT, N> buffer;
		std::size_t size;
	};

	template <std::size_t N = REX::MESSAGE_BUFFER_SIZE, class... Args>
	auto FixedFormat(FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> FixedFormatData<char, N>
		requires((formattable<Args, char> && ...))
	{
		auto formatBuffer = std::array<char, N>();
		auto formatResult = FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(N - 1),
			a_format,
			std::forward<Args>(a_args)...);

		return {
			.buffer = std::move(formatBuffer),
			.size = static_cast<std::size_t>(formatResult.size),
		};
	}

	template <std::size_t N = REX::MESSAGE_BUFFER_SIZE, class... Args>
	auto FixedFormat(WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> FixedFormatData<wchar_t, N>
		requires((formattable<Args, wchar_t> && ...))
	{
		auto formatBuffer = std::array<wchar_t, N>();
		auto formatResult = FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(N - 1),
			a_format,
			std::forward<Args>(a_args)...);

		return {
			.buffer = std::move(formatBuffer),
			.size = static_cast<std::size_t>(formatResult.size),
		};
	}

	template <class... Args>
	auto FixedFormat(std::span<char> a_buffer, FormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::string_view
		requires((formattable<Args, char> && ...))
	{
		const auto formatResult = FormatToN(
			a_buffer.data(),
			static_cast<std::ptrdiff_t>(a_buffer.size() - 1),
			a_format,
			std::forward<Args>(a_args)...);

		return { a_buffer.data(), static_cast<std::size_t>(formatResult.size) };
	}

	template <class... Args>
	auto FixedFormat(std::span<wchar_t> a_buffer, WFormatString<Args...> a_format, Args&&... a_args) noexcept
		-> std::wstring_view
		requires((formattable<Args, wchar_t> && ...))
	{
		const auto formatResult = FormatToN(
			a_buffer.data(),
			static_cast<std::ptrdiff_t>(a_buffer.size() - 1),
			a_format,
			std::forward<Args>(a_args)...);

		return { a_buffer.data(), static_cast<std::size_t>(formatResult.size) };
	}

#if FMT_VERSION > 0l || _MSC_VER > 0l
	template <std::size_t N = REX::MESSAGE_BUFFER_SIZE>
	auto VFixedFormat(std::string_view a_format, FormatArgs a_args)
		-> FixedFormatData<char, N>
	{
		auto formatBuffer = std::array<char, N>();
		auto formatResult = VFormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(N - 1),
			a_format,
			a_args);

		return {
			.buffer = std::move(formatBuffer),
			.size = static_cast<std::size_t>(formatResult.size),
		};
	}

	template <std::size_t N = REX::MESSAGE_BUFFER_SIZE>
	auto VFixedFormat(std::wstring_view a_format, WFormatArgs a_args)
		-> FixedFormatData<wchar_t, N>
	{
		auto formatBuffer = std::array<wchar_t, N>();
		auto formatResult = VFormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(N - 1),
			a_format,
			a_args);

		return {
			.buffer = std::move(formatBuffer),
			.size = static_cast<std::size_t>(formatResult.size),
		};
	}

	inline auto VFixedFormat(std::span<char> a_buffer, std::string_view a_format, FormatArgs a_args)
		-> std::string_view
	{
		const auto formatResult = VFormatToN(
			a_buffer.data(),
			static_cast<std::ptrdiff_t>(a_buffer.size() - 1),
			a_format,
			a_args);

		return { a_buffer.data(), static_cast<std::size_t>(formatResult.size) };
	}

	inline auto VFixedFormat(std::span<wchar_t> a_buffer, std::wstring_view a_format, WFormatArgs a_args)
		-> std::wstring_view
	{
		const auto formatResult = VFormatToN(
			a_buffer.data(),
			static_cast<std::ptrdiff_t>(a_buffer.size() - 1),
			a_format,
			a_args);

		return { a_buffer.data(), static_cast<std::size_t>(formatResult.size) };
	}
#endif
}
