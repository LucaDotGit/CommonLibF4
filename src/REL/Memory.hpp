#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Error.hpp"
#include "REX/Exception.hpp"

namespace REL
{
	class IId;

	inline constexpr auto INVALID_ADDRESS = std::numeric_limits<std::uintptr_t>::min();

	inline constexpr auto OP_CODE_NOP = static_cast<std::uint8_t>(0x90);
	inline constexpr auto OP_CODE_RET = static_cast<std::uint8_t>(0xC3);
	inline constexpr auto OP_CODE_INT3 = static_cast<std::uint8_t>(0xCC);

	template <class T, class U>
	[[nodiscard]]
	constexpr auto AdjustPointer(U* a_ptr, std::ptrdiff_t a_offset) noexcept -> auto*
	{
		const auto address = a_ptr ? std::bit_cast<std::uintptr_t>(a_ptr) + a_offset : 0;

		if constexpr (std::is_const_v<U> && std::is_volatile_v<U>) {
			return std::bit_cast<std::add_cv_t<T>*>(address);
		}
		else if constexpr (std::is_const_v<U>) {
			return std::bit_cast<std::add_const_t<T>*>(address);
		}
		else if constexpr (std::is_volatile_v<U>) {
			return std::bit_cast<std::add_volatile_t<T>*>(address);
		}
		else {
			return std::bit_cast<T*>(address);
		}
	}

	template <class T>
	[[nodiscard]]
	auto GetVtableAddress(const T& a_self) noexcept -> std::uintptr_t
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<const std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	[[nodiscard]]
	auto GetVtableRef(T& a_self) noexcept -> std::uintptr_t&
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	[[nodiscard]]
	auto GetVtableRef(const T& a_self) noexcept -> const std::uintptr_t&
		requires(std::is_polymorphic_v<T>)
	{
		return reinterpret_cast<const std::uintptr_t*>(std::addressof(a_self))[0];
	}

	template <class T>
	void EmplaceVtable(T* a_self, std::uintptr_t a_vtableAddress) noexcept
		requires(std::is_polymorphic_v<T> && !std::is_const_v<T>)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto& vtableRef = GetVtableRef(*a_self);
		vtableRef = a_vtableAddress;
	}

	template <class T, class Id, std::size_t N>
	void EmplaceVtable(T* a_self, const std::array<Id, N>& a_vtable) noexcept
		requires(std::is_polymorphic_v<T> && !std::is_const_v<T> && std::derived_from<Id, REL::IId> && N > 0)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		EmplaceVtable(a_self, a_vtable[0].GetAddress());
	}

	template <class T>
	void EmplaceVtable(T* a_self) noexcept
		requires(
			std::is_polymorphic_v<T> &&
			!std::is_const_v<T> &&
			std::derived_from<
				typename std::remove_reference_t<decltype(REX::remove_cvpr_t<T>::VTABLE)>::value_type,
				REL::IId>)
	{
		if (!a_self) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		EmplaceVtable(a_self, T::VTABLE[0].GetAddress());
	}

	auto Write(void* a_target, const void* a_source, std::size_t a_size) noexcept -> std::size_t;
	auto Write(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept -> std::size_t;

	auto WriteFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept -> std::size_t;
	auto WriteFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept -> std::size_t;

	template <REX::trivially_writable T, std::size_t N>
	auto Write(void* a_target, std::span<T, N> a_source) noexcept -> std::size_t
	{
		return Write(a_target, a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto Write(std::uintptr_t a_target, std::span<T, N> a_source) noexcept -> std::size_t
	{
		return Write(std::bit_cast<void*>(a_target), a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto Write(std::span<T, N> a_target, const void* a_source) noexcept -> std::size_t
	{
		return Write(static_cast<void*>(a_target.data()), a_source, a_target.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto Write(std::span<T, N> a_target, std::uintptr_t a_source) noexcept -> std::size_t
	{
		return Write(static_cast<void*>(a_target.data()), std::bit_cast<void*>(a_source), a_target.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto WriteFill(std::span<T, N> a_target, std::uint8_t a_value) noexcept -> std::size_t
	{
		return WriteFill(static_cast<void*>(a_target.data()), a_value, a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	auto WriteData(void* a_target, const T& a_source) noexcept -> std::size_t
	{
		return Write(a_target, static_cast<const void*>(std::addressof(a_source)), sizeof(T));
	}

	template <REX::trivially_writable T>
	auto WriteData(std::uintptr_t a_target, const T& a_source) noexcept -> std::size_t
	{
		return Write(std::bit_cast<void*>(a_target), static_cast<const void*>(std::addressof(a_source)), sizeof(T));
	}

	template <REX::trivially_writable T1, REX::trivially_readable T2>
	auto WriteData(std::span<T1> a_target, const T2& a_source) noexcept -> std::size_t
	{
		return Write(
			static_cast<void*>(a_target.data()),
			static_cast<const void*>(std::addressof(a_source)),
			a_target.size_bytes());
	}

	auto WriteSafe(void* a_target, const void* a_source, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	auto WriteSafe(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	auto WriteSafeFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	auto WriteSafeFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	template <REX::trivially_writable T, std::size_t N>
	auto WriteSafe(void* a_target, std::span<T, N> a_source) noexcept -> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(a_target, a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto WriteSafe(std::uintptr_t a_target, std::span<T, N> a_source) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(std::bit_cast<void*>(a_target), a_source.data(), a_source.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto WriteSafe(std::span<T, N> a_target, const void* a_source) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(a_target.data(), a_source, a_target.size_bytes());
	}

	template <REX::trivially_writable T, std::size_t N>
	auto WriteSafe(std::span<T, N> a_target, std::uintptr_t a_source) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(a_target.data(), std::bit_cast<void*>(a_source), a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	auto WriteSafeData(void* a_target, const T& a_source) noexcept -> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(a_target, static_cast<const void*>(std::addressof(a_source)), sizeof(T));
	}

	template <REX::trivially_writable T>
	auto WriteSafeData(std::uintptr_t a_target, const T& a_source) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(std::bit_cast<void*>(a_target), static_cast<const void*>(std::addressof(a_source)), sizeof(T));
	}

	template <REX::trivially_writable T1, REX::trivially_readable T2>
	auto WriteSafeData(std::span<T1> a_target, const T2& a_source) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(
			static_cast<void*>(a_target.data()),
			static_cast<const void*>(std::addressof(a_source)),
			a_target.size_bytes());
	}

	template <REX::trivially_writable T>
	auto WriteSafeFill(std::span<T> a_target, std::uint8_t a_value) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafeFill(static_cast<void*>(a_target.data()), a_value, a_target.size_bytes());
	}

	void WriteZeros(void* a_ptr, std::size_t a_size) noexcept;
	void WriteZeros(std::uintptr_t a_ptr, std::size_t a_size) noexcept;

	template <REX::trivially_writable T>
	void WriteZeros(std::span<T> a_target) noexcept
	{
		WriteZeros(static_cast<void*>(a_target.data()), a_target.size_bytes());
	}

	[[nodiscard]]
	__declspec(allocator)
	__declspec(restrict) auto AlignedAllocate(std::size_t a_size, std::align_val_t a_alignment) noexcept -> void*;
	__declspec(noalias) void AlignedFree(void* a_ptr) noexcept;
}

namespace REL
{
	template <class T>
	struct StlAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr StlAllocator() noexcept = default;
		constexpr ~StlAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StlAllocator([[maybe_unused]] const StlAllocator<U>& a_other) noexcept
		{
		}

		constexpr StlAllocator(const StlAllocator&) noexcept = default;
		constexpr StlAllocator(StlAllocator&&) noexcept = default;

		constexpr auto operator=(const StlAllocator&) noexcept -> StlAllocator& = default;
		constexpr auto operator=(StlAllocator&&) noexcept -> StlAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			// NOLINTNEXTLINE(cppcoreguidelines-no-malloc)
			auto* mem = std::malloc(a_count * sizeof(value_type));
			if (!mem) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			return mem;
		}

		[[nodiscard]]
		auto allocate_at_least(size_type a_count) -> std::allocation_result<value_type*, size_type>
		{
			return {allocate(a_count), a_count};
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			// NOLINTNEXTLINE(cppcoreguidelines-no-malloc)
			std::free(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const StlAllocator<T1>& a_lhs,
		[[maybe_unused]] const StlAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}

	template <class T>
	struct StlAlignedAllocator
	{
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;

		constexpr StlAlignedAllocator() noexcept = default;
		constexpr ~StlAlignedAllocator() noexcept = default;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StlAlignedAllocator([[maybe_unused]] const StlAlignedAllocator<U>& a_other) noexcept
		{
		}

		constexpr StlAlignedAllocator(const StlAlignedAllocator&) noexcept = default;
		constexpr StlAlignedAllocator(StlAlignedAllocator&&) noexcept = default;

		constexpr auto operator=(const StlAlignedAllocator&) noexcept -> StlAlignedAllocator& = default;
		constexpr auto operator=(StlAlignedAllocator&&) noexcept -> StlAlignedAllocator& = default;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate(size_type a_count) -> value_type*
		{
			auto* mem =
				REL::AlignedAllocate(a_count * sizeof(value_type), static_cast<std::align_val_t>(alignof(value_type)));
			if (!mem) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			return mem;
		}

		[[nodiscard]]
		auto allocate_at_least(size_type a_count) -> std::allocation_result<value_type*, size_type>
		{
			return {allocate(a_count), a_count};
		}

		__declspec(noalias) void deallocate(value_type* a_ptr, [[maybe_unused]] size_type a_count) noexcept
		{
			REL::AlignedFree(static_cast<void*>(a_ptr));
		}
	};

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto operator==(
		[[maybe_unused]] const StlAlignedAllocator<T1>& a_lhs,
		[[maybe_unused]] const StlAlignedAllocator<T2>& a_rhs) noexcept -> bool
	{
		return true;
	}
}

#define REL_HEAP_REDEFINE_NEW(a_type)                                                                                 \
	static_assert(std::is_class_v<a_type>);                                                                           \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size)                                                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = std::malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size)                                                                           \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = std::malloc(a_size);                                                                              \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment)                                               \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = REL::AlignedAllocate(a_size, a_alignment);                                                        \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, std::align_val_t a_alignment)                                             \
		->void*                                                                                                       \
	{                                                                                                                 \
		auto* mem = REL::AlignedAllocate(a_size, a_alignment);                                                        \
		if (!mem) [[unlikely]] {                                                                                      \
			::REX::Throw<std::bad_alloc>();                                                                           \
		}                                                                                                             \
                                                                                                                      \
		return mem;                                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                      \
	{                                                                                                                 \
		return std::malloc(a_size);                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](std::size_t a_size, const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                    \
	{                                                                                                                 \
		return std::malloc(a_size);                                                                                   \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new(std::size_t a_size, std::align_val_t a_alignment, const std::nothrow_t& /*a_nothrow*/) noexcept \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return REL::AlignedAllocate(a_size, a_alignment);                                                             \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	auto operator new[](                                                                                              \
		std::size_t a_size,                                                                                           \
		std::align_val_t a_alignment,                                                                                 \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return REL::AlignedAllocate(a_size, a_alignment);                                                             \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                                \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr) noexcept -> void*                              \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept       \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, std::align_val_t /*a_alignment*/, void* a_ptr) noexcept     \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept    \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](std::size_t /*a_size*/, void* a_ptr, const std::nothrow_t& /*a_nothrow*/) noexcept  \
		-> void*                                                                                                      \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new(                                                                                      \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	[[nodiscard]]                                                                                                     \
	constexpr auto operator new[](                                                                                    \
		std::size_t /*a_size*/,                                                                                       \
		std::align_val_t /*a_alignment*/,                                                                             \
		void* a_ptr,                                                                                                  \
		const std::nothrow_t& /*a_nothrow*/) noexcept -> void*                                                        \
	{                                                                                                                 \
		return a_ptr;                                                                                                 \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr) noexcept                                                                        \
	{                                                                                                                 \
		std::free(a_ptr);                                                                                             \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr) noexcept                                                                      \
	{                                                                                                                 \
		std::free(a_ptr);                                                                                             \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                      \
	{                                                                                                                 \
		REL::AlignedFree(a_ptr);                                                                                      \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::align_val_t /*a_alignment*/) noexcept                                    \
	{                                                                                                                 \
		REL::AlignedFree(a_ptr);                                                                                      \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t) noexcept                                                           \
	{                                                                                                                 \
		std::free(a_ptr);                                                                                             \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t) noexcept                                                         \
	{                                                                                                                 \
		std::free(a_ptr);                                                                                             \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete(void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept              \
	{                                                                                                                 \
		REL::AlignedFree(a_ptr);                                                                                      \
	}                                                                                                                 \
                                                                                                                      \
	void operator delete[](void* a_ptr, std::size_t /*a_size*/, std::align_val_t /*a_alignment*/) noexcept            \
	{                                                                                                                 \
		REL::AlignedFree(a_ptr);                                                                                      \
	}
