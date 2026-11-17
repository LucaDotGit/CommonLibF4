#pragma once

#include "RE/B/BSResource_ErrorCode.hpp"
#include "RE/B/BSResource_Info.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	enum class StreamFlags : std::uint32_t;

	class __declspec(novtable) StreamBase
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__StreamBase;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__StreamBase;

		StreamBase() = default;
		StreamBase(std::uint32_t a_totalSize, bool a_writable) noexcept;

		StreamBase(const StreamBase&) = delete;
		StreamBase(StreamBase&& a_rhs) noexcept;

		auto operator=(const StreamBase&) -> StreamBase& = delete;
		auto operator=(StreamBase&& a_rhs) noexcept -> StreamBase&;

		virtual ~StreamBase() = default; // 0x00

		// add
		virtual auto DoOpen() -> ErrorCode = 0;			   // 0x01
		virtual void DoClose() = 0;						   // 0x02
		virtual auto DoGetKey() const -> std::size_t;	   // 0x03
		virtual auto DoGetInfo(Info& a_info) -> ErrorCode; // 0x04

		GAME_HEAP_REDEFINE_NEW(StreamBase);

		[[nodiscard]]
		auto IsWritable() const noexcept -> bool;

		auto IncRef() const noexcept -> std::uint32_t;
		auto DecRef() const noexcept -> std::uint32_t;

		// members
		std::uint32_t totalSize{0};								// 0x08
		mutable REX::EnumSet<StreamFlags, std::uint32_t> flags; // 0x0C
	};

	static_assert(sizeof(StreamBase) == 0x10);
}
