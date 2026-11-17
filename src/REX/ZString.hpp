#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	template <class CharT>
		requires(REX::character<std::remove_const_t<CharT>>)
	using BasicZString = CharT*;

	using ZString = BasicZString<const char>;
	using ZWString = BasicZString<const wchar_t>;
	using ZU8String = BasicZString<const char8_t>;
	using ZU16String = BasicZString<const char16_t>;
	using ZU32String = BasicZString<const char32_t>;

	template <class CharT>
		requires(REX::character<CharT>)
	using BasicMutableZString = CharT*;

	using MutableZString = BasicMutableZString<char>;
	using MutableZWString = BasicMutableZString<wchar_t>;
	using MutableZU8String = BasicMutableZString<char8_t>;
	using MutableZU16String = BasicMutableZString<char16_t>;
	using MutableZU32String = BasicMutableZString<char32_t>;

	template <class CharT>
		requires(REX::character<CharT>)
	using BasicZStringView = std::basic_string_view<CharT>;

	using ZStringView = BasicZStringView<char>;
	using ZWStringView = BasicZStringView<wchar_t>;
	using ZU8StringView = BasicZStringView<char8_t>;
	using ZU16StringView = BasicZStringView<char16_t>;
	using ZU32StringView = BasicZStringView<char32_t>;
}
