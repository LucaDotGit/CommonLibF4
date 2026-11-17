#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"
#include "REX/Version.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/ZString.hpp"

namespace REX::W32
{
	// NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
	enum KF : std::uint32_t;

	class GUID;
}

namespace REX
{
	template <REX::win32_character CharT>
	[[nodiscard]]
	auto IsModuleLoaded(REX::BasicZStringView<CharT> a_moduleName) noexcept -> bool;

	template <>
	[[nodiscard]]
	auto IsModuleLoaded(REX::ZStringView a_moduleName) noexcept -> bool;

	template <>
	[[nodiscard]]
	auto IsModuleLoaded(REX::ZWStringView a_moduleName) noexcept -> bool;

	[[nodiscard]]
	auto GetCurrentModuleHandle() noexcept -> REX::W32::HMODULE;
	[[nodiscard]]
	auto GetParentModuleHandle() noexcept -> REX::W32::HMODULE;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle, std::span<CharT> a_buffer) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle, std::span<char> a_buffer) noexcept
		-> std::expected<std::string_view, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle, std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>;

	[[nodiscard]]
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle) noexcept
		-> std::expected<std::filesystem::path, REX::SystemError>;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto GetModuleVersion(REX::BasicZStringView<CharT> a_moduleName, REX::BasicZStringView<CharT> a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleVersion(REX::ZStringView a_moduleName, REX::ZStringView a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleVersion(REX::ZWStringView a_moduleName, REX::ZWStringView a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto GetModuleFileVersion(REX::BasicZStringView<CharT> a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleFileVersion(REX::ZStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleFileVersion(REX::ZWStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>;

	template <REX::win32_character CharT>
	[[nodiscard]]
	auto GetModuleProductVersion(REX::BasicZStringView<CharT> a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleProductVersion(REX::ZStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>;

	template <>
	[[nodiscard]]
	auto GetModuleProductVersion(REX::ZWStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>;

	[[nodiscard]]
	auto GetKnownFolderPath(const REX::W32::GUID& a_folderId, REX::W32::KF a_flags) noexcept
		-> std::expected<std::filesystem::path, REX::SystemError>;

	[[noreturn]]
	void Terminate(std::uint32_t a_exitCode) noexcept;
}
