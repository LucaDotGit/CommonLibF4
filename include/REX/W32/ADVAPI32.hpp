#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	inline constexpr auto HKEY_CLASSES_ROOT{ static_cast<HKEY>(0x80000000ui64) };
	inline constexpr auto HKEY_CURRENT_USER{ static_cast<HKEY>(0x80000001ui64) };
	inline constexpr auto HKEY_LOCAL_MACHINE{ static_cast<HKEY>(0x80000002ui64) };
}

namespace REX::W32
{
	std::int32_t RegGetValueA(HKEY a_key, const char* a_subKey, const char* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen) noexcept;
	std::int32_t RegGetValueW(HKEY a_key, const wchar_t* a_subKey, const wchar_t* a_value, std::uint32_t a_flags, std::uint32_t* a_type, void* a_data, std::uint32_t* a_dataLen) noexcept;
}
