#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource::Archive2
{
	class __declspec(novtable) ReaderStream : public Stream // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__Archive2__ReaderStream;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__Archive2__ReaderStream;

		enum class ReaderFlags : std::uint32_t
		{
			None = 0,
			CompressedStandard = 1 << 8,
			CompressedPlatform = 1 << 9,
			CtxInFullRead = 1 << 10,
			CtxInScrapHeap = 1 << 11,
			CtxMultiplexed = 1 << 12,
			HasEmbeddedName = 1 << 13
		};

		class PlatformContext; // To-Do

		class StandardContext
		{
		public:
			// members
			std::array<std::byte, 0x58> zStream;	// 0x00 - To-Do: `z_stream_s`
			std::array<std::byte*, 2> inputBuffers; // 0x58
			std::byte* outputBuffer;				// 0x68
			std::byte* currentOut;					// 0x70
			BSEventFlag* eventFlag;					// 0x78
			std::array<std::uint32_t, 2> tags;		// 0x80
			std::array<std::uint32_t, 2> tagVals;	// 0x88
			std::uint32_t inputSize;				// 0x90
			std::uint32_t outputSize;				// 0x94
			std::uint32_t outputAvail;				// 0x98
			std::uint32_t remainIn;					// 0x9C
			std::uint32_t remainFetch;				// 0xA0
			std::uint32_t whichFetch;				// 0xA4
			std::uint32_t whichWait;				// 0xA8
			std::uint32_t offsetInDecompressed;		// 0xAC
		};

		static_assert(sizeof(StandardContext) == 0xB0);

		ReaderStream();

		ReaderStream(const ReaderStream&) = delete;
		ReaderStream(ReaderStream&&) noexcept = default;

		auto operator=(const ReaderStream&) -> ReaderStream& = delete;
		auto operator=(ReaderStream&&) noexcept -> ReaderStream& = default;

		~ReaderStream() override = default; // 0x00

		// override (Stream)
		auto DoOpen() -> ErrorCode override;																  // 0x01
		void DoClose() override;																			  // 0x02
		auto DoGetKey() const -> std::size_t override;														  // 0x03
		void DoClone(BSTSmartPointer<Stream>& a_result) const override;										  // 0x05
		auto DoRead(void* a_buffer, std::size_t a_numBytes, std::size_t& a_read) const -> ErrorCode override; // 0x06
		auto DoWrite(const void* a_buffer, std::size_t a_numBytes, std::size_t& a_write) const
			-> ErrorCode override; // 0x08
		auto DoSeek(std::ptrdiff_t a_offset, SeekMode a_whence, std::size_t& a_position) const
			-> ErrorCode override;																// 0x09
		auto DoPrefetchAll(std::uint32_t a_priority) const -> ErrorCode override;				// 0x0E
		auto DoGetName(BSFixedString& a_result) const -> bool override;							// 0x0F
		auto DoCreateAsync(BSTSmartPointer<AsyncStream>& a_result) const -> ErrorCode override; // 0x10
		auto DoGetIsFromArchive() const -> bool override; // 0x13 - { return true; }

		// members
		BSTSmartPointer<Stream> source; // 0x10

		union
		{
		public:
			StandardContext* standardContext{nullptr};
			PlatformContext* platformContext;
		}; // 0x18

		std::size_t startOffset;							  // 0x02
		BSFixedString name;									  // 0x28
		std::uint32_t currentRelativeOffset;				  // 0x30
		std::uint32_t compressedSize;						  // 0x34
		std::uint32_t uncompressedSize;						  // 0x38
		REX::EnumSet<ReaderFlags, std::uint32_t> readerFlags; // 0x3C
	};

	static_assert(sizeof(ReaderStream) == 0x40);
}
