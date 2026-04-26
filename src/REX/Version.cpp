#include "REX/Version.hpp"

#include "REX/W32/VERSION.hpp"

namespace REX
{
	template auto Version::FromString(std::string_view a_version, char a_separator) noexcept -> std::expected<Version, REX::PosixErrorCode>;
	template auto Version::FromString(std::wstring_view a_version, wchar_t a_separator) noexcept -> std::expected<Version, REX::PosixErrorCode>;

	template auto Version::ToString(char a_separator) const -> std::string;
	template auto Version::ToString(wchar_t a_separator) const -> std::wstring;

	static_assert(Version::FromString(""sv) == Version(0, 0, 0, 0));
	static_assert(Version().ToString<char>() == "0.0.0.0"sv);

	static_assert(Version::FromString("1"sv) == Version(1, 0, 0, 0));
	static_assert(Version(1).ToString<char>() == "1.0.0.0"sv);

	static_assert(Version::FromString("1.2"sv) == Version(1, 2, 0, 0));
	static_assert(Version(1, 2).ToString<char>() == "1.2.0.0"sv);

	static_assert(Version::FromString("1.2.3"sv) == Version(1, 2, 3, 0));
	static_assert(Version(1, 2, 3).ToString<char>() == "1.2.3.0"sv);

	static_assert(Version(1, 2, 3, 4).ToString<char>() == "1.2.3.4"sv);

	static_assert(Version::FromString("1-2-3-4"sv, '-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<char>('-') == "1-2-3-4"sv);

	static_assert(Version::FromString(""sv) == Version(0, 0, 0, 0));
	static_assert(Version().ToString<wchar_t>() == L"0.0.0.0"sv);

	static_assert(Version::FromString("1"sv) == Version(1, 0, 0, 0));
	static_assert(Version(1).ToString<wchar_t>() == L"1.0.0.0"sv);

	static_assert(Version::FromString("1.2"sv) == Version(1, 2, 0, 0));
	static_assert(Version(1, 2).ToString<wchar_t>() == L"1.2.0.0"sv);

	static_assert(Version::FromString("1.2.3"sv) == Version(1, 2, 3, 0));
	static_assert(Version(1, 2, 3).ToString<wchar_t>() == L"1.2.3.0"sv);

	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>() == L"1.2.3.4"sv);

	static_assert(Version::FromString("1-2-3-4"sv, '-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>('-') == L"1-2-3-4"sv);

	static_assert(Version::FromString(L"1-2-3-4"sv, L'-') == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).ToString<wchar_t>(L'-') == L"1-2-3-4"sv);

	static_assert(Version::Unpack(0x01020034ui32) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint32_t>() == 0x01020034ui32);

	static_assert(Version::Unpack(0x0001000200030004ui64) == Version(1, 2, 3, 4));
	static_assert(Version(1, 2, 3, 4).Pack<std::uint64_t>() == 0x0001000200030004ui64);
}

namespace REX::Impl
{
	template <REX::win32_character T>
	[[nodiscard]] static auto GetFileVersion(REX::basic_zstring_view<T> a_fileName, std::basic_string_view<T> a_subblock) noexcept -> std::expected<Version, REX::SystemError>;

	template <>
	auto GetFileVersion(REX::zstring_view a_fileName, REX::zstring_view a_subblock) noexcept -> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = 0ui32;

		const auto versionSize = REX::W32::GetFileVersionInfoSizeA(a_fileName.data(), std::addressof(tempVersionHandle));
		if (versionSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionData = std::vector<std::byte>();

		try {
			versionData.resize(versionSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_HANDLE = 0ui32;

		if (!REX::W32::GetFileVersionInfoA(a_fileName.data(), IGNORED_HANDLE, static_cast<std::uint32_t>(versionData.size()), versionData.data())) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionLength = 0ui32;

		if (!REX::W32::VerQueryValueA(versionData.data(), a_subblock.data(), std::addressof(versionBuffer), std::addressof(versionLength))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionString = std::string_view{ reinterpret_cast<const char*>(versionBuffer), versionLength };

		const auto version = Version::FromString(versionString);
		if (!version) {
			return std::unexpected(REX::CreateSystemError(std::move(version).error()));
		}

		return *version;
	}

	template <>
	auto GetFileVersion(REX::zwstring_view a_fileName, REX::zwstring_view a_subblock) noexcept -> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = 0ui32;

		const auto versionSize = REX::W32::GetFileVersionInfoSizeW(a_fileName.data(), std::addressof(tempVersionHandle));
		if (versionSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionData = std::vector<std::byte>();

		try {
			versionData.resize(versionSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_HANDLE = 0ui32;

		if (!REX::W32::GetFileVersionInfoW(a_fileName.data(), IGNORED_HANDLE, static_cast<std::uint32_t>(versionData.size()), versionData.data())) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionLength = 0ui32;

		if (!REX::W32::VerQueryValueW(versionData.data(), a_subblock.data(), std::addressof(versionBuffer), std::addressof(versionLength))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionString = std::wstring_view{ reinterpret_cast<const wchar_t*>(versionBuffer), versionLength };

		const auto version = Version::FromString(versionString);
		if (!version) {
			return std::unexpected(REX::CreateSystemError(std::move(version).error()));
		}

		return *version;
	}
}

namespace REX
{
	template <REX::win32_character T>
	static constexpr auto US_FILE_VERSION_SUBBLOCK = std::basic_string<T>();

	template <>
	constexpr auto US_FILE_VERSION_SUBBLOCK<char> = R"(\StringFileInfo\040904B0\FileVersion)"sv;

	template <>
	constexpr auto US_FILE_VERSION_SUBBLOCK<wchar_t> = LR"(\StringFileInfo\040904B0\FileVersion)"sv;

	template <REX::win32_character T>
	static constexpr auto US_PRODUCT_VERSION_SUBBLOCK = std::basic_string<T>();

	template <>
	constexpr auto US_PRODUCT_VERSION_SUBBLOCK<char> = R"(\StringFileInfo\040904B0\ProductVersion)"sv;

	template <>
	constexpr auto US_PRODUCT_VERSION_SUBBLOCK<wchar_t> = LR"(\StringFileInfo\040904B0\ProductVersion)"sv;

	auto GetFileVersion(std::string_view a_fileName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_fileName, US_FILE_VERSION_SUBBLOCK<char>);
	}

	auto GetFileVersion(std::wstring_view a_fileName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_fileName, US_FILE_VERSION_SUBBLOCK<wchar_t>);
	}

	auto GetProductVersion(std::string_view a_fileName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_fileName, US_PRODUCT_VERSION_SUBBLOCK<char>);
	}

	auto GetProductVersion(std::wstring_view a_fileName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return Impl::GetFileVersion(a_fileName, US_PRODUCT_VERSION_SUBBLOCK<wchar_t>);
	}
}
