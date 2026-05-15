#include "RE/B/BSResource_StreamBase.hpp"

#include "RE/B/BSResource_StreamFlags.hpp"

namespace RE::BSResource
{
	StreamBase::StreamBase(std::uint32_t a_totalSize, bool writable) noexcept
		: totalSize(a_totalSize),
		  flags(writable ? StreamFlags::kWritable : StreamFlags::kNone)
	{
	}

	StreamBase::StreamBase(StreamBase&& a_rhs) noexcept
		: totalSize(a_rhs.totalSize),
		  flags(a_rhs.flags.underlying() & ~std::to_underlying(StreamFlags::kRefCountMask))
	{
	}

	StreamBase& StreamBase::operator=(StreamBase&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		totalSize = a_rhs.totalSize;
		flags = a_rhs.flags.underlying() & ~std::to_underlying(StreamFlags::kRefCountMask);
		return *this;
	}

	std::size_t StreamBase::DoGetKey() const
	{
		return 0;
	}

	ErrorCode StreamBase::DoGetInfo([[maybe_unused]] Info& a_info)
	{
		return ErrorCode::kUnsupported;
	}

	bool StreamBase::IsWritable() const noexcept
	{
		return flags.any_atomic(StreamFlags::kWritable);
	}

	std::uint32_t StreamBase::IncRef() noexcept
	{
		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = 0ui32;

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(expectedFlags, expectedFlags + std::to_underlying(StreamFlags::kRefCountIncrement),
			std::memory_order_acq_rel, std::memory_order_relaxed));

		return (expectedFlags - std::to_underlying(StreamFlags::kRefCountIncrement)) & std::to_underlying(StreamFlags::kRefCountMask);
	}

	std::uint32_t StreamBase::DecRef() noexcept
	{
		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = 0ui32;

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(expectedFlags, expectedFlags - std::to_underlying(StreamFlags::kRefCountIncrement),
			std::memory_order_acq_rel, std::memory_order_relaxed));

		return (expectedFlags - std::to_underlying(StreamFlags::kRefCountIncrement)) & std::to_underlying(StreamFlags::kRefCountMask);
	}
}
