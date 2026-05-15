#include "REX/Version.hpp"

namespace REX
{
	template auto Version::FromString(std::string_view, char) noexcept
		-> std::expected<Version, REX::PosixErrorCode>;
	template auto Version::FromString(std::wstring_view, wchar_t) noexcept
		-> std::expected<Version, REX::PosixErrorCode>;

	template auto Version::ToString(std::span<char>, char) const noexcept
		-> std::string_view;
	template auto Version::ToString(std::span<wchar_t>, wchar_t) const noexcept
		-> std::wstring_view;

	template auto Version::ToString(char) const
		-> std::string;
	template auto Version::ToString(wchar_t) const
		-> std::wstring;

	static_assert(Version::FromString(""sv) == Version(0, 0, 0, 0));
	static_assert(Version().ToString<char>() == "0.0.0.0"sv);

	static_assert(Version::FromString("1"sv) == Version(1, 0, 0, 0));
	static_assert(Version(1).ToString<char>() == "1.0.0.0"sv);

	static_assert(Version::FromString("1.2"sv) == Version(1, 2, 0, 0));
	static_assert(Version(1, 2).ToString<char>() == "1.2.0.0"sv);

	static_assert(Version::FromString("1.2.3"sv) == Version(1, 2, 3, 0));
	static_assert(Version(1, 2, 3).ToString<char>() == "1.2.3.0"sv);

	static_assert(Version(1, 2, 3, 4).ToString<char>() == "1.2.3.4"sv);

	static_assert(Version::FromString("1-2-3-4"sv, '-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<char>('-') == "1-2-3-4"sv);

	static_assert(Version::FromString(""sv) == Version(0, 0, 0, 0));
	static_assert(Version().ToString<wchar_t>() == L"0.0.0.0"sv);

	static_assert(Version::FromString("1"sv) == Version(1, 0, 0, 0));
	static_assert(Version(1).ToString<wchar_t>() == L"1.0.0.0"sv);

	static_assert(Version::FromString("1.2"sv) == Version(1, 2, 0, 0));
	static_assert(Version(1, 2).ToString<wchar_t>() == L"1.2.0.0"sv);

	static_assert(Version::FromString("1.2.3"sv) == Version(1, 2, 3, 0));
	static_assert(Version(1, 2, 3).ToString<wchar_t>() == L"1.2.3.0"sv);

	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>() == L"1.2.3.4"sv);

	static_assert(Version::FromString("1-2-3-4"sv, '-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>('-') == L"1-2-3-4"sv);

	static_assert(Version::FromString(L"1-2-3-4"sv, L'-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>(L'-') == L"1-2-3-4"sv);

	static_assert(Version::Unpack(0x01020034ui32) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint32_t>() == 0x01020034ui32);

	static_assert(Version::Unpack(0x0001000200030004ui64) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint64_t>() == 0x0001000200030004ui64);
}
