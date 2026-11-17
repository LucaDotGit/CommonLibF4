#include "REX/FileStream.hpp"

#include "REX/Container.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Localization.hpp"
#include "REX/SeekOrigin.hpp"
#include "REX/StaticMap.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REX::Impl
{
	namespace
	{
		constexpr auto READ_WRITE_MAX_CHUNK_SIZE = std::numeric_limits<std::uint32_t>::max();

		constexpr auto FILE_MODE_FLAGS = REX::CreateStaticMap(
			std::make_pair(FileMode::CreateNew, static_cast<std::uint32_t>(REX::W32::CREATE_NEW)),
			std::make_pair(FileMode::Create, static_cast<std::uint32_t>(REX::W32::CREATE_ALWAYS)),
			std::make_pair(FileMode::Open, static_cast<std::uint32_t>(REX::W32::OPEN_EXISTING)),
			std::make_pair(FileMode::OpenOrCreate, static_cast<std::uint32_t>(REX::W32::OPEN_ALWAYS)),
			std::make_pair(FileMode::Truncate, static_cast<std::uint32_t>(REX::W32::TRUNCATE_EXISTING)),
			std::make_pair(FileMode::Append, static_cast<std::uint32_t>(REX::W32::OPEN_ALWAYS)));

		constexpr auto FILE_ACCESS_FLAGS = REX::CreateStaticMap(
			std::make_pair(FileAccess::Read, static_cast<std::uint32_t>(REX::W32::GENERIC_READ)),
			std::make_pair(FileAccess::Write, static_cast<std::uint32_t>(REX::W32::GENERIC_WRITE)),
			std::make_pair(
				FileAccess::ReadWrite,
				static_cast<std::uint32_t>(REX::W32::GENERIC_READ | REX::W32::GENERIC_WRITE)));

		constexpr auto FILE_SHARE_FLAGS = REX::CreateStaticMap(
			std::make_pair(FileShare::None, static_cast<std::uint32_t>(0)),
			std::make_pair(FileShare::Read, static_cast<std::uint32_t>(REX::W32::FILE_SHARE_READ)),
			std::make_pair(FileShare::Write, static_cast<std::uint32_t>(REX::W32::FILE_SHARE_WRITE)),
			std::make_pair(
				FileShare::ReadWrite,
				static_cast<std::uint32_t>(REX::W32::FILE_SHARE_READ | REX::W32::FILE_SHARE_WRITE)),
			std::make_pair(FileShare::Delete, static_cast<std::uint32_t>(REX::W32::FILE_SHARE_DELETE)),
			std::make_pair(FileShare::Inheritable, static_cast<std::uint32_t>(0)));

		constexpr auto FILE_OPTION_FLAGS = REX::CreateStaticMap(
			std::make_pair(FileOptions::None, static_cast<std::uint32_t>(0)),
			std::make_pair(FileOptions::DeleteOnClose, static_cast<std::uint32_t>(REX::W32::FILE_FLAG_DELETE_ON_CLOSE)),
			std::make_pair(
				FileOptions::SequentialScan,
				static_cast<std::uint32_t>(REX::W32::FILE_FLAG_SEQUENTIAL_SCAN)),
			std::make_pair(FileOptions::RandomAccess, static_cast<std::uint32_t>(REX::W32::FILE_FLAG_RANDOM_ACCESS)),
			std::make_pair(FileOptions::WriteThrough, static_cast<std::uint32_t>(REX::W32::FILE_FLAG_WRITE_THROUGH)));

		static_assert(FILE_MODE_FLAGS.size() == static_cast<std::size_t>(FileMode::_Count));
		static_assert(FILE_ACCESS_FLAGS.size() == static_cast<std::size_t>(FileAccess::_Count));
		static_assert(FILE_SHARE_FLAGS.size() == static_cast<std::size_t>(FileShare::_Count));

		class HandleReadWriteResult final
		{
		public:
			FileStream::size_type size{0};
			REX::SystemError error;
		};

		[[nodiscard]]
		constexpr auto GetFileModeFlags(FileMode a_mode) noexcept -> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* modeIt = FILE_MODE_FLAGS.find(a_mode);
			if (modeIt == FILE_MODE_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return modeIt->second;
		}

		[[nodiscard]]
		constexpr auto GetFileAccessFlags(FileAccess a_access) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* accessIt = FILE_ACCESS_FLAGS.find(a_access);
			if (accessIt == FILE_ACCESS_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return accessIt->second;
		}

		[[nodiscard]]
		constexpr auto GetFileShareFlags(FileShare a_share) noexcept -> std::expected<std::uint32_t, REX::SystemError>
		{
			const auto* shareIt = FILE_SHARE_FLAGS.find(a_share);
			if (shareIt == FILE_SHARE_FLAGS.end()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return shareIt->second;
		}

		[[nodiscard]]
		constexpr auto GetFileOptionFlags(FileOptions a_options) noexcept
			-> std::expected<std::uint32_t, REX::SystemError>
		{
			if (a_options == FileOptions::None) {
				return static_cast<std::uint32_t>(0);
			}

			const auto optionSet = REX::EnumSet(a_options);
			if (optionSet.none(FileOptions::_All)) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			auto optionFlags = static_cast<std::uint32_t>(FileOptions::None);
			for (auto&& [option, flag] : FILE_OPTION_FLAGS) {
				if (optionSet.any(option)) {
					optionFlags |= flag;
				}
			}

			return optionFlags;
		}

		[[nodiscard]]
		auto OpenHandle(
			const std::filesystem::path& a_path,
			FileMode a_mode,
			FileAccess a_access,
			FileShare a_share,
			FileOptions a_options) noexcept -> std::expected<REX::W32::HANDLE, REX::SystemError>
		{
			REX::Assert(a_mode >= FileMode::_Min && a_mode <= FileMode::_Max);
			REX::Assert(a_access >= FileAccess::_Min && a_access <= FileAccess::_Max);
			REX::Assert(a_share >= FileShare::_Min && a_share <= FileShare::_Max);
			REX::Assert(a_options >= FileOptions::None && a_options <= FileOptions::_All);

			const auto modeFlags = GetFileModeFlags(a_mode);
			if (!modeFlags.has_value()) [[unlikely]] {
				return std::unexpected(modeFlags.error());
			}

			const auto accessFlags = GetFileAccessFlags(a_access);
			if (!accessFlags.has_value()) [[unlikely]] {
				return std::unexpected(accessFlags.error());
			}

			const auto shareFlags = GetFileShareFlags(a_share);
			if (!shareFlags.has_value()) [[unlikely]] {
				return std::unexpected(shareFlags.error());
			}

			const auto optionFlags = GetFileOptionFlags(a_options);
			if (!optionFlags.has_value()) [[unlikely]] {
				return std::unexpected(optionFlags.error());
			}

			auto securityAttributes = REX::W32::SECURITY_ATTRIBUTES{
				.length = sizeof(REX::W32::SECURITY_ATTRIBUTES),
				.securityDescriptor = nullptr,
				.inheritHandle = static_cast<REX::W32::BOOL>(a_share == FileShare::Inheritable)
			};

			constexpr auto TEMPLATE_FILE_HANDLE = static_cast<REX::W32::HANDLE>(0);

			const auto handle = REX::W32::CreateFileW(
				a_path.native().data(),
				accessFlags.value(),
				shareFlags.value(),
				std::addressof(securityAttributes),
				modeFlags.value(),
				optionFlags.value(),
				TEMPLATE_FILE_HANDLE);
			if (handle == REX::W32::INVALID_HANDLE_VALUE) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			if (a_mode == FileMode::Append && !REX::W32::SetFilePointerEx(handle, 0, nullptr, REX::W32::FILE_END))
				[[unlikely]] {
				const auto currentError = REX::GetCurrentSystemError();
				std::ignore = REX::W32::CloseHandle(handle);
				return std::unexpected(currentError);
			}

			return handle;
		}

		[[nodiscard]]
		auto CloseHandle(REX::W32::HANDLE a_handle) noexcept -> REX::SystemError
		{
			if (!REX::W32::CloseHandle(a_handle)) [[unlikely]] {
				return REX::GetCurrentSystemError();
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		[[nodiscard]]
		auto GetHandleSize(REX::W32::HANDLE a_handle) noexcept -> std::expected<FileStream::size_type, REX::SystemError>
		{
			auto fileSize = static_cast<FileStream::difference_type>(0);
			if (!REX::W32::GetFileSizeEx(a_handle, std::addressof(fileSize))) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return static_cast<FileStream::size_type>(fileSize);
		}

		[[nodiscard]]
		auto SetHandleSize(REX::W32::HANDLE a_handle, FileStream::FileStream::size_type a_size) noexcept
			-> REX::SystemError
		{
			if (!REX::W32::SetFilePointerEx(
					a_handle,
					static_cast<FileStream::difference_type>(a_size),
					nullptr,
					REX::W32::FILE_BEGIN)) [[unlikely]] {
				return REX::GetCurrentSystemError();
			}

			if (!REX::W32::SetEndOfFile(a_handle)) [[unlikely]] {
				return REX::GetCurrentSystemError();
			}

			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		[[nodiscard]]
		auto SeekHandle(
			REX::W32::HANDLE a_handle,
			FileStream::FileStream::difference_type a_offset,
			SeekOrigin a_seekOrigin) noexcept -> std::expected<FileStream::size_type, REX::SystemError>
		{
			static_assert((static_cast<std::int32_t>(REX::SeekOrigin::Begin) - 1) == REX::W32::FILE_BEGIN);
			static_assert((static_cast<std::int32_t>(REX::SeekOrigin::Current) - 1) == REX::W32::FILE_CURRENT);
			static_assert((static_cast<std::int32_t>(REX::SeekOrigin::End) - 1) == REX::W32::FILE_END);

			REX::Assert(a_seekOrigin >= SeekOrigin::Begin && a_seekOrigin <= SeekOrigin::End);

			auto currentPosition = static_cast<FileStream::difference_type>(0);
			if (!REX::W32::SetFilePointerEx(
					a_handle,
					static_cast<FileStream::difference_type>(a_offset),
					std::addressof(currentPosition),
					static_cast<std::uint32_t>(std::to_underlying(a_seekOrigin) - 1))) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return static_cast<FileStream::size_type>(currentPosition);
		}

		[[nodiscard]]
		auto TryReadHandle(
			REX::W32::HANDLE a_handle,
			FileStream::FileStream::pointer a_buffer,
			FileStream::size_type a_count) noexcept -> HandleReadWriteResult
		{
			if (a_count == 0) {
				return {.size = 0, .error = REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS)};
			}

			if (!a_buffer) [[unlikely]] {
				return {.size = 0, .error = REX::CreateSystemError(REX::PosixErrorCode::invalid_argument)};
			}

			auto totalReadSize = static_cast<FileStream::size_type>(0);
			while (totalReadSize < a_count) {
				const auto remainingChunkSize = a_count - totalReadSize;
				const auto currentChunkSize =
					std::min(remainingChunkSize, static_cast<FileStream::size_type>(READ_WRITE_MAX_CHUNK_SIZE));

				constexpr auto OVERLAPPED = static_cast<REX::W32::OVERLAPPED*>(nullptr);

				auto readSize = static_cast<std::uint32_t>(0);
				if (!REX::W32::ReadFile(
						a_handle,
						a_buffer + totalReadSize,
						static_cast<decltype(readSize)>(currentChunkSize),
						std::addressof(readSize),
						OVERLAPPED)) [[unlikely]] {
					return {.size = totalReadSize, .error = REX::GetCurrentSystemError()};
				}

				if (readSize == 0) {
					break;
				}

				totalReadSize += readSize;
			}

			return {.size = totalReadSize, .error = REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS)};
		}

		[[nodiscard]]
		auto TryWriteHandle(
			REX::W32::HANDLE a_handle,
			FileStream::FileStream::const_pointer a_buffer,
			FileStream::size_type a_count) noexcept -> HandleReadWriteResult
		{
			if (a_count == 0) {
				return {.size = 0, .error = REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS)};
			}

			if (!a_buffer) [[unlikely]] {
				return {.size = 0, .error = REX::CreateSystemError(REX::PosixErrorCode::invalid_argument)};
			}

			auto totalWriteSize = static_cast<FileStream::size_type>(0);
			while (totalWriteSize < a_count) {
				const auto remainingChunkSize = a_count - totalWriteSize;
				const auto currentChunkSize =
					std::min(remainingChunkSize, static_cast<FileStream::size_type>(READ_WRITE_MAX_CHUNK_SIZE));

				constexpr auto OVERLAPPED = static_cast<REX::W32::OVERLAPPED*>(nullptr);

				auto writeSize = static_cast<std::uint32_t>(0);
				if (!REX::W32::WriteFile(
						a_handle,
						a_buffer + totalWriteSize,
						static_cast<decltype(writeSize)>(currentChunkSize),
						std::addressof(writeSize),
						OVERLAPPED)) [[unlikely]] {
					return {.size = totalWriteSize, .error = REX::GetCurrentSystemError()};
				}

				if (writeSize == 0) [[unlikely]] {
					return {.size = totalWriteSize, .error = REX::CreateSystemError(REX::PosixErrorCode::io_error)};
				}

				totalWriteSize += writeSize;
			}

			return {.size = totalWriteSize, .error = REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS)};
		}
	}
}

namespace REX
{
	FileStream::FileStream(
		REX::W32::HANDLE a_handle,
		std::filesystem::path a_path,
		FileMode a_mode,
		FileAccess a_access,
		FileShare a_share,
		FileOptions a_options,
		FileBufferOptions a_bufferOptions) noexcept :
		_handle(a_handle),
		_path(std::move(a_path)),
		_mode(a_mode),
		_access(a_access),
		_share(a_share),
		_options(a_options),
		_buffer{
			.data = nullptr,
			.options = a_bufferOptions,
			.size = 0,
			.position = 0,
			.startPosition = 0,
			.mode = BufferMode::None
		}
	{
		REX::Assert(a_mode >= FileMode::_Min && a_mode <= FileMode::_Max);
		REX::Assert(a_access >= FileAccess::_Min && a_access <= FileAccess::_Max);
		REX::Assert(a_share >= FileShare::_Min && a_share <= FileShare::_Max);
		REX::Assert(a_options >= FileOptions::None && a_options <= FileOptions::_All);
	}

	FileStream::FileStream() noexcept :
		FileStream(
			REX::W32::INVALID_HANDLE_VALUE,
			std::filesystem::path(),
			FileMode::_Min,
			FileAccess::_Min,
			FileShare::None,
			FileOptions::None,
			DEFAULT_FILE_BUFFER_OPTIONS)
	{
	}

	FileStream::~FileStream() noexcept
	{
		std::ignore = Close();
	}

	FileStream::FileStream(FileStream&& a_rhs) noexcept :
		_handle(std::exchange(a_rhs._handle, REX::W32::INVALID_HANDLE_VALUE)),
		_path(std::move(a_rhs._path)),
		_mode(std::exchange(a_rhs._mode, FileMode::_Min)),
		_access(std::exchange(a_rhs._access, FileAccess::_Min)),
		_share(std::exchange(a_rhs._share, FileShare::None)),
		_options(std::exchange(a_rhs._options, FileOptions::None)),
		_buffer(std::move(a_rhs._buffer))
	{
	}

	auto FileStream::operator=(FileStream&& a_rhs) noexcept -> FileStream&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		std::ignore = Close();

		_handle = std::exchange(a_rhs._handle, REX::W32::INVALID_HANDLE_VALUE);
		_path = std::move(a_rhs._path);
		_mode = std::exchange(a_rhs._mode, FileMode::_Min);
		_access = std::exchange(a_rhs._access, FileAccess::_Min);
		_share = std::exchange(a_rhs._share, FileShare::None);
		_options = std::exchange(a_rhs._options, FileOptions::None);
		_buffer = std::move(a_rhs._buffer);

		return *this;
	}

	auto FileStream::IsOpen() const noexcept -> bool
	{
		return _handle != REX::W32::INVALID_HANDLE_VALUE;
	}

	auto FileStream::IsReadable() const noexcept -> bool
	{
		if (!IsOpen()) {
			return false;
		}

		switch (_access.get()) {
			case FileAccess::Read:
			case FileAccess::ReadWrite: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto FileStream::IsWritable() const noexcept -> bool
	{
		if (!IsOpen()) {
			return false;
		}

		switch (_access.get()) {
			case FileAccess::Write:
			case FileAccess::ReadWrite: {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	auto FileStream::IsSeekable() const noexcept -> bool
	{
		if (!IsOpen()) {
			return false;
		}

		return _mode != FileMode::Append;
	}

	auto FileStream::Open(std::filesystem::path a_path, FileMode a_mode, FileAccess a_access) noexcept
		-> std::expected<FileStream, REX::SystemError>
	{
		return Open(std::move(a_path), a_mode, a_access, FileShare::None);
	}

	auto FileStream::Open(std::filesystem::path a_path, FileMode a_mode, FileAccess a_access, FileShare a_share)
		noexcept -> std::expected<FileStream, REX::SystemError>
	{
		return Open(std::move(a_path), a_mode, a_access, a_share, FileOptions::None);
	}

	auto FileStream::Open(
		std::filesystem::path a_path,
		FileMode a_mode,
		FileAccess a_access,
		FileShare a_share,
		FileOptions a_options) noexcept -> std::expected<FileStream, REX::SystemError>
	{
		return Open(std::move(a_path), a_mode, a_access, a_share, a_options, DEFAULT_FILE_BUFFER_OPTIONS);
	}

	auto FileStream::Open(
		std::filesystem::path a_path,
		FileMode a_mode,
		FileAccess a_access,
		FileShare a_share,
		FileOptions a_options,
		FileBufferOptions a_bufferOptions) noexcept -> std::expected<FileStream, REX::SystemError>
	{
		if (a_bufferOptions.capacity == 0 || a_bufferOptions.readChunkSize == 0) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		const auto handle = Impl::OpenHandle(a_path, a_mode, a_access, a_share, a_options);
		if (!handle.has_value()) [[unlikely]] {
			return std::unexpected(handle.error());
		}

		return FileStream(handle.value(), std::move(a_path), a_mode, a_access, a_share, a_options, a_bufferOptions);
	}

	auto FileStream::Flush() noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		return FlushBuffer();
	}

	auto FileStream::Close() noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		const auto flushError = FlushBuffer();
		const auto closeError = Impl::CloseHandle(_handle);

		_handle = REX::W32::INVALID_HANDLE_VALUE;

		ReleaseBuffer();

		if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return flushError;
		}

		return closeError;
	}

	auto FileStream::GetPosition() const noexcept -> std::expected<size_type, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsSeekable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		return GetBufferedPosition();
	}

	auto FileStream::SetPosition(size_type a_position) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsSeekable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		const auto synchronizeError = SynchronizeBuffer();
		if (synchronizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return synchronizeError;
		}

		const auto newPosition =
			Impl::SeekHandle(_handle, static_cast<FileStream::difference_type>(a_position), SeekOrigin::Begin);
		if (!newPosition.has_value()) [[unlikely]] {
			return newPosition.error();
		}

		_buffer.startPosition = newPosition.value();

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::GetSize() const noexcept -> std::expected<size_type, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		const auto size = Impl::GetHandleSize(_handle);
		if (!size.has_value()) [[unlikely]] {
			return std::unexpected(size.error());
		}

		if (_buffer.mode != BufferMode::Write) {
			return size.value();
		}

		if (!IsSeekable()) {
			return size.value() + _buffer.size;
		}

		return std::max(size.value(), _buffer.startPosition + _buffer.size);
	}

	auto FileStream::SetSize(size_type a_size) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsWritable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		const auto synchronizeError = SynchronizeBuffer();
		if (synchronizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return synchronizeError;
		}

		return Impl::SetHandleSize(_handle, a_size);
	}

	auto FileStream::Seek(difference_type a_offset, SeekOrigin a_seekOrigin) noexcept
		-> std::expected<size_type, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsSeekable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		const auto synchronizeError = SynchronizeBuffer();
		if (synchronizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return std::unexpected(synchronizeError);
		}

		const auto newPosition = Impl::SeekHandle(_handle, a_offset, a_seekOrigin);
		if (!newPosition.has_value()) [[unlikely]] {
			return std::unexpected(newPosition.error());
		}

		_buffer.startPosition = newPosition.value();

		return newPosition.value();
	}

	auto FileStream::Peek() noexcept -> std::expected<std::byte, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable() || !IsSeekable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		if (_buffer.mode != BufferMode::Read || _buffer.position >= _buffer.size) {
			const auto readBufferError = PrepareReadBuffer();
			if (readBufferError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return std::unexpected(readBufferError);
			}
		}

		if (_buffer.position >= _buffer.size) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(END_OF_FILE_ERROR_CODE));
		}

		return _buffer.data[_buffer.position];
	}

	auto FileStream::TryRead(pointer a_buffer, size_type a_count) noexcept -> std::expected<size_type, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		if (a_count == 0) {
			return static_cast<size_type>(0);
		}

		if (!a_buffer) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
		}

		auto totalReadSize = static_cast<size_type>(0);
		while (totalReadSize < a_count) {
			if (_buffer.mode == BufferMode::Write) {
				const auto flushError = FlushBuffer();
				if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return std::unexpected(flushError);
				}
			}

			if (_buffer.mode == BufferMode::Read) {
				const auto availableSize = _buffer.size - _buffer.position;
				if (availableSize != 0) {
					const auto currentReadSize = std::min(a_count - totalReadSize, availableSize);
					std::copy_n(_buffer.data.get() + _buffer.position, currentReadSize, a_buffer + totalReadSize);

					_buffer.position += currentReadSize;
					totalReadSize += currentReadSize;
					continue;
				}

				ResetBuffer();
			}

			const auto remainingSize = a_count - totalReadSize;
			if (remainingSize >= _buffer.options.capacity) {
				const auto readResult = Impl::TryReadHandle(_handle, a_buffer + totalReadSize, remainingSize);

				totalReadSize += readResult.size;
				_buffer.startPosition += readResult.size;

				if (readResult.error.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return std::unexpected(readResult.error);
				}

				if (readResult.size != remainingSize) {
					break;
				}

				continue;
			}

			const auto readBufferError = PrepareReadBuffer();
			if (readBufferError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return std::unexpected(readBufferError);
			}

			if (_buffer.size == 0) {
				break;
			}
		}

		return totalReadSize;
	}

	auto FileStream::Read(pointer a_buffer, size_type a_count) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsReadable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		if (a_count == 0) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		const auto readSize = TryRead(a_buffer, a_count);
		if (!readSize.has_value()) [[unlikely]] {
			return readSize.error();
		}

		if (readSize.value() == 0) [[unlikely]] {
			return REX::CreateSystemError(END_OF_FILE_ERROR_CODE);
		}

		if (readSize.value() != a_count) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::io_error);
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::ReadText() noexcept -> std::expected<std::string, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		auto result = std::string();

		while (true) {
			const auto oldSize = result.size();
			const auto additionalSize = _buffer.options.readChunkSize;

			try {
				REX::ResizeForOverwrite(result, oldSize + additionalSize);
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}

			const auto readSize = TryRead(reinterpret_cast<pointer>(result.data()) + oldSize, additionalSize);
			if (!readSize.has_value()) [[unlikely]] {
				return std::unexpected(readSize.error());
			}

			result.resize(oldSize + readSize.value());

			if (readSize.value() != additionalSize) {
				break;
			}
		}

		return result;
	}

	auto FileStream::ReadBytes() noexcept -> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		auto result = std::vector<std::byte>();

		while (true) {
			const auto oldSize = result.size();
			const auto additionalSize = _buffer.options.readChunkSize;

			try {
				REX::ResizeForOverwrite(result, oldSize + additionalSize);
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}

			const auto readSize = TryRead(result.data() + oldSize, additionalSize);
			if (!readSize.has_value()) [[unlikely]] {
				return std::unexpected(readSize.error());
			}

			result.resize(oldSize + readSize.value());

			if (readSize.value() != additionalSize) {
				break;
			}
		}

		return result;
	}

	auto FileStream::ReadLines() noexcept -> std::expected<std::vector<std::string>, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		auto result = std::vector<std::string>();

		while (true) {
			auto readLine = ReadLine();
			if (!readLine.has_value()) [[unlikely]] {
				if (readLine.error() != END_OF_FILE_ERROR_CODE) [[unlikely]] {
					return std::unexpected(readLine.error());
				}

				break;
			}

			try {
				result.push_back(std::move(readLine).value());
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}
		}

		return result;
	}

	auto FileStream::ReadLine() noexcept -> std::expected<std::string, REX::SystemError>
	{
		if (!IsOpen()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor));
		}

		if (!IsReadable()) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted));
		}

		auto result = std::string();

		while (true) {
			const auto readBufferError = PrepareReadBuffer();
			if (readBufferError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return std::unexpected(readBufferError);
			}

			if (_buffer.size == 0) {
				if (result.empty()) [[unlikely]] {
					return std::unexpected(REX::CreateSystemError(END_OF_FILE_ERROR_CODE));
				}

				break;
			}

			const auto remainingSize = _buffer.size - _buffer.position;

			const auto* bufferBegin = _buffer.data.get() + _buffer.position;
			const auto* bufferEnd = bufferBegin + remainingSize;
			const auto* newline = std::find(bufferBegin, bufferEnd, static_cast<std::byte>(REX::NEWLINE_CHAR<char>));

			const auto readSize = static_cast<size_type>(newline - bufferBegin);
			if (readSize != 0) {
				try {
					result.append(reinterpret_cast<const char*>(bufferBegin), readSize);
				}
				catch (const std::bad_alloc& error) {
					std::ignore = error;
					return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
				}

				_buffer.position += readSize;
			}

			if (newline != bufferEnd) {
				_buffer.position++;

				if (!result.empty() && result.back() == REX::CARRIAGE_RETURN_CHAR<char>) {
					result.pop_back();
				}

				break;
			}

			_buffer.position = _buffer.size;
		}

		return result;
	}

	auto FileStream::Write(const_pointer a_buffer, size_type a_count) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsWritable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		if (a_count == 0) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		if (!a_buffer) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::invalid_argument);
		}

		auto totalWriteSize = static_cast<size_type>(0);
		while (totalWriteSize < a_count) {
			if (_buffer.mode == BufferMode::Read) {
				const auto synchronizeError = SynchronizeBuffer();
				if (synchronizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return synchronizeError;
				}
			}

			const auto remainingSize = a_count - totalWriteSize;
			if (remainingSize >= _buffer.options.capacity) {
				if (_buffer.mode == BufferMode::Write) {
					const auto flushError = FlushBuffer();
					if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
						return flushError;
					}
				}

				const auto writeResult = Impl::TryWriteHandle(_handle, a_buffer + totalWriteSize, remainingSize);

				totalWriteSize += writeResult.size;
				_buffer.startPosition += writeResult.size;

				if (writeResult.error.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return writeResult.error;
				}

				continue;
			}

			const auto writeBufferError = PrepareWriteBuffer();
			if (writeBufferError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return writeBufferError;
			}

			const auto availableSize = _buffer.options.capacity - _buffer.size;
			const auto currentWriteSize = std::min(remainingSize, availableSize);
			std::copy_n(a_buffer + totalWriteSize, currentWriteSize, _buffer.data.get() + _buffer.size);

			_buffer.size += currentWriteSize;
			totalWriteSize += currentWriteSize;

			if (_buffer.size == _buffer.options.capacity) {
				const auto flushError = FlushBuffer();
				if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return flushError;
				}
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::WriteText(std::string_view a_text) noexcept -> REX::SystemError
	{
		return Write(reinterpret_cast<const_pointer>(a_text.data()), a_text.size());
	}

	auto FileStream::WriteBytes(std::span<const std::byte> a_bytes) noexcept -> REX::SystemError
	{
		return Write(reinterpret_cast<const_pointer>(a_bytes.data()), a_bytes.size());
	}

	auto FileStream::WriteBytes(std::span<const std::uint8_t> a_bytes) noexcept -> REX::SystemError
	{
		return Write(reinterpret_cast<const_pointer>(a_bytes.data()), a_bytes.size());
	}

	auto FileStream::WriteLines(std::span<const std::string> a_lines) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsWritable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		for (const auto& line : a_lines) {
			const auto writeError = WriteLine(line);
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return writeError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::WriteLines(std::span<const std::string_view> a_lines) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsWritable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		for (const auto& line : a_lines) {
			const auto writeError = WriteLine(line);
			if (writeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return writeError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::WriteLine(std::string_view a_line) noexcept -> REX::SystemError
	{
		if (!IsOpen()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::bad_file_descriptor);
		}

		if (!IsWritable()) [[unlikely]] {
			return REX::CreateSystemError(REX::PosixErrorCode::operation_not_permitted);
		}

		const auto writeTextError = WriteText(a_line);
		if (writeTextError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeTextError;
		}

		const auto writeNewLineError = Write(REX::NEWLINE_CHAR<char>);
		if (writeNewLineError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeNewLineError;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	void FileStream::swap(FileStream& a_other) noexcept
	{
		std::swap(_handle, a_other._handle);
		std::swap(_path, a_other._path);
		std::swap(_mode, a_other._mode);
		std::swap(_access, a_other._access);
		std::swap(_share, a_other._share);
		std::swap(_options, a_other._options);
		std::swap(_buffer, a_other._buffer);
	}

	auto FileStream::GetBufferedPosition() const noexcept -> FileStream::size_type
	{
		switch (_buffer.mode) {
			case BufferMode::None: {
				return _buffer.startPosition;
			}
			case BufferMode::Read: {
				return _buffer.startPosition + _buffer.position;
			}
			case BufferMode::Write: {
				return _buffer.startPosition + _buffer.size;
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto FileStream::AllocateBuffer() noexcept -> REX::SystemError
	{
		auto& bufferData = _buffer.data;
		if (bufferData) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		try {
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			bufferData = std::make_unique_for_overwrite<std::byte[]>(_buffer.options.capacity);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory);
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::PrepareReadBuffer() noexcept -> REX::SystemError
	{
		switch (_buffer.mode) {
			case BufferMode::None: {
				break;
			}
			case BufferMode::Read: {
				if (_buffer.position < _buffer.size) {
					return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
				}

				ResetBuffer();
				break;
			}
			case BufferMode::Write: {
				const auto flushError = FlushBuffer();
				if (flushError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return flushError;
				}

				break;
			}
			default: {
				std::unreachable();
			}
		}

		const auto allocateError = AllocateBuffer();
		if (allocateError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return allocateError;
		}

		const auto readResult = Impl::TryReadHandle(_handle, _buffer.data.get(), _buffer.options.capacity);

		_buffer.size = readResult.size;
		_buffer.position = 0;
		_buffer.mode = readResult.size == 0 ? BufferMode::None : BufferMode::Read;

		if (readResult.error.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return readResult.error;
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::PrepareWriteBuffer() noexcept -> REX::SystemError
	{
		switch (_buffer.mode) {
			case BufferMode::None: {
				break;
			}
			case BufferMode::Read: {
				const auto synchronizeError = SynchronizeBuffer();
				if (synchronizeError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
					return synchronizeError;
				}

				break;
			}
			case BufferMode::Write: {
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}
			default: {
				std::unreachable();
			}
		}

		const auto allocateError = AllocateBuffer();
		if (allocateError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return allocateError;
		}

		_buffer.size = 0;
		_buffer.position = 0;
		_buffer.mode = BufferMode::Write;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::FlushBuffer() noexcept -> REX::SystemError
	{
		if (_buffer.mode != BufferMode::Write) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		if (_buffer.size == 0) {
			ResetBuffer();
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		const auto pendingSize = _buffer.size;
		const auto writeResult = Impl::TryWriteHandle(_handle, _buffer.data.get(), pendingSize);

		_buffer.startPosition += writeResult.size;

		if (writeResult.size != 0) {
			const auto remainingSize = pendingSize - writeResult.size;
			if (remainingSize != 0) {
				std::copy_n(_buffer.data.get() + writeResult.size, remainingSize, _buffer.data.get());
			}

			_buffer.size = remainingSize;
		}

		_buffer.position = 0;

		if (writeResult.error.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
			return writeResult.error;
		}

		_buffer.mode = BufferMode::None;

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto FileStream::SynchronizeBuffer() noexcept -> REX::SystemError
	{
		switch (_buffer.mode) {
			case BufferMode::None: {
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}
			case BufferMode::Write: {
				return FlushBuffer();
			}
			case BufferMode::Read: {
				const auto currentPosition = GetBufferedPosition();
				if (currentPosition != _buffer.startPosition + _buffer.size) {
					const auto newPosition = Impl::SeekHandle(
						_handle,
						static_cast<FileStream::difference_type>(currentPosition),
						SeekOrigin::Begin);
					if (!newPosition.has_value()) [[unlikely]] {
						return newPosition.error();
					}
				}

				ResetBuffer();
				return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
			}
			default: {
				std::unreachable();
			}
		}
	}

	void FileStream::ResetBuffer() noexcept
	{
		switch (_buffer.mode) {
			case BufferMode::None: {
				break;
			}
			case BufferMode::Read: {
				_buffer.startPosition += _buffer.position;
				break;
			}
			case BufferMode::Write: {
				_buffer.startPosition += _buffer.size;
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_buffer.size = 0;
		_buffer.position = 0;
		_buffer.mode = BufferMode::None;
	}

	void FileStream::ReleaseBuffer() noexcept
	{
		_buffer.data.reset();
		_buffer.size = 0;
		_buffer.position = 0;
		_buffer.startPosition = 0;
		_buffer.mode = BufferMode::None;
	}
}
