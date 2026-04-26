#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource::Archive2
{
	class __declspec(novtable) ReaderStream
		: public Stream // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__Archive2__ReaderStream };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__ReaderStream };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kCompressedStandard = 1 << 8,
			kCompressedPlatform = 1 << 9,
			kCtxInFullRead = 1 << 10,
			kCtxInScrapHeap = 1 << 11,
			kCtxMultiplexed = 1 << 12,
			kHasEmbeddedName = 1 << 13
		};

		class PlatformContext; // TODO

		class StandardContext
		{
		public:
			// members
			std::array<std::byte, 0x58> zStream;	// 00 - TODO: `z_stream_s`
			std::array<std::byte*, 2> inputBuffers; // 58
			std::byte* outputBuffer;				// 68
			std::byte* currentOut;					// 70
			BSEventFlag* eventFlag;					// 78
			std::array<std::uint32_t, 2> tags;		// 80
			std::array<std::uint32_t, 2> tagVals;	// 88
			std::uint32_t inputSize;				// 90
			std::uint32_t outputSize;				// 94
			std::uint32_t outputAvail;				// 98
			std::uint32_t remainIn;					// 9C
			std::uint32_t remainFetch;				// A0
			std::uint32_t whichFetch;				// A4
			std::uint32_t whichWait;				// A8
			std::uint32_t offsetInDecompressed;		// AC
		};
		static_assert(sizeof(StandardContext) == 0xB0);

		ReaderStream();

		ReaderStream(const ReaderStream&) = delete;
		ReaderStream(ReaderStream&&) noexcept = default;

		ReaderStream& operator=(const ReaderStream&) = delete;
		ReaderStream& operator=(ReaderStream&&) noexcept = default;

		~ReaderStream() override = default; // 00

		// override (Stream)
		ErrorCode DoOpen() override;																		  // 01
		void DoClose() override;																			  // 02
		std::size_t DoGetKey() const override;																  // 03
		void DoClone(BSTSmartPointer<Stream>& a_result) const override;										  // 05
		ErrorCode DoRead(void* a_buffer, std::size_t a_numBytes, std::size_t& a_read) const override;		  // 06
		ErrorCode DoWrite(const void* a_buffer, std::size_t a_numBytes, std::size_t& a_write) const override; // 08
		ErrorCode DoSeek(std::ptrdiff_t a_offset, SeekMode a_whence, std::size_t& a_position) const override; // 09
		ErrorCode DoPrefetchAll(std::uint32_t a_priority) const override;									  // 0E
		bool DoGetName(BSFixedString& a_result) const override;												  // 0F
		ErrorCode DoCreateAsync(BSTSmartPointer<AsyncStream>& a_result) const override;						  // 10
		bool DoGetIsFromArchive() const override;															  // 13 - { return true; }

		// members
		BSTSmartPointer<Stream> source; // 10
		union
		{
			StandardContext* standardContext{ nullptr };
			PlatformContext* platformContext;
		}; // 18
		std::size_t startOffset;				  // 02
		BSFixedString name;						  // 28
		std::uint32_t currentRelativeOffset;	  // 30
		std::uint32_t compressedSize;			  // 34
		std::uint32_t uncompressedSize;			  // 38
		REX::EnumSet<Flags, std::uint32_t> flags; // 3C
	};
	static_assert(sizeof(ReaderStream) == 0x40);
}
