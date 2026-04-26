#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_AsyncStream.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource::Archive2
{
	class __declspec(novtable) AsyncReaderStream
		: public AsyncStream // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__Archive2__AsyncReaderStream };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__AsyncReaderStream };

		AsyncReaderStream();

		AsyncReaderStream(const AsyncReaderStream&) = delete;
		AsyncReaderStream(AsyncReaderStream&&) noexcept = default;

		AsyncReaderStream& operator=(const AsyncReaderStream&) = delete;
		AsyncReaderStream& operator=(AsyncReaderStream&&) noexcept = default;

		~AsyncReaderStream() override = default; // 00

		// override (AsyncStream)
		ErrorCode DoOpen() override;																											 // 01
		void DoClose() override;																												 // 02
		void DoClone(BSTSmartPointer<AsyncStream>& a_result) const override;																	 // 05
		ErrorCode DoStartRead(void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const override;									 // 06
		ErrorCode DoStartPacketAlignedBufferedRead(PacketAlignedBuffer* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const override; // 07
		ErrorCode DoStartWrite(const void* a_buffer, std::uint64_t a_bytes, std::uint64_t a_offset) const override;								 // 08 - { return ErrorCode::kUnsupported; }
		ErrorCode DoTruncate(std::uint64_t) const override;																						 // 09 - { return ErrorCode::kUnsupported; }
		ErrorCode DoWait(std::uint64_t& a_transferred, bool a_block) override;																	 // 0B

		// members
		BSTSmartPointer<AsyncStream> source;		   // 18
		std::uint64_t startOffset{ 0 };				   // 20
		PacketAlignedBuffer* currentBuffer{ nullptr }; // 28
		BSFixedString nameText;						   // 30
	};
	static_assert(sizeof(AsyncReaderStream) == 0x38);
}
