#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	enum UNDNAME : std::uint32_t
	{
		UNDNAME_NO_MS_KEYWORDS = 0x02,
		UNDNAME_NO_FUNCTION_RETURNS = 0x04,
		UNDNAME_NO_ALLOCATION_MODEL = 0x08,
		UNDNAME_NO_ALLOCATION_LANGUAGE = 0x10,
		UNDNAME_NO_THISTYPE = 0x60,
		UNDNAME_NO_ACCESS_SPECIFIERS = 0x80,
		UNDNAME_NO_THROW_SIGNATURES = 0x100,
		UNDNAME_NO_RETURN_UDT_MODEL = 0x400,
		UNDNAME_NAME_ONLY = 0x1000,
		UNDNAME_NO_ARGUMENTS = 0x2000
	};
}

namespace REX::W32
{
	auto UnDecorateSymbolName(const char* a_name, char* a_buffer, std::uint32_t a_bufferLength, std::uint32_t a_flags)
		noexcept -> std::uint32_t;
	auto UnDecorateSymbolNameW(
		const wchar_t* a_name,
		wchar_t* a_buffer,
		std::uint32_t a_bufferLength,
		std::uint32_t a_flags) noexcept -> std::uint32_t;
}
