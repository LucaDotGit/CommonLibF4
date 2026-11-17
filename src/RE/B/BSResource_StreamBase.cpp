#include "RE/B/BSResource_StreamBase.hpp"

#include "RE/B/BSResource_StreamFlags.hpp"

namespace RE::BSResource
{
	StreamBase::StreamBase(std::uint32_t a_totalSize, bool a_writable) noexcept :
		totalSize(a_totalSize),
		flags(a_writable ? StreamFlags::Writable : StreamFlags::None)
	{
	}

	StreamBase::StreamBase(StreamBase&& a_rhs) noexcept :
		totalSize(a_rhs.totalSize),
		flags(static_cast<StreamFlags>(a_rhs.flags.underlying() & ~std::to_underlying(StreamFlags::RefCountMask)))
	{
	}

	auto StreamBase::operator=(StreamBase&& a_rhs) noexcept -> StreamBase&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		totalSize = a_rhs.totalSize;
		flags = static_cast<StreamFlags>(a_rhs.flags.underlying() & ~std::to_underlying(StreamFlags::RefCountMask));
		return *this;
	}

	auto StreamBase::DoGetKey() const -> std::size_t
	{
		return 0;
	}

	auto StreamBase::DoGetInfo([[maybe_unused]] Info& a_info) -> ErrorCode
	{
		return ErrorCode::Unsupported;
	}

	auto StreamBase::IsWritable() const noexcept -> bool
	{
		return flags.any_atomic(StreamFlags::Writable);
	}

	auto StreamBase::IncRef() const noexcept -> std::uint32_t
	{
		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = static_cast<std::uint32_t>(0);

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(
			expectedFlags,
			expectedFlags + std::to_underlying(StreamFlags::RefCountIncrement),
			std::memory_order_acq_rel,
			std::memory_order_relaxed));

		return (expectedFlags - std::to_underlying(StreamFlags::RefCountIncrement)) &
			   std::to_underlying(StreamFlags::RefCountMask);
	}

	auto StreamBase::DecRef() const noexcept -> std::uint32_t
	{
		auto atomicFlags = flags.underlying_atomic_ref();
		auto expectedFlags = static_cast<std::uint32_t>(0);

		do {
			expectedFlags = atomicFlags.load(std::memory_order_acquire);
		}
		while (!atomicFlags.compare_exchange_weak(
			expectedFlags,
			expectedFlags - std::to_underlying(StreamFlags::RefCountIncrement),
			std::memory_order_acq_rel,
			std::memory_order_relaxed));

		return (expectedFlags - std::to_underlying(StreamFlags::RefCountIncrement)) &
			   std::to_underlying(StreamFlags::RefCountMask);
	}
}
