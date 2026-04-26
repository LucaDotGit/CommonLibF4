#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	template <class CharT>
		requires(character<std::remove_const_t<CharT>>)
	using basic_zstring = CharT*;

	using zstring = basic_zstring<const char>;
	using zwstring = basic_zstring<const wchar_t>;
	using zu8string = basic_zstring<const char8_t>;
	using zu16string = basic_zstring<const char16_t>;
	using zu32string = basic_zstring<const char32_t>;

	template <class CharT>
		requires(character<CharT>)
	using basic_mutable_zstring = CharT*;

	using mutable_zstring = basic_mutable_zstring<char>;
	using mutable_zwstring = basic_mutable_zstring<wchar_t>;
	using mutable_zu8string = basic_mutable_zstring<char8_t>;
	using mutable_zu16string = basic_mutable_zstring<char16_t>;
	using mutable_zu32string = basic_mutable_zstring<char32_t>;

	template <class CharT>
		requires(character<CharT>)
	using basic_zstring_view = std::basic_string_view<CharT>;

	using zstring_view = basic_zstring_view<char>;
	using zwstring_view = basic_zstring_view<wchar_t>;
	using zu8string_view = basic_zstring_view<char8_t>;
	using zu16string_view = basic_zstring_view<char16_t>;
	using zu32string_view = basic_zstring_view<char32_t>;
}
