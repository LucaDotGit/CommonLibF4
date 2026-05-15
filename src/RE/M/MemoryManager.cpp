#include "RE/M/MemoryManager.hpp"

namespace RE
{
	MemoryManager::AutoScrapBuffer::~AutoScrapBuffer() noexcept
	{
		deallocate_bytes(_data);
	}

	MemoryManager::AutoScrapBuffer::AutoScrapBuffer(std::size_t a_size, std::align_val_t a_alignment)
		: _data(allocate_bytes(a_size, a_alignment))
	{
	}

	MemoryManager::AutoScrapBuffer::AutoScrapBuffer(AutoScrapBuffer&& a_rhs) noexcept
		: _data(std::exchange(a_rhs._data, nullptr))
	{
	}

	MemoryManager::AutoScrapBuffer& MemoryManager::AutoScrapBuffer::operator=(AutoScrapBuffer&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		deallocate_bytes(_data);
		_data = std::exchange(a_rhs._data, nullptr);

		return *this;
	}

	__declspec(allocator) __declspec(restrict) void* MemoryManager::AutoScrapBuffer::allocate_bytes(std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		return scrap_alloc(a_size, a_alignment);
	}

	__declspec(noalias) void MemoryManager::AutoScrapBuffer::deallocate_bytes(void* a_mem) noexcept
	{
		if (!a_mem) {
			return;
		}

		scrap_free(a_mem);
	}

	MemoryManager& MemoryManager::GetSingleton()
	{
		using FuncType = decltype(&MemoryManager::GetSingleton);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::Singleton };
		return std::invoke(FUNC);
	}

	void MemoryManager::RegisterMemoryManager()
	{
		using FuncType = decltype(&MemoryManager::RegisterMemoryManager);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::RegisterMemoryManager };
		std::invoke(FUNC, this);
	}

	ScrapHeap* MemoryManager::GetThreadScrapHeap()
	{
		using FuncType = decltype(&MemoryManager::GetThreadScrapHeap);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::GetThreadScrapHeap };
		return std::invoke(FUNC, this);
	}

	__declspec(allocator) __declspec(restrict) void* MemoryManager::Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
	{
		using FuncType = decltype(&MemoryManager::Allocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::Allocate };
		return std::invoke(FUNC, this, a_size, a_alignment, a_alignmentRequired);
	}

	__declspec(allocator) __declspec(restrict) void* MemoryManager::Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired)
	{
		using FuncType = decltype(&MemoryManager::Reallocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::Reallocate };
		return std::invoke(FUNC, this, a_oldMem, a_newSize, a_alignment, a_alignmentRequired);
	}

	__declspec(noalias) void MemoryManager::Deallocate(void* a_mem, bool a_alignmentRequired)
	{
		using FuncType = decltype(&MemoryManager::Deallocate);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::Deallocate };
		std::invoke(FUNC, this, a_mem, a_alignmentRequired);
	}

	__declspec(noalias) std::size_t MemoryManager::Size(const void* a_ptr) const
	{
		using FuncType = decltype(&MemoryManager::Size);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::MemoryManager::Size };
		return std::invoke(FUNC, this, a_ptr);
	}

	__declspec(allocator) __declspec(restrict) void* malloc(std::size_t a_size) noexcept
	{
		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			return memoryManager.Allocate(a_size, 0, false);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* aligned_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			return memoryManager.Allocate(a_size, static_cast<std::uint32_t>(a_alignment), true);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* calloc(std::size_t a_count, std::size_t a_size) noexcept
	{
		try {
			auto* mem = malloc(a_count * a_size);
			if (!mem) {
				return nullptr;
			}

			REL::MemWriteZero(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* realloc(void* a_ptr, std::size_t a_newSize) noexcept
	{
		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			return memoryManager.Reallocate(a_ptr, a_newSize, 0, false);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* aligned_realloc(void* a_ptr, std::size_t a_newSize, std::align_val_t a_alignment) noexcept
	{
		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			return memoryManager.Reallocate(a_ptr, a_newSize, static_cast<std::uint32_t>(a_alignment), true);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* scrap_alloc(std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		try {
			auto* memoryManager = MemoryManager::GetSingleton().GetThreadScrapHeap();
			if (!memoryManager) {
				return nullptr;
			}

			return memoryManager->Allocate(a_size, a_alignment);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* scrap_calloc(std::size_t a_count, std::size_t a_size, std::align_val_t a_alignment) noexcept
	{
		try {
			auto* mem = scrap_alloc(a_count * a_size, a_alignment);
			if (!mem) {
				return nullptr;
			}

			REL::MemWriteZero(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void free(void* a_ptr) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			memoryManager.Deallocate(a_ptr, false);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}

	__declspec(noalias) void aligned_free(void* a_ptr) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			memoryManager.Deallocate(a_ptr, true);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}

	__declspec(noalias) void scrap_free(void* a_ptr) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			auto* scrapHeap = MemoryManager::GetSingleton().GetThreadScrapHeap();
			if (!scrapHeap) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			scrapHeap->Deallocate(a_ptr);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}

	__declspec(noalias) std::size_t msize(const void* a_ptr) noexcept
	{
		try {
			auto& memoryManager = MemoryManager::GetSingleton();
			return memoryManager.Size(a_ptr);
		}
		catch (...) {
			return 0;
		}
	}

	__declspec(noalias) std::size_t scrap_msize(const void* a_ptr) noexcept
	{
		try {
			auto* scrapHeap = MemoryManager::GetSingleton().GetThreadScrapHeap();
			if (!scrapHeap) {
				return 0;
			}

			return scrapHeap->Size(a_ptr);
		}
		catch (...) {
			return 0;
		}
	}
}
