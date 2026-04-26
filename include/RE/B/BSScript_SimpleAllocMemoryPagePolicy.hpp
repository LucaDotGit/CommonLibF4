#pragma once

#include "RE/B/BSScript_IMemoryPagePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class __declspec(novtable) SimpleAllocMemoryPagePolicy
		: public IMemoryPagePolicy // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__SimpleAllocMemoryPagePolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__SimpleAllocMemoryPagePolicy };

		~SimpleAllocMemoryPagePolicy() override; // 00

		// override (IMemoryPagePolicy)
		std::uint32_t MaximumPageSize() const override;																							// 01 - { return maxPageSize; }
		std::uint32_t MaximumStackDepth() const override;																						// 02 - { return maxStackDepth; }
		AllocationStatus AllocatePage(std::uint32_t a_sizeInBytes, NewPageStrategy a_strategy, BSTAutoPointer<MemoryPage>& a_newPage) override; // 03
		AllocationStatus GetLargestAvailablePage(BSTAutoPointer<MemoryPage>& a_newPage) override;												// 04
		void DisposePage(BSTAutoPointer<MemoryPage>& a_oldPage) override;																		// 05

		// members
		std::uint32_t minPageSize{ 0x80 };			 // 08
		std::uint32_t maxPageSize{ 0x200 };			 // 0C
		std::uint32_t maxAllocatedMemory{ 0x25800 }; // 10
		std::uint32_t maxStackDepth{ 0x64 };		 // 14
		bool ignoreMemoryLimit;						 // 18
		bool outOfMemory;							 // 19
		mutable BSSpinLock dataLock;				 // 1C
		std::uint32_t currentMemorySize;			 // 24
		std::uint32_t maxAdditionalAllocations;		 // 28
	};
	static_assert(sizeof(SimpleAllocMemoryPagePolicy) == 0x30);
}
