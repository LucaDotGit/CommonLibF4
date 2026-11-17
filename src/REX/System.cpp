#include "REX/System.hpp"

#include "REX/Concepts.hpp"
#include "REX/Container.hpp"
#include "REX/Error.hpp"
#include "REX/Macros.hpp"
#include "REX/Version.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"
#include "REX/W32/OLE32.hpp"
#include "REX/W32/SHELL32.hpp"
#include "REX/W32/VERSION.hpp"
#include "REX/ZString.hpp"

namespace REX::Impl
{
	namespace
	{
		template <REX::win32_character CharT>
		constexpr auto FILE_VERSION_SUBBLOCK_EN_US =
			REX_STRING_LITERAL(CharT, R"(\StringFileInfo\040904B0\FileVersion)"sv);

		template <REX::win32_character CharT>
		constexpr auto PRODUCT_VERSION_SUBBLOCK_EN_US =
			REX_STRING_LITERAL(CharT, R"(\StringFileInfo\040904B0\ProductVersion)"sv);
	}
}

namespace REX
{
	template <>
	auto IsModuleLoaded(REX::ZStringView a_moduleName) noexcept -> bool
	{
		return REX::W32::GetModuleHandleA(a_moduleName.data()) != 0;
	}

	template <>
	auto IsModuleLoaded(REX::ZWStringView a_moduleName) noexcept -> bool
	{
		return REX::W32::GetModuleHandleW(a_moduleName.data()) != 0;
	}

	auto GetCurrentModuleHandle() noexcept -> REX::W32::HMODULE
	{
		return REX::W32::GetCurrentModule();
	}

	auto GetParentModuleHandle() noexcept -> REX::W32::HMODULE
	{
		return REX::W32::GetParentModule();
	}

	template <>
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle, std::span<char> a_buffer) noexcept
		-> std::expected<std::string_view, REX::SystemError>
	{
		const auto moduleNameSize =
			REX::W32::GetModuleFileNameA(a_moduleHandle, a_buffer.data(), static_cast<std::uint32_t>(a_buffer.size()));
		if (moduleNameSize == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return std::string_view{a_buffer.data(), moduleNameSize};
	}

	template <>
	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle, std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>
	{
		const auto moduleNameSize =
			REX::W32::GetModuleFileNameW(a_moduleHandle, a_buffer.data(), static_cast<std::uint32_t>(a_buffer.size()));
		if (moduleNameSize == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return std::wstring_view{a_buffer.data(), moduleNameSize};
	}

	auto GetModuleFilePath(REX::W32::HMODULE a_moduleHandle) noexcept
		-> std::expected<std::filesystem::path, REX::SystemError>
	{
		auto fileNameBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

		const auto fileNameView = GetModuleFilePath<wchar_t>(a_moduleHandle, fileNameBuffer);
		if (!fileNameView.has_value()) [[unlikely]] {
			return std::unexpected(fileNameView.error());
		}

		try {
			return std::filesystem::path(fileNameView.value(), std::filesystem::path::generic_format);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	template <>
	auto GetModuleVersion(REX::ZStringView a_moduleName, REX::ZStringView a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = static_cast<std::uint32_t>(0);

		const auto versionInfoSize =
			REX::W32::GetFileVersionInfoSizeA(a_moduleName.data(), std::addressof(tempVersionHandle));
		if (versionInfoSize == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionInfoData = std::vector<std::byte>();

		try {
			REX::ResizeForOverwrite(versionInfoData, versionInfoSize);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_VERSION_HANDLE = static_cast<std::uint32_t>(0);

		if (!REX::W32::GetFileVersionInfoA(
				a_moduleName.data(),
				IGNORED_VERSION_HANDLE,
				static_cast<std::uint32_t>(versionInfoData.size()),
				versionInfoData.data())) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionBufferSize = static_cast<std::uint32_t>(0);

		if (!REX::W32::VerQueryValueA(
				versionInfoData.data(),
				a_subblock.data(),
				std::addressof(versionBuffer),
				std::addressof(versionBufferSize))) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionString = std::string_view{reinterpret_cast<const char*>(versionBuffer), versionBufferSize};

		const auto version = Version::FromString(versionString);
		if (!version.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(version.error()));
		}

		return version.value();
	}

	template <>
	auto GetModuleVersion(REX::ZWStringView a_moduleName, REX::ZWStringView a_subblock) noexcept
		-> std::expected<Version, REX::SystemError>
	{
		auto tempVersionHandle = static_cast<std::uint32_t>(0);

		const auto versionInfoSize =
			REX::W32::GetFileVersionInfoSizeW(a_moduleName.data(), std::addressof(tempVersionHandle));
		if (versionInfoSize == 0) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto versionInfoData = std::vector<std::byte>();

		try {
			REX::ResizeForOverwrite(versionInfoData, versionInfoSize);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		constexpr auto IGNORED_VERSION_HANDLE = static_cast<std::uint32_t>(0);

		if (!REX::W32::GetFileVersionInfoW(
				a_moduleName.data(),
				IGNORED_VERSION_HANDLE,
				static_cast<std::uint32_t>(versionInfoData.size()),
				versionInfoData.data())) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto* versionBuffer = static_cast<void*>(nullptr);
		auto versionBufferSize = static_cast<std::uint32_t>(0);

		if (!REX::W32::VerQueryValueW(
				versionInfoData.data(),
				a_subblock.data(),
				std::addressof(versionBuffer),
				std::addressof(versionBufferSize))) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto versionBufferView =
			std::wstring_view{reinterpret_cast<const wchar_t*>(versionBuffer), versionBufferSize};

		const auto version = Version::FromString(versionBufferView);
		if (!version.has_value()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(version.error()));
		}

		return version.value();
	}

	template <>
	auto GetModuleFileVersion(REX::ZStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return GetModuleVersion(a_moduleName, Impl::FILE_VERSION_SUBBLOCK_EN_US<char>);
	}

	template <>
	auto GetModuleFileVersion(REX::ZWStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return GetModuleVersion(a_moduleName, Impl::FILE_VERSION_SUBBLOCK_EN_US<wchar_t>);
	}

	template <>
	auto GetModuleProductVersion(REX::ZStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return GetModuleVersion(a_moduleName, Impl::PRODUCT_VERSION_SUBBLOCK_EN_US<char>);
	}

	template <>
	auto GetModuleProductVersion(REX::ZWStringView a_moduleName) noexcept -> std::expected<Version, REX::SystemError>
	{
		return GetModuleVersion(a_moduleName, Impl::PRODUCT_VERSION_SUBBLOCK_EN_US<wchar_t>);
	}

	auto GetKnownFolderPath(const REX::W32::GUID& a_folderId, REX::W32::KF a_flags) noexcept
		-> std::expected<std::filesystem::path, REX::SystemError>
	{
		class KnownPathBuffer final
		{
		public:
			KnownPathBuffer() noexcept = default;

			~KnownPathBuffer() noexcept
			{
				if (_buffer) {
					REX::W32::CoTaskMemFree(_buffer);
				}
			}

			KnownPathBuffer(const KnownPathBuffer&) = delete;
			KnownPathBuffer(KnownPathBuffer&&) = delete;

			auto operator=(const KnownPathBuffer&) -> KnownPathBuffer& = delete;
			auto operator=(KnownPathBuffer&&) -> KnownPathBuffer& = delete;

			[[nodiscard]]
			auto data() noexcept -> wchar_t*&
			{
				return _buffer;
			}

			[[nodiscard]]
			auto data() const noexcept -> wchar_t* const&
			{
				return _buffer;
			}

		private:
			wchar_t* _buffer{nullptr};
		};

		constexpr auto* IGNORED_FOLDER_TOKEN = static_cast<void*>(nullptr);

		auto knownPathBuffer = KnownPathBuffer();
		if (!REX::W32::SH_SUCCESS(
				REX::W32::SHGetKnownFolderPath(
					a_folderId,
					a_flags,
					IGNORED_FOLDER_TOKEN,
					std::addressof(knownPathBuffer.data())))) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		try {
			return std::filesystem::path(knownPathBuffer.data(), std::filesystem::path::generic_format);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	void Terminate(std::uint32_t a_exitCode) noexcept
	{
		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(a_exitCode);
	}
}
