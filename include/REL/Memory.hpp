#pragma once

#include "REX/Concepts.hpp"
#include "REX/Error.hpp"

namespace REL
{
	inline constexpr auto INVALID_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

	inline constexpr auto NOP = 0x90ui8;
	inline constexpr auto RET = 0xC3ui8;
	inline constexpr auto INT3 = 0xCCui8;

	void Write(void* a_target, const void* a_source, std::size_t a_size) noexcept;
	void Write(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept;

	template <REX::trivially_writable T>
	void Write(void* a_target, std::span<T> a_source) noexcept
	{
		Write(a_target, a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T>
	void Write(std::uintptr_t a_target, std::span<T> a_source) noexcept
	{
		Write(std::bit_cast<void*>(a_target), a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T>
	void Write(std::span<T> a_target, const void* a_source) noexcept
	{
		Write(a_target.data(), a_source, a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	void Write(std::span<T> a_target, std::uintptr_t a_source) noexcept
	{
		Write(a_target.data(), std::bit_cast<void*>(a_source), a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	void WriteData(void* a_target, const T& a_source) noexcept
	{
		Write(a_target, std::addressof(a_source), sizeof(T));
	}

	template <REX::trivially_writable T>
	void WriteData(std::uintptr_t a_target, const T& a_source) noexcept
	{
		Write(std::bit_cast<void*>(a_target), std::addressof(a_source), sizeof(T));
	}

	template <REX::trivially_writable T1, REX::trivially_readable T2>
	void WriteData(std::span<T1> a_target, const T2& a_source) noexcept
	{
		Write(a_target.data(), std::addressof(a_source), a_target.size_bytes());
	}

	REX::SystemError WriteSafe(void* a_target, const void* a_source, std::size_t a_size) noexcept;
	REX::SystemError WriteSafe(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept;
	REX::SystemError WriteSafeFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept;
	REX::SystemError WriteSafeFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept;

	template <REX::trivially_writable T>
	REX::SystemError WriteSafe(void* a_target, std::span<T> a_source) noexcept
	{
		return WriteSafe(a_target, a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T>
	REX::SystemError WriteSafe(std::uintptr_t a_target, std::span<T> a_source) noexcept
	{
		return WriteSafe(std::bit_cast<void*>(a_target), a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T>
	REX::SystemError WriteSafe(std::span<T> a_target, const void* a_source) noexcept
	{
		return WriteSafe(a_target.data(), a_source, a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	REX::SystemError WriteSafe(std::span<T> a_target, std::uintptr_t a_source) noexcept
	{
		return WriteSafe(a_target.data(), std::bit_cast<void*>(a_source), a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	REX::SystemError WriteSafeData(void* a_target, const T& a_source) noexcept
	{
		return WriteSafe(a_target, std::addressof(a_source), sizeof(T));
	}

	template <REX::trivially_writable T>
	REX::SystemError WriteSafeData(std::uintptr_t a_target, const T& a_source) noexcept
	{
		return WriteSafe(std::bit_cast<void*>(a_target), std::addressof(a_source), sizeof(T));
	}

	template <REX::trivially_writable T1, REX::trivially_readable T2>
	REX::SystemError WriteSafeData(std::span<T1> a_target, const T2& a_source) noexcept
	{
		return WriteSafe(a_target.data(), std::addressof(a_source), a_target.size_bytes());
	}
}

#if _WIN32 == 1
#define REL_ALIGNED_ALLOC(a_size, a_alignment) ::_aligned_malloc(a_size, static_cast<std::size_t>(a_alignment))
#define REL_ALIGNED_FREE(a_ptr) ::_aligned_free(a_ptr)
#else
#define REL_ALIGNED_ALLOC(a_size, a_alignment) std::aligned_alloc(a_size, static_cast<std::size_t>(a_alignment))
#define REL_ALIGNED_FREE(a_ptr) std::free(a_ptr)
#endif

#define REL_HEAP_REDEFINE_NEW(a_type)                                                                                   \
	static_assert(std::is_class_v<a_type>);                                                                             \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size)                                                                \
	{                                                                                                                   \
		auto* mem = std::malloc(a_size);                                                                                \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size)                                                              \
	{                                                                                                                   \
		auto* mem = std::malloc(a_size);                                                                                \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new(std::size_t a_size, std::align_val_t a_alignment)                                  \
	{                                                                                                                   \
		auto* mem = REL_ALIGNED_ALLOC(a_size, a_alignment);                                                             \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] void* operator new[](std::size_t a_size, std::align_val_t a_alignment)                                \
	{                                                                                                                   \
		auto* mem = REL_ALIGNED_ALLOC(a_size, a_alignment);                                                             \
		if (!mem) [[unlikely]] {                                                                                        \
			throw std::bad_alloc();                                                                                     \
		}                                                                                                               \
                                                                                                                        \
		return mem;                                                                                                     \
	}                                                                                                                   \
                                                                                                                        \
	[[nodiscard]] constexpr void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] constexpr void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] constexpr void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] constexpr void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                                        \
	void operator delete(void* a_ptr) noexcept { std::free(a_ptr); }                                                    \
	void operator delete[](void* a_ptr) noexcept { std::free(a_ptr); }                                                  \
	void operator delete(void* a_ptr, std::align_val_t) noexcept { REL_ALIGNED_FREE(a_ptr); }                           \
	void operator delete[](void* a_ptr, std::align_val_t) noexcept { REL_ALIGNED_FREE(a_ptr); }                         \
	void operator delete(void* a_ptr, std::size_t) noexcept { std::free(a_ptr); }                                       \
	void operator delete[](void* a_ptr, std::size_t) noexcept { std::free(a_ptr); }                                     \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) noexcept { REL_ALIGNED_FREE(a_ptr); }              \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) noexcept { REL_ALIGNED_FREE(a_ptr); }
