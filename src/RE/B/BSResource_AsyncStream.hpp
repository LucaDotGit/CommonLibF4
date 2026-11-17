#pragma once

#include "RE/B/BSResource_StreamBase.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) AsyncStream : public StreamBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__AsyncStream;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__AsyncStream;

		class PacketAlignedBuffer
		{
		public:
			std::size_t resultOffset{0};	  // 0x00
			std::uint32_t bufferSize{0};	  // 0x08
			std::byte* packetBuffer{nullptr}; // 0x10
			std::uint32_t dataRequestSize{0}; // 0x18
			std::uint32_t dataSize{0};		  // 0x1C
			std::byte* dataStart{nullptr};	  // 0x20
		};

		static_assert(sizeof(PacketAlignedBuffer) == 0x28);

		AsyncStream();
		AsyncStream(std::uint32_t a_totalSize, bool writable);

		AsyncStream(const AsyncStream& a_rhs) = delete;
		AsyncStream(AsyncStream&&) noexcept = default;

		auto operator=(const AsyncStream&) -> AsyncStream& = delete;
		auto operator=(AsyncStream&&) noexcept -> AsyncStream& = default;

		~AsyncStream() override = default; // 0x00

		// add
		virtual void DoClone(BSTSmartPointer<AsyncStream>& a_result) const = 0; // 0x05
		virtual auto DoStartRead(void* a_buffer, std::size_t a_bytes, std::size_t a_offset) const
			-> ErrorCode = 0; // 0x06
		virtual auto DoStartPacketAlignedBufferedRead(
			PacketAlignedBuffer* a_buffer,
			std::size_t a_bytes,
			std::size_t a_offset) const -> ErrorCode = 0; // 0x07
		virtual auto DoStartWrite(const void* a_buffer, std::size_t a_bytes, std::size_t a_offset) const
			-> ErrorCode = 0;												 // 0x08
		virtual auto DoTruncate(std::size_t a_bytes) const -> ErrorCode = 0; // 0x09
		virtual auto DoPrefetchAt(std::size_t a_bytes, std::size_t a_position, std::uint32_t a_priority) const
			-> ErrorCode; // 0x0A - { return ErrorCode::Unsupported; }
		virtual auto DoWait(std::size_t& a_transferred, bool a_block) -> ErrorCode = 0; // 0x0B

		// members
		std::uint32_t minPacketSize{0}; // 0x10
	};

	static_assert(sizeof(AsyncStream) == 0x18);
}
