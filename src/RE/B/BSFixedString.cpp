#include "RE/B/BSFixedString.hpp"

namespace RE::Impl
{
	template class BSFixedString<char, false>;
	static_assert(sizeof(BSFixedString<char, false>) == 0x08);

	template class BSFixedString<char, true>;
	static_assert(sizeof(BSFixedString<char, true>) == 0x08);

	template class BSFixedString<wchar_t, false>;
	static_assert(sizeof(BSFixedString<wchar_t, false>) == 0x08);

	template class BSFixedString<wchar_t, true>;
	static_assert(sizeof(BSFixedString<wchar_t, true>) == 0x08);
}

namespace RE
{
	template void swap(RE::BSFixedString&, RE::BSFixedString&) noexcept;
	template void swap(RE::BSFixedStringCS&, RE::BSFixedStringCS&) noexcept;
	template void swap(RE::BSFixedStringW&, RE::BSFixedStringW&) noexcept;
	template void swap(RE::BSFixedStringWCS&, RE::BSFixedStringWCS&) noexcept;

	template struct BSCRC32<RE::BSFixedString>;
	template struct BSCRC32<RE::BSFixedStringCS>;
	template struct BSCRC32<RE::BSFixedStringW>;
	template struct BSCRC32<RE::BSFixedStringWCS>;
}

namespace std
{
	template struct hash<RE::BSFixedString>;
	template struct hash<RE::BSFixedStringCS>;
	template struct hash<RE::BSFixedStringW>;
	template struct hash<RE::BSFixedStringWCS>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<RE::BSFixedString, RE::BSFixedString::value_type>;
	template struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type>;
	template struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type>;
	template struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type>;
}
#endif

/*
#if FMT_VERSION > 0L
namespace fmt
{
	template struct formatter<RE::BSFixedString, RE::BSFixedString::value_type>;
	template struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type>;
	template struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type>;
	template struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type>;
}
#endif
*/
