#pragma once

#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_SeekMode.hpp"
#include "RE/B/BSResource_StreamBase.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class AsyncStream;
	class ICacheDriveOp;

	class __declspec(novtable) Stream
		: public StreamBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__Stream };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__Stream };

		Stream();
		Stream(std::uint32_t a_totalSize, bool writable);

		Stream(const Stream& a_rhs) = delete;
		Stream(Stream&&) noexcept = default;

		Stream& operator=(const Stream&) = delete;
		Stream& operator=(Stream&&) noexcept = default;

		~Stream() override = default; // 00

		// add
		virtual void DoClone(BSTSmartPointer<Stream>& a_result) const = 0;																																														  // 05
		virtual ErrorCode DoRead(void* a_buffer, std::size_t a_numBytes, std::size_t& a_read) const = 0;																																						  // 06
		virtual ErrorCode DoReadAt(void* a_buffer, std::size_t a_numBytes, std::size_t a_position, std::size_t& a_read) const;																																	  // 07
		virtual ErrorCode DoWrite(const void* a_buffer, std::size_t a_numBytes, std::size_t& a_write) const = 0;																																				  // 08
		virtual ErrorCode DoSeek(std::ptrdiff_t a_offset, SeekMode a_seekMode, std::size_t& a_position) const = 0;																																				  // 09
		virtual ErrorCode DoSetEndOfStream();																																																					  // 0A
		virtual ErrorCode DoPrefetchAt(std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority) const;																																			  // 0B
		virtual ErrorCode DoStartTaggedPrioritizedRead(void* a_buffer, std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority, volatile std::uint32_t* a_completionTag, std::uint32_t& a_completionTagWaitValue, BSEventFlag* a_eventFlag) const; // 0C
		virtual ErrorCode DoWaitTags(volatile std::uint32_t* a_completionTag, std::uint32_t a_completionTagWaitValue, BSEventFlag* a_eventFlag) const;																											  // 0D
		virtual ErrorCode DoPrefetchAll(std::uint32_t a_priority) const;																																														  // 0E
		virtual bool DoGetName(BSFixedString& a_result) const;																																																	  // 0F
		virtual ErrorCode DoCreateAsync(BSTSmartPointer<AsyncStream>& a_result) const;																																											  // 10
		virtual bool DoQTaggedPrioritizedReadSupported() const;																																																	  // 11
		virtual ErrorCode DoCreateOp(BSTSmartPointer<ICacheDriveOp>& a_result, const char* a_unk02) const;																																						  // 12
		virtual bool DoGetIsFromArchive() const;																																																				  // 13

		bool GetName(BSFixedString& a_dst) const;
		ErrorCode Open(bool a_buffered, bool a_fullReadHint);
		ErrorCode Read(void* a_buffer, std::size_t a_toRead, std::size_t& a_read) const;
		ErrorCode Seek(std::ptrdiff_t a_toSeek, SeekMode a_mode, std::size_t& a_sought) const;
		ErrorCode Write(const void* a_buffer, std::size_t a_toWrite, std::size_t& a_written) const;
		ErrorCode ReadAt(void* a_buffer, std::size_t a_offset, std::size_t a_toRead, std::size_t& a_read) const;
		ErrorCode CreateOp(BSTSmartPointer<ICacheDriveOp>& a_opOut, const char* name) const;
		ErrorCode CreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const;
		ErrorCode PrefetchAll(std::uint32_t a_priority) const;
		ErrorCode PrefetchAt(std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority) const;
		std::uint32_t QFullReadHint() const;
		bool QTaggedPrioritizedReadSupported() const;
		ErrorCode StartTaggedPrioritizedRead(void* a_buffer, std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority, volatile std::uint32_t* a_completionTag, std::uint32_t& a_completionTagWaitValue, BSEventFlag* a_eventFlag) const;
		ErrorCode WaitTags(volatile std::uint32_t* a_completionTag, std::uint32_t a_completionTagWaitValue, BSEventFlag* a_eventFlag) const;
		std::uint32_t QBuffered() const;
		ErrorCode SetEndOfStream();
	};
	static_assert(sizeof(Stream) == 0x10);
}
