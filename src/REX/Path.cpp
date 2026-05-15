#include "REX/Path.hpp"

namespace REX
{
	template std::string_view GetFileName(std::string_view) noexcept;
	template std::wstring_view GetFileName(std::wstring_view) noexcept;
	template std::u8string_view GetFileName(std::u8string_view) noexcept;
	template std::u16string_view GetFileName(std::u16string_view) noexcept;
	template std::u32string_view GetFileName(std::u32string_view) noexcept;

	template std::string_view GetFileNameWithoutExtension(std::string_view) noexcept;
	template std::wstring_view GetFileNameWithoutExtension(std::wstring_view) noexcept;
	template std::u8string_view GetFileNameWithoutExtension(std::u8string_view) noexcept;
	template std::u16string_view GetFileNameWithoutExtension(std::u16string_view) noexcept;
	template std::u32string_view GetFileNameWithoutExtension(std::u32string_view) noexcept;

	template std::string_view GetFileExtension(std::string_view) noexcept;
	template std::wstring_view GetFileExtension(std::wstring_view) noexcept;
	template std::u8string_view GetFileExtension(std::u8string_view) noexcept;
	template std::u16string_view GetFileExtension(std::u16string_view) noexcept;
	template std::u32string_view GetFileExtension(std::u32string_view) noexcept;

	template std::string_view GetDirectoryPath(std::string_view) noexcept;
	template std::wstring_view GetDirectoryPath(std::wstring_view) noexcept;
	template std::u8string_view GetDirectoryPath(std::u8string_view) noexcept;
	template std::u16string_view GetDirectoryPath(std::u16string_view) noexcept;
	template std::u32string_view GetDirectoryPath(std::u32string_view) noexcept;

	template void GeneralizePath(std::span<char>) noexcept;
	template void GeneralizePath(std::span<wchar_t>) noexcept;
	template void GeneralizePath(std::span<char8_t>) noexcept;
	template void GeneralizePath(std::span<char16_t>) noexcept;
	template void GeneralizePath(std::span<char32_t>) noexcept;
}
