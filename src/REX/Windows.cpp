#include "REX/Windows.hpp"

#include "REX/Path.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"
#include "REX/W32/VERSION.hpp"

namespace REX::Impl
{
	template <REX::win32_character CharT>
	static constexpr auto US_FILE_VERSION_SUBBLOCK = std::false_type();

	template <>
	constexpr auto US_FILE_VERSION_SUBBLOCK<char> = R"(\StringFileInfo\040904B0\FileVersion)"sv;

	template <>
	constexpr auto US_FILE_VERSION_SUBBLOCK<wchar_t> = LR"(\StringFileInfo\040904B0\FileVersion)"sv;

	template <REX::win32_character CharT>
	static constexpr auto US_PRODUCT_VERSION_SUBBLOCK = std::false_type();

	template <>
	constexpr auto US_PRODUCT_VERSION_SUBBLOCK<char> = R"(\StringFileInfo\040904B0\ProductVersion)"sv;

	template <>
	constexpr auto US_PRODUCT_VERSION_SUBBLOCK<wchar_t> = LR"(\StringFileInfo\040904B0\ProductVersion)"sv;

	template <REX::win32_character CharT>
	[[nodiscard]] static auto GetFileVersion(REX::basic_zstring_view<CharT> a_moduleName, std::basic_string_view<CharT> a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>;

	template <>
	auto GetFileVersion(REX::zstring_view a_moduleName, REX::zstring_view a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = 0ui32;

		const auto versionInfoSize = REX::W32::GetFileVersionInfoSizeA(a_moduleName.data(), std::addressof(tempVersionHandle));
		if (versionInfoSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionInfoData = std::vector<std::byte>();

		try {
			versionInfoData.resize(versionInfoSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_VERSION_HANDLE = 0ui32;

		if (!REX::W32::GetFileVersionInfoA(a_moduleName.data(), IGNORED_VERSION_HANDLE, static_cast<std::uint32_t>(versionInfoData.size()), versionInfoData.data())) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionBufferSize = 0ui32;

		if (!REX::W32::VerQueryValueA(versionInfoData.data(), a_subblock.data(), std::addressof(versionBuffer), std::addressof(versionBufferSize))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionString = std::string_view{ reinterpret_cast<const char*>(versionBuffer), versionBufferSize };

		const auto version = Version::FromString(versionString);
		if (!version) {
			return std::unexpected(REX::CreateSystemError(version.error()));
		}

		return *version;
	}

	template <>
	auto GetFileVersion(REX::zwstring_view a_moduleName, REX::zwstring_view a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = 0ui32;

		const auto versionInfoSize = REX::W32::GetFileVersionInfoSizeW(a_moduleName.data(), std::addressof(tempVersionHandle));
		if (versionInfoSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionInfoData = std::vector<std::byte>();

		try {
			versionInfoData.resize(versionInfoSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_VERSION_HANDLE = 0ui32;

		if (!REX::W32::GetFileVersionInfoW(a_moduleName.data(), IGNORED_VERSION_HANDLE, static_cast<std::uint32_t>(versionInfoData.size()), versionInfoData.data())) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionBufferSize = 0ui32;

		if (!REX::W32::VerQueryValueW(versionInfoData.data(), a_subblock.data(), std::addressof(versionBuffer), std::addressof(versionBufferSize))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionBufferView = std::wstring_view{ reinterpret_cast<const wchar_t*>(versionBuffer), versionBufferSize };

		const auto version = Version::FromString(versionBufferView);
		if (!version) {
			return std::unexpected(REX::CreateSystemError(version.error()));
		}

		return *version;
	}
}

namespace REX
{
	bool IsModuleLoaded(REX::zstring_view a_moduleName) noexcept
	{
		return REX::W32::GetModuleHandleA(a_moduleName.data()) != 0;
	}

	bool IsModuleLoaded(REX::zwstring_view a_moduleName) noexcept
	{
		return REX::W32::GetModuleHandleW(a_moduleName.data()) != 0;
	}

	template <>
	auto GetCurrentModuleFileName(std::span<char> a_buffer) noexcept
		-> std::expected<std::string_view, REX::SystemError>
	{
		if (REX::W32::GetModuleFileNameA(REX::W32::GetCurrentModule(), a_buffer.data(), static_cast<std::uint32_t>(a_buffer.size())) == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return REX::GetFileName(std::string_view(a_buffer.data()));
	}

	template <>
	auto GetCurrentModuleFileName(std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>
	{
		if (REX::W32::GetModuleFileNameW(REX::W32::GetCurrentModule(), a_buffer.data(), static_cast<std::uint32_t>(a_buffer.size())) == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return REX::GetFileName(std::wstring_view(a_buffer.data()));
	}

	template <>
	auto GetCurrentModuleFileName() noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		auto fileNameBuffer = std::array<char, REX::W32::MAX_FNAME>();

		const auto fileNameView = GetCurrentModuleFileName<char>(fileNameBuffer);
		if (!fileNameView) {
			return std::unexpected(fileNameView.error());
		}

		return std::string(fileNameView.value());
	}

	template <>
	auto GetCurrentModuleFileName() noexcept
		-> std::expected<std::wstring, REX::SystemError>
	{
		auto fileNameBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

		const auto fileNameView = GetCurrentModuleFileName<wchar_t>(fileNameBuffer);
		if (!fileNameView) {
			return std::unexpected(fileNameView.error());
		}

		return std::wstring(fileNameView.value());
	}

	auto GetModuleFileVersion(std::string_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_moduleName, Impl::US_FILE_VERSION_SUBBLOCK<char>);
	}

	auto GetModuleFileVersion(std::wstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_moduleName, Impl::US_FILE_VERSION_SUBBLOCK<wchar_t>);
	}

	auto GetModuleProductVersion(std::string_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_moduleName, Impl::US_PRODUCT_VERSION_SUBBLOCK<char>);
	}

	auto GetModuleProductVersion(std::wstring_view a_moduleName) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_moduleName, Impl::US_PRODUCT_VERSION_SUBBLOCK<wchar_t>);
	}
}
