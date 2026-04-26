#include "RE/B/BSStringT.hpp"

namespace RE
{
	template class BSStringT<char, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;
	static_assert(sizeof(BSStringT<char, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>) == 0x10);

	template class BSStringT<wchar_t, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;
	static_assert(sizeof(BSStringT<wchar_t, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>) == 0x10);

	static_assert(sizeof(BSStaticStringT<10>) == 0x20);

	template void swap(BSString&, BSString&) noexcept;
	template void swap(BSStringW&, BSStringW&) noexcept;
}

namespace std
{
	template struct hash<RE::BSString>;
	template struct hash<RE::BSStringW>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template struct formatter<RE::BSString, RE::BSString::value_type>;
	template struct formatter<RE::BSStringW, RE::BSStringW::value_type>;
}
#endif

/*
#if FMT_VERSION > 0L
namespace fmt
{
	template struct formatter<RE::BSString, RE::BSString::value_type>;
	template struct formatter<RE::BSStringW, RE::BSStringW::value_type>;
}
#endif
*/
