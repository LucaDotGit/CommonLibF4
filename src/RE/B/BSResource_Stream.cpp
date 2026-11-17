#include "RE/B/BSResource_Stream.hpp"

#include "RE/B/BSResource_StreamFlags.hpp"

namespace RE::BSResource
{
	Stream::Stream()
	{
		REL::EmplaceVtable(this);
	}

	Stream::Stream(std::uint32_t a_totalSize, bool writable) :
		StreamBase(a_totalSize, writable)
	{
		REL::EmplaceVtable(this);
	}

	auto Stream::GetName(BSFixedString& a_target) const -> bool
	{
		return DoGetName(a_target);
	}

	auto Stream::Open(bool a_buffered, bool a_fullReadHint) -> ErrorCode
	{
		auto openFlags = REX::EnumSet(StreamFlags::Opened);

		if (a_buffered) {
			openFlags.set(StreamFlags::Buffered);
		}

		if (a_fullReadHint) {
			openFlags.set(StreamFlags::Buffered, StreamFlags::FullReadHint);
		}

		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = static_cast<std::uint32_t>(0);

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(
			expectedFlags,
			expectedFlags | openFlags.underlying(),
			std::memory_order_acq_rel,
			std::memory_order_relaxed));

		return DoOpen();
	}

	auto Stream::Seek(std::ptrdiff_t a_toSeek, SeekMode a_mode, std::size_t& a_sought) const -> ErrorCode
	{
		return DoSeek(a_toSeek, a_mode, a_sought);
	}

	auto Stream::Write(const void* a_buffer, std::size_t a_toWrite, std::size_t& a_written) const -> ErrorCode
	{
		if (flags.none_atomic(StreamFlags::Writable)) {
			return ErrorCode::Unsupported;
		}

		return DoWrite(a_buffer, a_toWrite, a_written);
	}

	auto Stream::CreateOp(BSTSmartPointer<ICacheDriveOp>& a_opOut, const char* name) const -> ErrorCode
	{
		return DoCreateOp(a_opOut, name);
	}

	auto Stream::CreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const -> ErrorCode
	{
		return DoCreateAsync(a_streamOut);
	}

	auto Stream::PrefetchAll(std::uint32_t a_priority) const -> ErrorCode
	{
		if (flags.any_atomic(StreamFlags::Writable)) {
			return ErrorCode::Unsupported;
		}

		return DoPrefetchAll(a_priority);
	}

	auto Stream::PrefetchAt(std::size_t a_numBytes, std::size_t a_offset, std::uint32_t a_priority) const -> ErrorCode
	{
		if (flags.any_atomic(StreamFlags::Writable)) {
			return ErrorCode::Unsupported;
		}

		return DoPrefetchAt(a_numBytes, a_offset, a_priority);
	}

	auto Stream::QFullReadHint() const -> std::uint32_t
	{
		return flags.any_atomic(StreamFlags::FullReadHint);
	}

	auto Stream::QTaggedPrioritizedReadSupported() const -> bool
	{
		return DoQTaggedPrioritizedReadSupported();
	}

	auto Stream::StartTaggedPrioritizedRead(
		void* a_buffer,
		std::size_t a_numBytes,
		std::size_t a_offset,
		std::uint32_t a_priority,
		volatile std::uint32_t* a_completionTag,
		std::uint32_t& a_completionTagWaitValue,
		BSEventFlag* a_eventFlag) const -> ErrorCode
	{
		if (flags.any_atomic(StreamFlags::Writable)) {
			return ErrorCode::Unsupported;
		}

		return DoStartTaggedPrioritizedRead(
			a_buffer,
			a_numBytes,
			a_offset,
			a_priority,
			a_completionTag,
			a_completionTagWaitValue,
			a_eventFlag);
	}

	auto Stream::WaitTags(
		volatile std::uint32_t* a_completionTag,
		std::uint32_t a_completionTagWaitValue,
		BSEventFlag* a_eventFlag) const -> ErrorCode
	{
		return DoWaitTags(a_completionTag, a_completionTagWaitValue, a_eventFlag);
	}

	auto Stream::QBuffered() const -> std::uint32_t
	{
		return flags.any_atomic(StreamFlags::Buffered);
	}

	auto Stream::SetEndOfStream() -> ErrorCode
	{
		return DoSetEndOfStream();
	}
}
