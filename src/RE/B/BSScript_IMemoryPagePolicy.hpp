#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class MemoryPage;

	class __declspec(novtable) IMemoryPagePolicy
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IMemoryPagePolicy;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IMemoryPagePolicy;

		enum class AllocationStatus : std::int32_t;
		enum class NewPageStrategy : std::int32_t;

		virtual ~IMemoryPagePolicy() = default; // 0x00

		// add
		virtual auto MaximumPageSize() const -> std::uint32_t = 0;	 // 0x01
		virtual auto MaximumStackDepth() const -> std::uint32_t = 0; // 0x02
		virtual auto AllocatePage(
			std::uint32_t a_sizeInBytes,
			NewPageStrategy a_strategy,
			BSTAutoPointer<MemoryPage>& a_newPage) -> AllocationStatus = 0;									 // 0x03
		virtual auto GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) -> AllocationStatus = 0; // 0x04
		virtual void DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) = 0;								 // 0x05

		GAME_HEAP_REDEFINE_NEW(IMemoryPagePolicy);
	};

	static_assert(sizeof(IMemoryPagePolicy) == 0x08);
}
