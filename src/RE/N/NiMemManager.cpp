#include "RE/N/NiMemManager.hpp"

namespace RE::Impl
{
	__declspec(allocator) __declspec(restrict) void* NiMalloc(std::size_t a_size)
	{
		using FuncType = decltype(&NiMalloc);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiMalloc };
		return std::invoke(FUNC, a_size);
	}

	__declspec(allocator) __declspec(restrict) void* NiAlignedAlloc(std::size_t a_size, std::align_val_t a_alignment)
	{
		using FuncType = decltype(&NiAlignedAlloc);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlignedAlloc };
		return std::invoke(FUNC, a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) void* NiRealloc(void* a_ptr, std::size_t a_newSize)
	{
		using FuncType = decltype(&NiRealloc);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiRealloc };
		return std::invoke(FUNC, a_ptr, a_newSize);
	}

	__declspec(allocator) __declspec(restrict) void* NiAlignedRealloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment)
	{
		using FuncType = decltype(&NiAlignedRealloc);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiAlignedRealloc };
		return std::invoke(FUNC, a_ptr, a_newSize, a_alignment);
	}

	__declspec(noalias) void NiFree(void* a_ptr)
	{
		using FuncType = decltype(&NiFree);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::NiFree };
		FUNC(a_ptr);
	}
}

namespace RE
{
	__declspec(allocator) __declspec(restrict) void* ni_malloc(std::size_t a_size) noexcept
	{
		try {
			return Impl::NiMalloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* ni_aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		try {
			return Impl::NiAlignedAlloc(a_size, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* ni_calloc(std::size_t a_count, std::size_t a_size) noexcept
	{
		try {
			auto* mem = ni_malloc(a_count * a_size);
			if (mem) {
				REL::MemWriteZero(mem, a_count * a_size);
			}

			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* ni_realloc(void* a_ptr, std::size_t a_newSize) noexcept
	{
		try {
			return Impl::NiRealloc(a_ptr, a_newSize);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* ni_aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept
	{
		try {
			return Impl::NiAlignedRealloc(a_ptr, a_newSize, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void ni_free(void* a_ptr) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			Impl::NiFree(a_ptr);
		}
		catch (...) {
			REX::DeallocationFail();
		}
	}
}
