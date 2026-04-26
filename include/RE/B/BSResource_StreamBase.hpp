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
		inline static constexpr auto RTTI{ RTTI::BSResource__StreamBase };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__StreamBase };

		StreamBase() = default;

		StreamBase(std::uint32_t a_totalSize, bool writable) noexcept;

		StreamBase(const StreamBase&) = delete;
		StreamBase(StreamBase&& a_rhs) noexcept;

		StreamBase& operator=(const StreamBase&) = delete;
		StreamBase& operator=(StreamBase&& a_rhs) noexcept;

		virtual ~StreamBase() = default; // 00

		// add
		virtual ErrorCode DoOpen() = 0;			   // 01
		virtual void DoClose() = 0;				   // 02
		virtual std::size_t DoGetKey() const;	   // 03
		virtual ErrorCode DoGetInfo(Info& a_info); // 04

		GAME_HEAP_REDEFINE_NEW(StreamBase);

		[[nodiscard]] bool IsWritable() const noexcept;

		std::uint32_t IncRef() noexcept;
		std::uint32_t DecRef() noexcept;

		// members
		std::uint32_t totalSize{ 0 };					// 08
		REX::EnumSet<StreamFlags, std::uint32_t> flags; // 0C
	};
	static_assert(sizeof(StreamBase) == 0x10);
}
