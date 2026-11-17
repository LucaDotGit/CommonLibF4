#include "REX/Version.hpp"

#include "REX/Formatting.hpp"

namespace REX
{
	template <>
	auto Version::ToString(std::span<char> a_buffer, char a_separator) const noexcept -> std::basic_string_view<char>
	{
		const auto formatResult = REX::FormatToN(
			a_buffer.begin(),
			static_cast<std::ptrdiff_t>(a_buffer.size()),
			"{}{}{}{}{}{}{}"sv,
			GetMajor(),
			a_separator,
			GetMinor(),
			a_separator,
			GetPatch(),
			a_separator,
			GetBuild());

		return std::basic_string_view<char>{a_buffer.data(), static_cast<std::size_t>(formatResult.size)};
	}

	template <>
	auto Version::ToString(std::span<wchar_t> a_buffer, wchar_t a_separator) const noexcept
		-> std::basic_string_view<wchar_t>
	{
		const auto formatResult = REX::FormatToN(
			a_buffer.begin(),
			static_cast<std::ptrdiff_t>(a_buffer.size()),
			L"{}{}{}{}{}{}{}"sv,
			GetMajor(),
			a_separator,
			GetMinor(),
			a_separator,
			GetPatch(),
			a_separator,
			GetBuild());

		return std::basic_string_view<wchar_t>{a_buffer.data(), static_cast<std::size_t>(formatResult.size)};
	}
}
