#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSStorageDefs_StreamBuffer.hpp"

#include "msvc/memory.hpp"

namespace RE::BSStorageDefs
{
	enum class ErrorCode : std::int32_t;
	enum class SeekMode : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) BSStorage
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSStorage };
		inline static constexpr auto VTABLE{ VTABLE::BSStorage };

		virtual ~BSStorage(); // 00

		// add
		virtual std::size_t GetSize() const = 0;																   // 01
		virtual std::size_t GetPosition() const = 0;															   // 02
		virtual BSStorageDefs::ErrorCode Seek(std::size_t a_offset, BSStorageDefs::SeekMode a_seekMode) const = 0; // 03
		virtual BSStorageDefs::ErrorCode Read(std::size_t a_numBytes, std::byte* a_bytes) const = 0;			   // 04
		virtual BSStorageDefs::ErrorCode Write(std::size_t a_numBytes, const std::byte* a_bytes) = 0;			   // 05

		template <REX::trivially_writable T>
		[[nodiscard]] BSStorageDefs::ErrorCode Read(T& a_value) const
		{
			return Read(sizeof(T), reinterpret_cast<std::byte*>(std::addressof(a_value)));
		}

		template <REX::trivially_writable T>
		[[nodiscard]] BSStorageDefs::ErrorCode Read(std::span<T> a_buffer) const
		{
			return Read(a_buffer.size_bytes(), reinterpret_cast<std::byte*>(a_buffer.data()));
		}

		template <REX::trivially_readable T>
		[[nodiscard]] BSStorageDefs::ErrorCode Write(const T& a_value)
		{
			return Write(sizeof(T), reinterpret_cast<const std::byte*>(std::addressof(a_value)));
		}

		template <REX::trivially_readable T>
		[[nodiscard]] BSStorageDefs::ErrorCode Write(std::span<const T> a_data)
		{
			return Write(a_data.size_bytes(), reinterpret_cast<const std::byte*>(a_data.data()));
		}

		// members
		msvc::unique_ptr<BSStorageDefs::StreamBuffer> buffer; // 10
		bool usingStreambuffer;								  // 18
	};
	static_assert(sizeof(BSStorage) == 0x20);
}
