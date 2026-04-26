#pragma once

#include "RE/B/BSResource_StreamBase.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) AsyncStream
		: public StreamBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__AsyncStream };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__AsyncStream };

		class PacketAlignedBuffer
		{
		public:
			std::size_t resultOffset{ 0 };		// 00
			std::uint32_t bufferSize{ 0 };		// 08
			std::byte* packetBuffer{ nullptr }; // 10
			std::uint32_t dataRequestSize{ 0 }; // 18
			std::uint32_t dataSize{ 0 };		// 1C
			std::byte* dataStart{ nullptr };	// 20
		};
		static_assert(sizeof(PacketAlignedBuffer) == 0x28);

		AsyncStream();
		AsyncStream(std::uint32_t a_totalSize, bool writable);

		AsyncStream(const AsyncStream& a_rhs) = delete;
		AsyncStream(AsyncStream&&) noexcept = default;

		AsyncStream& operator=(const AsyncStream&) = delete;
		AsyncStream& operator=(AsyncStream&&) noexcept = default;

		~AsyncStream() override = default; // 00

		// add
		virtual void DoClone(BSTSmartPointer<AsyncStream>& a_result) const = 0;																	// 05
		virtual ErrorCode DoStartRead(void* a_buffer, std::size_t a_bytes, std::size_t a_offset) const = 0;										// 06
		virtual ErrorCode DoStartPacketAlignedBufferedRead(PacketAlignedBuffer* a_buffer, std::size_t a_bytes, std::size_t a_offset) const = 0; // 07
		virtual ErrorCode DoStartWrite(const void* a_buffer, std::size_t a_bytes, std::size_t a_offset) const = 0;								// 08
		virtual ErrorCode DoTruncate(std::size_t a_bytes) const = 0;																			// 09
		virtual ErrorCode DoPrefetchAt(std::size_t a_bytes, std::size_t a_position, std::uint32_t a_priority) const;							// 0A - { return ErrorCode::kUnsupported; }
		virtual ErrorCode DoWait(std::size_t& a_transferred, bool a_block) = 0;																	// 0B

		// members
		std::uint32_t minPacketSize{ 0 }; // 10
	};
	static_assert(sizeof(AsyncStream) == 0x18);
}
