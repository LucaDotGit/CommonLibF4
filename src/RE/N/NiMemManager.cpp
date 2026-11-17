#include "RE/N/NiMemManager.hpp"

namespace RE::Impl
{
	__declspec(allocator) __declspec(restrict) auto NiMalloc(std::size_t a_size) -> void*
	{
		using FuncType = decltype(&NiMalloc);
		static const auto FUNC = REL::Relocation<FuncType>(ID::NiMalloc);
		return std::invoke(FUNC, a_size);
	}

	__declspec(allocator) __declspec(restrict) auto NiAlignedAlloc(std::size_t a_size, std::align_val_t a_alignment)
		-> void*
	{
		using FuncType = decltype(&NiAlignedAlloc);
		static const auto FUNC = REL::Relocation<FuncType>(ID::NiAlignedAlloc);
		return std::invoke(FUNC, a_size, a_alignment);
	}

	__declspec(allocator) __declspec(restrict) auto NiRealloc(void* a_ptr, std::size_t a_newSize) -> void*
	{
		using FuncType = decltype(&NiRealloc);
		static const auto FUNC = REL::Relocation<FuncType>(ID::NiRealloc);
		return std::invoke(FUNC, a_ptr, a_newSize);
	}

	__declspec(allocator) __declspec(restrict) auto NiAlignedRealloc(
		void* a_ptr,
		std::size_t a_newSize,
		std::align_val_t a_alignment) -> void*
	{
		using FuncType = decltype(&NiAlignedRealloc);
		static const auto FUNC = REL::Relocation<FuncType>(ID::NiAlignedRealloc);
		return std::invoke(FUNC, a_ptr, a_newSize, a_alignment);
	}

	__declspec(noalias) void NiFree(void* a_ptr)
	{
		using FuncType = decltype(&NiFree);
		static const auto FUNC = REL::Relocation<FuncType>(ID::NiFree);
		std::invoke(FUNC, a_ptr);
	}
}

namespace RE
{
	__declspec(allocator) __declspec(restrict) auto ni_malloc(std::size_t a_size) noexcept -> void*
	{
		try {
			return Impl::NiMalloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto ni_aligned_alloc(std::size_t a_size, std::align_val_t a_alignment)
		noexcept -> void*
	{
		try {
			return Impl::NiAlignedAlloc(a_size, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto ni_calloc(std::size_t a_count, std::size_t a_size) noexcept -> void*
	{
		try {
			auto* mem = ni_malloc(a_count * a_size);
			if (!mem) {
				return nullptr;
			}

			REL::WriteZeros(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto ni_realloc(void* a_ptr, std::size_t a_newSize) noexcept -> void*
	{
		try {
			return Impl::NiRealloc(a_ptr, a_newSize);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto ni_aligned_realloc(
		void* a_ptr,
		std::size_t a_newSize,
		std::align_val_t a_alignment) noexcept -> void*
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
			REX::Fail("Failed to free memory."sv);
		}
	}
}
