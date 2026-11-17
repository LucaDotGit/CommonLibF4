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

	class __declspec(novtable) Stream : public StreamBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__Stream;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__Stream;

		Stream();
		Stream(std::uint32_t a_totalSize, bool writable);

		Stream(const Stream& a_rhs) = delete;
		Stream(Stream&&) noexcept = default;

		auto operator=(const Stream&) -> Stream& = delete;
		auto operator=(Stream&&) noexcept -> Stream& = default;

		~Stream() override = default; // 0x00

		// add
		virtual void DoClone(BSTSmartPointer<Stream>& a_result) const = 0;										 // 0x05
		virtual auto DoRead(void* a_buffer, std::size_t a_numBytes, std::size_t& a_read) const -> ErrorCode = 0; // 0x06
		virtual auto DoReadAt(void* a_buffer, std::size_t a_numBytes, std::size_t a_position, std::size_t& a_read) const
			-> ErrorCode; // 0x07
		virtual auto DoWrite(const void* a_buffer, std::size_t a_numBytes, std::size_t& a_write) const
			-> ErrorCode = 0; // 0x08
		virtual auto DoSeek(std::ptrdiff_t a_offset, SeekMode a_seekMode, std::size_t& a_position) const
			-> ErrorCode = 0;						  // 0x09
		virtual auto DoSetEndOfStream() -> ErrorCode; // 0x0A
		virtual auto DoPrefetchAt(std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority) const
			-> ErrorCode; // 0x0B
		virtual auto DoStartTaggedPrioritizedRead(
			void* a_buffer,
			std::size_t a_numBytes,
			std::size_t a_offset,
			std::uint32_t a_priority,
			volatile std::uint32_t* a_completionTag,
			std::uint32_t& a_completionTagWaitValue,
			BSEventFlag* a_eventFlag) const -> ErrorCode; // 0x0C
		virtual auto DoWaitTags(
			volatile std::uint32_t* a_completionTag,
			std::uint32_t a_completionTagWaitValue,
			BSEventFlag* a_eventFlag) const -> ErrorCode;									   // 0x0D
		virtual auto DoPrefetchAll(std::uint32_t a_priority) const -> ErrorCode;			   // 0x0E
		virtual auto DoGetName(BSFixedString& a_result) const -> bool;						   // 0x0F
		virtual auto DoCreateAsync(BSTSmartPointer<AsyncStream>& a_result) const -> ErrorCode; // 0x10
		virtual auto DoQTaggedPrioritizedReadSupported() const -> bool;						   // 0x11
		virtual auto DoCreateOp(BSTSmartPointer<ICacheDriveOp>& a_result, const char* a_unk02) const
			-> ErrorCode;								 // 0x12
		virtual auto DoGetIsFromArchive() const -> bool; // 0x13

		auto GetName(BSFixedString& a_target) const -> bool;
		auto Open(bool a_buffered, bool a_fullReadHint) -> ErrorCode;
		auto Read(void* a_buffer, std::size_t a_toRead, std::size_t& a_read) const -> ErrorCode;
		auto Seek(std::ptrdiff_t a_toSeek, SeekMode a_mode, std::size_t& a_sought) const -> ErrorCode;
		auto Write(const void* a_buffer, std::size_t a_toWrite, std::size_t& a_written) const -> ErrorCode;
		auto ReadAt(void* a_buffer, std::size_t a_offset, std::size_t a_toRead, std::size_t& a_read) const -> ErrorCode;
		auto CreateOp(BSTSmartPointer<ICacheDriveOp>& a_opOut, const char* name) const -> ErrorCode;
		auto CreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const -> ErrorCode;
		auto PrefetchAll(std::uint32_t a_priority) const -> ErrorCode;
		auto PrefetchAt(std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority) const -> ErrorCode;
		auto QFullReadHint() const -> std::uint32_t;
		auto QTaggedPrioritizedReadSupported() const -> bool;
		auto StartTaggedPrioritizedRead(
			void* a_buffer,
			std::size_t a_numBytes,
			std::size_t a_offset,
			std::uint32_t a_priority,
			volatile std::uint32_t* a_completionTag,
			std::uint32_t& a_completionTagWaitValue,
			BSEventFlag* a_eventFlag) const -> ErrorCode;
		auto WaitTags(
			volatile std::uint32_t* a_completionTag,
			std::uint32_t a_completionTagWaitValue,
			BSEventFlag* a_eventFlag) const -> ErrorCode;
		auto QBuffered() const -> std::uint32_t;
		auto SetEndOfStream() -> ErrorCode;
	};

	static_assert(sizeof(Stream) == 0x10);
}
