#pragma once

#include "RE/H/hkMemoryAllocator.hpp"

namespace RE
{
	class __declspec(novtable) hkLifoAllocator : public hkMemoryAllocator // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkLifoAllocator;
		inline static constexpr const auto& VTABLE = VTABLE::hkLifoAllocator;

		class Implementation;

		// override (hkMemoryAllocator)
		auto BlockAlloc(std::int32_t a_numBytesIn) -> void* override;	   // 0x01
		void BlockFree(void* a_ptr, std::int32_t a_numBytesIn) override;   // 0x02
		auto BufAlloc(std::int32_t& a_reqNumBytesInOut) -> void* override; // 0x03
		void BufFree(void* a_ptr, std::int32_t a_numBytes) override;	   // 0x04
		auto BufRealloc(void* a_old, std::int32_t a_oldNumBytes, std::int32_t& a_reqNumBytesInOut)
			-> void* override;																			  // 0x05
		void GetMemoryStatistics(MemoryStatistics& a_stats) const override;								  // 0x08
		auto GetAllocatedSize(const void* a_obj, std::int32_t a_numBytes) const -> std::int32_t override; // 0x09

		// members
		Implementation* impl{nullptr};				   // 0x08
		std::int32_t slabSize{0x8000};				   // 0x10
		std::byte* current{nullptr};				   // 0x18
		std::byte* end{nullptr};					   // 0x20
		std::byte* firstNonLifoEnd{nullptr};		   // 0x28
		std::byte* cachedEmptySlab{nullptr};		   // 0x30
		hkMemoryAllocator* slabAllocator{nullptr};	   // 0x38
		hkMemoryAllocator* largeAllocator{nullptr};	   // 0x40
		hkMemoryAllocator* internalAllocator{nullptr}; // 0x48
	};

	static_assert(sizeof(hkLifoAllocator) == 0x50);
}
