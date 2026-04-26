#include "RE/B/BSResource_Stream.hpp"

#include "RE/B/BSResource_StreamFlags.hpp"

namespace RE::BSResource
{
	Stream::Stream()
	{
		REL::EmplaceVtable(this);
	}

	Stream::Stream(std::uint32_t a_totalSize, bool writable)
		: StreamBase(a_totalSize, writable)
	{
		REL::EmplaceVtable(this);
	}

	bool Stream::GetName(BSFixedString& a_dst) const
	{
		return DoGetName(a_dst);
	}

	ErrorCode Stream::Open(bool a_buffered, bool a_fullReadHint)
	{
		auto openFlags = REX::EnumSet(StreamFlags::kOpened);

		if (a_buffered) {
			openFlags.set(StreamFlags::kBuffered);
		}

		if (a_fullReadHint) {
			openFlags.set(StreamFlags::kBuffered, StreamFlags::kFullReadHint);
		}

		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = 0ui32;

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(expectedFlags, expectedFlags | openFlags.underlying(),
			std::memory_order_acq_rel, std::memory_order_relaxed));

		return DoOpen();
	}

	ErrorCode Stream::Seek(std::ptrdiff_t a_toSeek, SeekMode a_mode, std::size_t& a_sought) const
	{
		return DoSeek(a_toSeek, a_mode, a_sought);
	}

	ErrorCode Stream::Write(const void* a_buffer, std::size_t a_toWrite, std::size_t& a_written) const
	{
		if (flags.none_atomic(StreamFlags::kWritable)) {
			return ErrorCode::kUnsupported;
		}

		return DoWrite(a_buffer, a_toWrite, a_written);
	}

	ErrorCode Stream::CreateOp(BSTSmartPointer<ICacheDriveOp>& a_opOut, const char* name) const
	{
		return DoCreateOp(a_opOut, name);
	}

	ErrorCode Stream::CreateAsync(BSTSmartPointer<AsyncStream>& a_streamOut) const
	{
		return DoCreateAsync(a_streamOut);
	}

	ErrorCode Stream::PrefetchAll(std::uint32_t a_priority) const
	{
		if (flags.any_atomic(StreamFlags::kWritable)) {
			return ErrorCode::kUnsupported;
		}

		return DoPrefetchAll(a_priority);
	}

	ErrorCode Stream::PrefetchAt(std::size_t a_bytes, std::size_t a_offset, std::uint32_t a_priority) const
	{
		if (flags.any_atomic(StreamFlags::kWritable)) {
			return ErrorCode::kUnsupported;
		}

		return DoPrefetchAt(a_bytes, a_offset, a_priority);
	}

	std::uint32_t Stream::QFullReadHint() const
	{
		return flags.any_atomic(StreamFlags::kFullReadHint);
	}

	bool Stream::QTaggedPrioritizedReadSupported() const
	{
		return DoQTaggedPrioritizedReadSupported();
	}

	ErrorCode Stream::StartTaggedPrioritizedRead(void* a_buffer, std::size_t a_bytes, std::size_t a_offset, std::uint32_t a_priority, volatile std::uint32_t* a_completionTag, std::uint32_t& a_completionTagWaitValue, BSEventFlag* a_eventFlag) const
	{
		if (flags.any_atomic(StreamFlags::kWritable)) {
			return ErrorCode::kUnsupported;
		}

		return DoStartTaggedPrioritizedRead(
			a_buffer, a_bytes, a_offset, a_priority, a_completionTag, a_completionTagWaitValue, a_eventFlag);
	}

	ErrorCode Stream::WaitTags(volatile std::uint32_t* a_completionTag, std::uint32_t a_completionTagWaitValue, BSEventFlag* a_eventFlag) const
	{
		return DoWaitTags(a_completionTag, a_completionTagWaitValue, a_eventFlag);
	}

	std::uint32_t Stream::QBuffered() const
	{
		return flags.any_atomic(StreamFlags::kBuffered);
	}

	ErrorCode Stream::SetEndOfStream()
	{
		return DoSetEndOfStream();
	}
}
