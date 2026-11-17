#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	inline constexpr auto HKEY_CLASSES_ROOT = static_cast<HKEY>(0x8000'0000);
	inline constexpr auto HKEY_CURRENT_USER = static_cast<HKEY>(0x8000'0001);
	inline constexpr auto HKEY_LOCAL_MACHINE = static_cast<HKEY>(0x8000'0002);
}

namespace REX::W32
{
	auto RegGetValueA(
		HKEY a_key,
		const char* a_subKey,
		const char* a_value,
		std::uint32_t a_flags,
		std::uint32_t* a_type,
		void* a_data,
		std::uint32_t* a_dataLength) noexcept -> std::int32_t;
	auto RegGetValueW(
		HKEY a_key,
		const wchar_t* a_subKey,
		const wchar_t* a_value,
		std::uint32_t a_flags,
		std::uint32_t* a_type,
		void* a_data,
		std::uint32_t* a_dataLength) noexcept -> std::int32_t;
}
