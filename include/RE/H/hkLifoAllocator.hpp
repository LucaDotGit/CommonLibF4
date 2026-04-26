#pragma once

#include "RE/H/hkMemoryAllocator.hpp"

namespace RE
{
	class __declspec(novtable) hkLifoAllocator
		: public hkMemoryAllocator // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkLifoAllocator };
		inline static constexpr auto VTABLE{ VTABLE::hkLifoAllocator };

		class Implementation;

		// override (hkMemoryAllocator)
		void* BlockAlloc(std::int32_t a_numBytesIn) override;												  // 01
		void BlockFree(void* a_ptr, std::int32_t a_numBytesIn) override;									  // 02
		void* BufAlloc(std::int32_t& a_reqNumBytesInOut) override;											  // 03
		void BufFree(void* a_ptr, std::int32_t a_numBytes) override;										  // 04
		void* BufRealloc(void* a_old, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut) override; // 05
		void GetMemoryStatistics(MemoryStatistics& a_stats) const override;									  // 08
		std::int32_t GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) const override;			  // 09

		// members
		Implementation* impl{ nullptr };				 // 08
		std::int32_t slabSize{ 0x8000 };				 // 10
		std::byte* cur{ nullptr };						 // 18
		std::byte* end{ nullptr };						 // 20
		std::byte* firstNonLifoEnd{ nullptr };			 // 28
		std::byte* cachedEmptySlab{ nullptr };			 // 30
		hkMemoryAllocator* slabAllocator{ nullptr };	 // 38
		hkMemoryAllocator* largeAllocator{ nullptr };	 // 40
		hkMemoryAllocator* internalAllocator{ nullptr }; // 48
	};
	static_assert(sizeof(hkLifoAllocator) == 0x50);
}
