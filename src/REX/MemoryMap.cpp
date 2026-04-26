#include "REX/MemoryMap.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX
{
	MemoryMap::MemoryMap() = default;

	MemoryMap::~MemoryMap() noexcept
	{
		Close();
	}

	REX::SystemError MemoryMap::Create(bool a_write, std::string_view a_name, size_type a_size) noexcept
	{
		Close();

		auto createError = CreateImpl(a_write, REX::W32::INVALID_HANDLE_VALUE, a_name, a_size);
		if (createError.value() != REX::ERROR_NUMBER_SUCCESS) {
			return createError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	REX::SystemError MemoryMap::Create(bool a_write, const std::filesystem::path& a_path, std::string_view a_name, size_type a_size) noexcept
	{
		Close();

		const auto doAccess = a_write ? REX::W32::GENERIC_READ | REX::W32::GENERIC_WRITE : REX::W32::GENERIC_READ;
		const auto doShare = a_write ? REX::W32::FILE_SHARE_READ | REX::W32::FILE_SHARE_WRITE : REX::W32::FILE_SHARE_READ;

		constexpr auto* SECURITY_ATTRIBUTES = static_cast<REX::W32::SECURITY_ATTRIBUTES*>(nullptr);
		constexpr auto TEMPLATE_FILE = static_cast<REX::W32::HANDLE>(0);

		auto fileHandle = REX::W32::CreateFileA(a_path.generic_string().data(),
			doAccess, doShare, SECURITY_ATTRIBUTES, REX::W32::OPEN_EXISTING, REX::W32::FILE_ATTRIBUTE_READONLY, TEMPLATE_FILE);
		if (!fileHandle || fileHandle == REX::W32::INVALID_HANDLE_VALUE) {
			return REX::GetCurrentSystemError();
		}

		auto createError = CreateImpl(a_write, fileHandle, a_name, a_size);
		if (createError.value() != REX::ERROR_NUMBER_SUCCESS) {
			REX::W32::CloseHandle(fileHandle);
			return createError;
		}

		_fileHandle = fileHandle;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	void MemoryMap::Close() noexcept
	{
		if (_mapViewHandle) {
			REX::W32::UnmapViewOfFile(_mapViewHandle);
			_mapViewHandle = nullptr;
		}

		if (_mapHandle) {
			REX::W32::CloseHandle(_mapHandle);
			_mapHandle = 0;
		}

		if (_fileHandle && _fileHandle != REX::W32::INVALID_HANDLE_VALUE) {
			REX::W32::CloseHandle(_fileHandle);
			_fileHandle = REX::W32::INVALID_HANDLE_VALUE;
		}

		_size = 0;
		_isOwner = false;
	}

	REX::SystemError MemoryMap::CreateImpl(bool a_write, REX::W32::HANDLE a_fileHandle, std::string_view a_name, size_type a_size) noexcept
	{
		auto actualSize = 0i64;
		if (a_size == std::dynamic_extent) {
			if (!a_fileHandle || a_fileHandle == REX::W32::INVALID_HANDLE_VALUE) {
				return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
			}

			if (!W32::GetFileSizeEx(a_fileHandle, std::addressof(actualSize))) {
				return REX::GetCurrentSystemError();
			}
		}
		else {
			actualSize = static_cast<std::int64_t>(a_size);
		}

		const auto doAccess = a_write ? REX::W32::FILE_MAP_READ | REX::W32::FILE_MAP_WRITE : REX::W32::FILE_MAP_READ;

		auto isOwner = false;

		auto mapHandle = REX::W32::OpenFileMappingA(doAccess, false, a_name.data());
		if (!mapHandle) {
			constexpr auto* SECURITY_ATTRIBUTES = static_cast<REX::W32::SECURITY_ATTRIBUTES*>(nullptr);
			const auto protect = a_write ? REX::W32::PAGE_READWRITE : REX::W32::PAGE_READONLY;
			const auto sizeHigh = reinterpret_cast<const W32::LARGE_INTEGER*>(std::addressof(actualSize))->highPart;
			const auto sizeLow = reinterpret_cast<const W32::LARGE_INTEGER*>(std::addressof(actualSize))->lowPart;

			mapHandle = REX::W32::CreateFileMappingA(a_fileHandle, SECURITY_ATTRIBUTES, protect, sizeHigh, sizeLow, a_name.data());
			if (!mapHandle) {
				return REX::GetCurrentSystemError();
			}

			isOwner = true;
		}

		constexpr auto FILE_OFFSET_HIGH = 0ui32;
		constexpr auto FILE_OFFSET_LOW = 0ui32;

		auto* mapViewHandle = REX::W32::MapViewOfFile(mapHandle, doAccess, FILE_OFFSET_HIGH, FILE_OFFSET_LOW, actualSize);
		if (!mapViewHandle) {
			return REX::GetCurrentSystemError();
		}

		_mapHandle = mapHandle;
		_mapViewHandle = mapViewHandle;
		_size = static_cast<size_type>(actualSize);
		_isOwner = isOwner;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}
