#pragma once

namespace REX::W32
{
	enum UNDNAME : std::uint32_t
	{
		UNDNAME_NO_MS_KEYWORDS = 0x2,
		UNDNAME_NO_FUNCTION_RETURNS = 0x4,
		UNDNAME_NO_ALLOCATION_MODEL = 0x8,
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
	std::uint32_t UnDecorateSymbolName(const char* a_name, char* a_buffer, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept;
	std::uint32_t UnDecorateSymbolNameW(const wchar_t* a_name, wchar_t* a_buffer, std::uint32_t a_bufLen, std::uint32_t a_flags) noexcept;
}
