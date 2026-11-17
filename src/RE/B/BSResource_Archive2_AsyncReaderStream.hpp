#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_AsyncStream.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource::Archive2
{
	class __declspec(novtable) AsyncReaderStream : public AsyncStream // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__Archive2__AsyncReaderStream;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__Archive2__AsyncReaderStream;

		AsyncReaderStream();

		AsyncReaderStream(const AsyncReaderStream&) = delete;
		AsyncReaderStream(AsyncReaderStream&&) noexcept = default;

		auto operator=(const AsyncReaderStream&) -> AsyncReaderStream& = delete;
		auto operator=(AsyncReaderStream&&) noexcept -> AsyncReaderStream& = default;

		~AsyncReaderStream() override = default; // 0x00

		// override (AsyncStream)
		auto DoOpen() -> ErrorCode override;								 // 0x01
		void DoClose() override;											 // 0x02
		void DoClone(BSTSmartPointer<AsyncStream>& a_result) const override; // 0x05
		auto DoStartRead(void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const
			-> ErrorCode override; // 0x06
		auto DoStartPacketAlignedBufferedRead(
			PacketAlignedBuffer* a_buffer,
			std::uint64_t a_bytes,
			std::uint64_t a_offset) const -> ErrorCode override; // 0x07
		auto DoStartWrite(const void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const
			-> ErrorCode override;									// 0x08 - { return ErrorCode::Unsupported; }
		auto DoTruncate(std::uint64_t) const -> ErrorCode override; // 0x09 - { return ErrorCode::Unsupported; }
		auto DoWait(std::uint64_t& a_transferred, bool a_block) -> ErrorCode override; // 0x0B

		// members
		BSTSmartPointer<AsyncStream> source;		 // 0x18
		std::uint64_t startOffset{0};				 // 0x20
		PacketAlignedBuffer* currentBuffer{nullptr}; // 0x28
		BSFixedString nameText;						 // 0x30
	};

	static_assert(sizeof(AsyncReaderStream) == 0x38);
}
