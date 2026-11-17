#pragma once

#include "RE/B/BSScript_IMemoryPagePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) SimpleAllocMemoryPagePolicy : public IMemoryPagePolicy // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__SimpleAllocMemoryPagePolicy;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__SimpleAllocMemoryPagePolicy;

		~SimpleAllocMemoryPagePolicy() override; // 0x00

		// override (IMemoryPagePolicy)
		auto MaximumPageSize() const -> std::uint32_t override;	  // 0x01 - { return maxPageSize; }
		auto MaximumStackDepth() const -> std::uint32_t override; // 0x02 - { return maxStackDepth; }
		auto AllocatePage(
			std::uint32_t a_sizeInBytes,
			NewPageStrategy a_strategy,
			BSTAutoPointer<MemoryPage>& a_newPage) -> AllocationStatus override;						  // 0x03
		auto GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) -> AllocationStatus override; // 0x04
		void DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) override;								  // 0x05

		// members
		std::uint32_t minPageSize{0x80};			// 0x08
		std::uint32_t maxPageSize{0x200};			// 0x0C
		std::uint32_t maxAllocatedMemory{0x2'5800}; // 0x10
		std::uint32_t maxStackDepth{0x64};			// 0x14
		bool ignoreMemoryLimit;						// 0x18
		bool outOfMemory;							// 0x19
		mutable BSSpinLock dataLock;				// 0x1C
		std::uint32_t currentMemorySize;			// 0x24
		std::uint32_t maxAdditionalAllocations;		// 0x28
	};

	static_assert(sizeof(SimpleAllocMemoryPagePolicy) == 0x30);
}
