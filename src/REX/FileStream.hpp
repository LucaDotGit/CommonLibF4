#pragma once

#include "REX/ByteUnits.hpp"
#include "REX/Concepts.hpp"
#include "REX/Enum.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"
#include "REX/W32/CORE.hpp"

namespace REX
{
	enum class SeekOrigin : std::int32_t;

	enum class FileMode : std::int32_t
	{
		CreateNew = 1,
		Create,
		Open,
		OpenOrCreate,
		Truncate,
		Append,

		_Min = CreateNew,
		_Max = Append,

		_Count = _Max
	};

	enum class FileAccess : std::int32_t
	{
		Read = 1,
		Write,
		ReadWrite,

		_Min = Read,
		_Max = ReadWrite,

		_Count = _Max
	};

	enum class FileShare : std::int32_t
	{
		None = 0,
		Read,
		Write,
		ReadWrite,
		Delete,
		Inheritable,

		_Min = None,
		_Max = Inheritable,

		_Count = _Max + 1
	};

	enum class FileOptions : std::uint32_t
	{
		None = 0,
		DeleteOnClose = 1 << 0,
		SequentialScan = 1 << 1,
		RandomAccess = 1 << 2,
		WriteThrough = 1 << 3,

		_All = SequentialScan | RandomAccess | DeleteOnClose | WriteThrough
	};

	class FileBufferOptions final
	{
	public:
		using size_type = std::size_t;

		size_type capacity;
		size_type readChunkSize;
	};

	inline constexpr auto LARGE_FILE_BUFFER_OPTIONS =
		FileBufferOptions{.capacity = REX::Kibibyte(256).count(), .readChunkSize = REX::Kibibyte(16).count()};

	inline constexpr auto DEFAULT_FILE_BUFFER_OPTIONS =
		FileBufferOptions{.capacity = REX::Kibibyte(64).count(), .readChunkSize = REX::Kibibyte(4).count()};

	inline constexpr auto SMALL_FILE_BUFFER_OPTIONS =
		FileBufferOptions{.capacity = REX::Kibibyte(4).count(), .readChunkSize = REX::Kibibyte(1).count()};

	class FileStream final
	{
	public:
		using value_type = std::byte;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		inline static constexpr auto END_OF_FILE_ERROR_CODE = REX::PosixErrorCode::result_out_of_range;

	private:
		FileStream(
			REX::W32::HANDLE a_handle,
			std::filesystem::path a_path,
			FileMode a_mode,
			FileAccess a_access,
			FileShare a_share,
			FileOptions a_options,
			FileBufferOptions a_bufferOptions) noexcept;

	public:
		FileStream() noexcept;
		~FileStream() noexcept;

		FileStream(const FileStream&) = delete;
		FileStream(FileStream&& a_rhs) noexcept;

		auto operator=(const FileStream&) -> FileStream& = delete;
		auto operator=(FileStream&& a_rhs) noexcept -> FileStream&;

		[[nodiscard]]
		auto IsOpen() const noexcept -> bool;
		[[nodiscard]]
		auto IsReadable() const noexcept -> bool;
		[[nodiscard]]
		auto IsWritable() const noexcept -> bool;
		[[nodiscard]]
		auto IsSeekable() const noexcept -> bool;

		[[nodiscard]]
		auto GetPath() const noexcept -> const auto&
		{
			return _path;
		}

		[[nodiscard]]
		auto GetMode() const noexcept
		{
			return _mode.get();
		}

		[[nodiscard]]
		auto GetAccess() const noexcept
		{
			return _access.get();
		}

		[[nodiscard]]
		auto GetShare() const noexcept
		{
			return _share.get();
		}

		[[nodiscard]]
		auto GetOptions() const noexcept
		{
			return _options.get();
		}

		[[nodiscard]]
		static auto Open(std::filesystem::path a_path, FileMode a_mode, FileAccess a_access) noexcept
			-> std::expected<FileStream, REX::SystemError>;

		[[nodiscard]]
		static auto Open(std::filesystem::path a_path, FileMode a_mode, FileAccess a_access, FileShare a_share) noexcept
			-> std::expected<FileStream, REX::SystemError>;

		[[nodiscard]]
		static auto Open(
			std::filesystem::path a_path,
			FileMode a_mode,
			FileAccess a_access,
			FileShare a_share,
			FileOptions a_options) noexcept -> std::expected<FileStream, REX::SystemError>;

		[[nodiscard]]
		static auto Open(
			std::filesystem::path a_path,
			FileMode a_mode,
			FileAccess a_access,
			FileShare a_share,
			FileOptions a_options,
			FileBufferOptions a_bufferOptions) noexcept -> std::expected<FileStream, REX::SystemError>;

		auto Flush() noexcept -> REX::SystemError;

		auto Close() noexcept -> REX::SystemError;

		[[nodiscard]]
		auto GetSize() const noexcept -> std::expected<size_type, REX::SystemError>;

		auto SetSize(size_type a_size) noexcept -> REX::SystemError;

		[[nodiscard]]
		auto GetPosition() const noexcept -> std::expected<size_type, REX::SystemError>;

		auto SetPosition(size_type a_position) noexcept -> REX::SystemError;

		[[nodiscard]]
		auto Seek(difference_type a_offset, SeekOrigin a_seekOrigin) noexcept
			-> std::expected<size_type, REX::SystemError>;

		[[nodiscard]]
		auto Peek() noexcept -> std::expected<std::byte, REX::SystemError>;

		[[nodiscard]]
		auto TryRead(pointer a_buffer, size_type a_count) noexcept -> std::expected<size_type, REX::SystemError>;

		[[nodiscard]]
		auto Read(pointer a_buffer, size_type a_count) noexcept -> REX::SystemError;

		[[nodiscard]]
		auto ReadText() noexcept -> std::expected<std::string, REX::SystemError>;

		[[nodiscard]]
		auto ReadBytes() noexcept -> std::expected<std::vector<std::byte>, REX::SystemError>;

		[[nodiscard]]
		auto ReadLines() noexcept -> std::expected<std::vector<std::string>, REX::SystemError>;

		[[nodiscard]]
		auto ReadLine() noexcept -> std::expected<std::string, REX::SystemError>;

		auto Write(const_pointer a_buffer, size_type a_count) noexcept -> REX::SystemError;

		auto WriteText(std::string_view a_text) noexcept -> REX::SystemError;

		auto WriteBytes(std::span<const std::byte> a_bytes) noexcept -> REX::SystemError;

		auto WriteBytes(std::span<const std::uint8_t> a_bytes) noexcept -> REX::SystemError;

		auto WriteLines(std::span<const std::string> a_lines) noexcept -> REX::SystemError;

		auto WriteLines(std::span<const std::string_view> a_lines) noexcept -> REX::SystemError;

		auto WriteLine(std::string_view a_line) noexcept -> REX::SystemError;

		void swap(FileStream& a_other) noexcept;

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T* a_buffer, size_type a_count) noexcept -> REX::SystemError
		{
			return Read(reinterpret_cast<pointer>(a_buffer), a_count * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		[[nodiscard]]
		auto Read(std::span<T, N> a_buffer) noexcept -> REX::SystemError
		{
			return Read(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T& a_outValue) noexcept -> REX::SystemError
		{
			return Read(reinterpret_cast<pointer>(std::addressof(a_outValue)), sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read() noexcept -> std::expected<T, REX::SystemError>
		{
			auto result = T();

			const auto readError = Read(result);
			if (readError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return std::unexpected(readError);
			}

			return result;
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto TryRead(T* a_buffer, size_type a_count) noexcept -> std::expected<size_type, REX::SystemError>
		{
			return TryRead(reinterpret_cast<pointer>(a_buffer), a_count * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		[[nodiscard]]
		auto TryRead(std::span<T, N> a_buffer) noexcept -> std::expected<size_type, REX::SystemError>
		{
			return TryRead(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		template <REX::trivially_readable T>
		auto Write(const T* a_data, size_type a_count) noexcept -> REX::SystemError
		{
			return Write(reinterpret_cast<const_pointer>(a_data), a_count * sizeof(T));
		}

		template <REX::trivially_readable T, std::size_t N>
		auto Write(std::span<const T, N> a_span) noexcept -> REX::SystemError
		{
			return Write(reinterpret_cast<const_pointer>(a_span.data()), a_span.size_bytes());
		}

		template <REX::trivially_readable T>
		auto Write(const T& a_value) noexcept -> REX::SystemError
		{
			return Write(reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}

	private:
		enum class BufferMode : std::int32_t
		{
			None = 0,
			Read,
			Write,

			_Min = None,
			_Max = Write,

			_Count = _Max
		};

		[[nodiscard]]
		auto GetBufferedPosition() const noexcept -> size_type;

		[[nodiscard]]
		auto AllocateBuffer() noexcept -> REX::SystemError;

		[[nodiscard]]
		auto PrepareReadBuffer() noexcept -> REX::SystemError;
		[[nodiscard]]
		auto PrepareWriteBuffer() noexcept -> REX::SystemError;

		[[nodiscard]]
		auto FlushBuffer() noexcept -> REX::SystemError;
		[[nodiscard]]
		auto SynchronizeBuffer() noexcept -> REX::SystemError;

		void ResetBuffer() noexcept;
		void ReleaseBuffer() noexcept;

		REX::W32::HANDLE _handle;
		std::filesystem::path _path;
		REX::Enum<FileMode> _mode;
		REX::Enum<FileAccess> _access;
		REX::Enum<FileShare> _share;
		REX::EnumSet<FileOptions> _options;

		struct
		{
		public:
			// NOLINTNEXTLINE(modernize-avoid-c-arrays)
			std::unique_ptr<std::byte[]> data;
			FileBufferOptions options;
			size_type size;
			size_type position;
			size_type startPosition;
			BufferMode mode;
		} _buffer;
	};
}
