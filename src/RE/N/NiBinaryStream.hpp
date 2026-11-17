#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) NiBinaryStream
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiBinaryStream;
		inline static constexpr const auto& VTABLE = VTABLE::NiBinaryStream;

		class BufferInfo
		{
		public:
			// members
			std::byte* buffer{nullptr};				// 0x00
			std::size_t fileSize{0};				// 0x08
			std::size_t bufferAllocSize{0};			// 0x10
			std::size_t bufferReadSize{0};			// 0x18
			std::size_t position{0};				// 0x20
			std::size_t absoluteCurrentPosition{0}; // 0x28
		};

		static_assert(sizeof(BufferInfo) == 0x30);

		NiBinaryStream() = default;

		NiBinaryStream(const NiBinaryStream&) = delete;
		NiBinaryStream(NiBinaryStream&&) noexcept = default;

		auto operator=(const NiBinaryStream&) -> NiBinaryStream& = delete;
		auto operator=(NiBinaryStream&&) noexcept -> NiBinaryStream& = default;

		virtual ~NiBinaryStream() = default; // 0x00

		// add
		virtual explicit operator bool() const = 0;		  // 0x01
		virtual void Seek(std::ptrdiff_t a_numBytes) = 0; // 0x02

		virtual auto GetPosition() const -> std::size_t // 0x03
		{
			return absoluteCurrentPosition;
		}

		virtual void GetBufferInfo(BufferInfo& a_info);										   // 0x04
		virtual auto DoRead(void* a_buffer, std::size_t a_numBytes) -> std::size_t = 0;		   // 0x05
		virtual auto DoWrite(const void* a_buffer, std::size_t a_numBytes) -> std::size_t = 0; // 0x06

		GAME_HEAP_REDEFINE_NEW(NiBinaryStream);

		[[nodiscard]]
		auto BinaryRead(std::byte* a_buffer, std::size_t a_size) -> std::size_t;
		[[nodiscard]]
		auto BinaryWrite(const std::byte* a_buffer, std::size_t a_size) -> std::size_t;

		// members
		std::size_t absoluteCurrentPosition{0}; // 0x08
	};

	static_assert(sizeof(NiBinaryStream) == 0x10);
}
