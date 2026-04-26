#include "RE/H/hkContainerHeapAllocator.hpp"

namespace RE
{
	hkContainerHeapAllocator::Allocator& hkContainerHeapAllocator::GetAllocator()
	{
		static const auto ALLOCATOR = REL::Relocation<Allocator*>{ ID::hkContainerHeapAllocator::Allocator };
		return *ALLOCATOR;
	}

	__declspec(allocator) __declspec(restrict) void* hk_container_malloc(std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerHeapAllocator::GetAllocator();
			return allocator.malloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* hk_container_calloc(std::size_t a_count, std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerHeapAllocator::GetAllocator();
			return allocator.calloc(a_count, a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void hk_container_free(void* a_ptr, std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerHeapAllocator::GetAllocator();
			allocator.free(a_ptr, a_size);
		}
		catch (...) {
			REX::DeallocationFail();
		}
	}
}
