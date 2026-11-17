#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSStorageDefs_ErrorCode.hpp"
#include "RE/B/BSStorageDefs_StreamBuffer.hpp"
#include "msvc/memory.hpp"

namespace RE::BSStorageDefs
{
	enum class SeekMode : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) BSStorage : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSStorage;
		inline static constexpr const auto& VTABLE = VTABLE::BSStorage;

		using value_type = std::byte;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		virtual ~BSStorage() = default; // 0x00

		// add
		virtual auto GetSize() const -> size_type = 0;	   // 0x01
		virtual auto GetPosition() const -> size_type = 0; // 0x02
		virtual auto Seek(size_type a_offset, BSStorageDefs::SeekMode a_seekMode) const
			-> BSStorageDefs::ErrorCode = 0;														  // 0x03
		virtual auto Read(size_type a_size, pointer a_buffer) const -> BSStorageDefs::ErrorCode = 0;  // 0x04
		virtual auto Write(size_type a_size, const_pointer a_buffer) -> BSStorageDefs::ErrorCode = 0; // 0x05

		[[nodiscard]]
		auto Read(pointer a_data, size_type a_size) const -> BSStorageDefs::ErrorCode
		{
			const auto readError = Read(a_size, a_data);
			if (readError != BSStorageDefs::ErrorCode::None) [[unlikely]] {
				return readError;
			}

			return BSStorageDefs::ErrorCode::None;
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T* a_buffer, size_type a_size) const -> BSStorageDefs::ErrorCode
		{
			return Read(reinterpret_cast<pointer>(a_buffer), a_size * sizeof(T));
		}

		template <REX::trivially_writable T, std::size_t N>
		[[nodiscard]]
		auto Read(std::span<T, N> a_buffer) const -> BSStorageDefs::ErrorCode
		{
			return Read(reinterpret_cast<pointer>(a_buffer.data()), a_buffer.size_bytes());
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read(T& a_outValue) const -> BSStorageDefs::ErrorCode
		{
			return Read(reinterpret_cast<pointer>(std::addressof(a_outValue)), sizeof(T));
		}

		template <REX::trivially_writable T>
		[[nodiscard]]
		auto Read() const -> std::expected<T, BSStorageDefs::ErrorCode>
		{
			auto result = T();

			const auto readError = Read(result);
			if (readError != BSStorageDefs::ErrorCode::None) [[unlikely]] {
				return std::unexpected(readError);
			}

			return result;
		}

		auto Write(const_pointer a_data, size_type a_size) -> BSStorageDefs::ErrorCode
		{
			return Write(a_size, a_data);
		}

		template <REX::trivially_readable T>
		auto Write(const T* a_data, size_type a_size) -> BSStorageDefs::ErrorCode
		{
			return Write(reinterpret_cast<const_pointer>(a_data), a_size * sizeof(T));
		}

		template <REX::trivially_readable T, std::size_t N>
		auto Write(std::span<const T, N> a_span) -> BSStorageDefs::ErrorCode
		{
			return Write(reinterpret_cast<const_pointer>(a_span.data()), a_span.size_bytes());
		}

		template <REX::trivially_readable T>
		auto Write(const T& a_value) -> BSStorageDefs::ErrorCode
		{
			return Write(reinterpret_cast<const_pointer>(std::addressof(a_value)), sizeof(T));
		}

		// members
		msvc::unique_ptr<BSStorageDefs::StreamBuffer> streamBuffer; // 0x10
		bool usingStreambuffer;										// 0x18
	};

	static_assert(sizeof(BSStorage) == 0x20);
}
