#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"
#include "REX/Version.hpp"
#include "REX/ZString.hpp"

namespace REX
{
	[[nodiscard]] bool IsModuleLoaded(REX::zstring_view a_moduleName) noexcept;
	[[nodiscard]] bool IsModuleLoaded(REX::zwstring_view a_moduleName) noexcept;

	template <REX::win32_character CharT>
	[[nodiscard]] auto GetCurrentModuleFileName(std::span<CharT> a_buffer) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>;

	template <>
	[[nodiscard]] auto GetCurrentModuleFileName(std::span<char> a_buffer) noexcept
		-> std::expected<std::string_view, REX::SystemError>;

	template <>
	[[nodiscard]] auto GetCurrentModuleFileName(std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>;

	template <REX::win32_character CharT>
	[[nodiscard]] auto GetCurrentModuleFileName() noexcept
		-> std::expected<std::basic_string<CharT>, REX::SystemError>;

	template <>
	[[nodiscard]] auto GetCurrentModuleFileName() noexcept
		-> std::expected<std::string, REX::SystemError>;

	template <>
	[[nodiscard]] auto GetCurrentModuleFileName() noexcept
		-> std::expected<std::wstring, REX::SystemError>;

	[[nodiscard]] auto GetModuleFileVersion(REX::zstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;
	[[nodiscard]] auto GetModuleFileVersion(REX::zwstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;

	[[nodiscard]] auto GetModuleProductVersion(REX::zstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;
	[[nodiscard]] auto GetModuleProductVersion(REX::zwstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;
}
