#include "REX/FileMemoryMap.hpp"

#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/StaticMap.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"
#include "REX/ZString.hpp"

namespace REX::Impl
{
	namespace
	{
		constexpr auto MEMORY_FILE_ACCESS_FLAGS = REX::CreateStaticMap(
			std::make_pair(REX::FileMemoryMap::Options::Read, REX::W32::GENERIC_READ),
			std::make_pair(REX::FileMemoryMap::Options::ReadWrite, REX::W32::GENERIC_READ | REX::W32::GENERIC_WRITE));

		constexpr auto MEMORY_FILE_SHARE_FLAGS = REX::CreateStaticMap(
			std::make_pair(REX::FileMemoryMap::Options::Read, REX::W32::FILE_SHARE_READ),
			std::make_pair(
				REX::FileMemoryMap::Options::ReadWrite,
				REX::W32::FILE_SHARE_READ | REX::W32::FILE_SHARE_WRITE));

		constexpr auto MEMORY_FILE_MAP_FLAGS = REX::CreateStaticMap(
			std::make_pair(REX::FileMemoryMap::Options::Read, REX::W32::FILE_MAP_READ),
			std::make_pair(REX::FileMemoryMap::Options::ReadWrite, REX::W32::FILE_MAP_ALL_ACCESS));

		constexpr auto MEMORY_FILE_PROTECTION_FLAGS = REX::CreateStaticMap(
			std::make_pair(REX::FileMemoryMap::Options::Read, REX::W32::PAGE_READONLY),
			std::make_pair(REX::FileMemoryMap::Options::ReadWrite, REX::W32::PAGE_READWRITE));

		[[nodiscard]]
		constexpr auto GetMemoryFileAccessFlags(REX::FileMemoryMap::Options a_options) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* accessFlagsIt = MEMORY_FILE_ACCESS_FLAGS.find(a_options);
			if (accessFlagsIt == MEMORY_FILE_ACCESS_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return accessFlagsIt->second;
		}

		[[nodiscard]]
		constexpr auto GetMemoryFileShareFlags(REX::FileMemoryMap::Options a_options) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* shareFlagsIt = MEMORY_FILE_SHARE_FLAGS.find(a_options);
			if (shareFlagsIt == MEMORY_FILE_SHARE_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return shareFlagsIt->second;
		}

		[[nodiscard]]
		constexpr auto GetMemoryFileMapFlags(REX::FileMemoryMap::Options a_options) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* mapFlagsIt = MEMORY_FILE_MAP_FLAGS.find(a_options);
			if (mapFlagsIt == MEMORY_FILE_MAP_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return mapFlagsIt->second;
		}

		[[nodiscard]]
		constexpr auto GetMemoryFileProtectionFlags(REX::FileMemoryMap::Options a_options) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* protectionFlagsIt = MEMORY_FILE_PROTECTION_FLAGS.find(a_options);
			if (protectionFlagsIt == MEMORY_FILE_PROTECTION_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return protectionFlagsIt->second;
		}
	}
}

namespace REX
{
	FileMemoryMap::FileMemoryMap() = default;

	FileMemoryMap::~FileMemoryMap() noexcept
	{
		Close();
	}

	FileMemoryMap::FileMemoryMap(FileMemoryMap&& a_other) noexcept :
		_fileHandle(std::exchange(a_other._fileHandle, REX::W32::INVALID_HANDLE_VALUE)),
		_mapHandle(std::exchange(a_other._mapHandle, 0)),
		_mapViewHandle(std::exchange(a_other._mapViewHandle, nullptr)),
		_size(std::exchange(a_other._size, 0)),
		_isOwner(std::exchange(a_other._isOwner, false))
	{
	}

	auto FileMemoryMap::operator=(FileMemoryMap&& a_other) noexcept -> FileMemoryMap&
	{
		if (this == std::addressof(a_other)) {
			return *this;
		}

		Close();

		_fileHandle = std::exchange(a_other._fileHandle, REX::W32::INVALID_HANDLE_VALUE);
		_mapHandle = std::exchange(a_other._mapHandle, 0);
		_mapViewHandle = std::exchange(a_other._mapViewHandle, nullptr);
		_size = std::exchange(a_other._size, 0);
		_isOwner = std::exchange(a_other._isOwner, false);

		return *this;
	}

	auto FileMemoryMap::Create(REX::ZStringView a_name, REX::FileMemoryMap::Options a_options, size_type a_maxSize)
		noexcept -> REX::SystemError
	{
		Close();

		if (a_maxSize == 0) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::invalid_argument);
		}

		const auto createError = CreateImpl(REX::W32::INVALID_HANDLE_VALUE, a_name, a_options, a_maxSize);
		if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return createError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileMemoryMap::Create(
		const std::filesystem::path& a_filePath,
		REX::ZStringView a_name,
		REX::FileMemoryMap::Options a_options,
		size_type a_maxSize) noexcept -> REX::SystemError
	{
		Close();

		if (a_maxSize == 0) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::invalid_argument);
		}

		const auto accessFlags = Impl::GetMemoryFileAccessFlags(a_options);
		if (!accessFlags.has_value()) [[unlikely]] {
			return accessFlags.error();
		}

		const auto shareFlags = Impl::GetMemoryFileShareFlags(a_options);
		if (!shareFlags.has_value()) [[unlikely]] {
			return shareFlags.error();
		}

		constexpr auto* SECURITY_ATTRIBUTES = static_cast<REX::W32::SECURITY_ATTRIBUTES*>(nullptr);
		constexpr auto TEMPLATE_FILE_HANDLE = static_cast<REX::W32::HANDLE>(0);

		const auto fileHandle = REX::W32::CreateFileW(
			a_filePath.native().data(),
			accessFlags.value(),
			shareFlags.value(),
			SECURITY_ATTRIBUTES,
			REX::W32::OPEN_EXISTING,
			REX::W32::FILE_ATTRIBUTE_READONLY,
			TEMPLATE_FILE_HANDLE);
		if (fileHandle == REX::W32::INVALID_HANDLE_VALUE) [[unlikely]] {
			return REX::GetCurrentSystemError();
		}

		const auto createError = CreateImpl(fileHandle, a_name, a_options, a_maxSize);
		if (createError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			REX::W32::CloseHandle(fileHandle);
			return createError;
		}

		_fileHandle = fileHandle;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	void FileMemoryMap::Close() noexcept
	{
		if (_mapViewHandle) {
			if (!REX::W32::UnmapViewOfFile(_mapViewHandle)) [[unlikely]] {
				REX::Assert(false);
			}

			_mapViewHandle = nullptr;
		}

		if (_mapHandle != 0) {
			if (!REX::W32::CloseHandle(_mapHandle)) [[unlikely]] {
				REX::Assert(false);
			}

			_mapHandle = 0;
		}

		if (_fileHandle != REX::W32::INVALID_HANDLE_VALUE) {
			if (!REX::W32::CloseHandle(_fileHandle)) [[unlikely]] {
				REX::Assert(false);
			}

			_fileHandle = REX::W32::INVALID_HANDLE_VALUE;
		}

		_size = 0;
		_isOwner = false;
	}

	auto FileMemoryMap::CreateImpl(
		REX::W32::HANDLE a_fileHandle,
		REX::ZStringView a_name,
		REX::FileMemoryMap::Options a_options,
		size_type a_maxSize) noexcept -> REX::SystemError
	{
		const auto actualSize = [a_fileHandle, a_maxSize]() noexcept -> std::expected<std::size_t, REX::SystemError> {
			if (a_maxSize == 0) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			if (a_maxSize != std::dynamic_extent) {
				return a_maxSize;
			}

			if (a_fileHandle == REX::W32::INVALID_HANDLE_VALUE) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
			}

			auto fileSize = static_cast<std::int64_t>(0);
			if (!REX::W32::GetFileSizeEx(a_fileHandle, std::addressof(fileSize))) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return fileSize;
		}();

		if (!actualSize.has_value()) [[unlikely]] {
			return actualSize.error();
		}

		auto isOwner = false;

		const auto mapHandle = [a_fileHandle, a_name, a_options, actualSize, &isOwner]() noexcept
			-> std::expected<REX::W32::HANDLE, REX::SystemError> {
			const auto mapFlags = Impl::GetMemoryFileMapFlags(a_options);
			if (!mapFlags.has_value()) [[unlikely]] {
				return std::unexpected(mapFlags.error());
			}

			constexpr auto INHERIT_HANDLE = false;

			const auto openMapHandle = REX::W32::OpenFileMappingA(mapFlags.value(), INHERIT_HANDLE, a_name.data());
			if (openMapHandle != 0) {
				return openMapHandle;
			}

			constexpr auto* SECURITY_ATTRIBUTES = static_cast<REX::W32::SECURITY_ATTRIBUTES*>(nullptr);

			const auto protectionFlags = Impl::GetMemoryFileProtectionFlags(a_options);
			if (!protectionFlags.has_value()) [[unlikely]] {
				return std::unexpected(protectionFlags.error());
			}

			const auto mapHandle = REX::W32::CreateFileMappingA(
				a_fileHandle,
				SECURITY_ATTRIBUTES,
				protectionFlags.value(),
				actualSize.value(),
				a_name.data());
			if (mapHandle == 0) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			isOwner = true;
			return mapHandle;
		}();

		if (!mapHandle.has_value()) [[unlikely]] {
			return mapHandle.error();
		}

		const auto mapViewHandle =
			[mapHandle, a_options, actualSize]() noexcept -> std::expected<void*, REX::SystemError> {
			const auto mapFlags = Impl::GetMemoryFileMapFlags(a_options);
			if (!mapFlags.has_value()) [[unlikely]] {
				return std::unexpected(mapFlags.error());
			}

			constexpr auto FILE_OFFSET = static_cast<std::size_t>(0);

			auto* mapViewHandle =
				REX::W32::MapViewOfFile(mapHandle.value(), mapFlags.value(), FILE_OFFSET, actualSize.value());
			if (!mapViewHandle) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return mapViewHandle;
		}();

		if (!mapViewHandle.has_value()) [[unlikely]] {
			if (!REX::W32::CloseHandle(mapHandle.value())) [[unlikely]] {
				REX::Assert(false);
			}

			return mapViewHandle.error();
		}

		_mapHandle = mapHandle.value();
		_mapViewHandle = mapViewHandle.value();
		_size = static_cast<size_type>(actualSize.value());
		_isOwner = isOwner;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}
