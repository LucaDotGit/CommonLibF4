#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class SimpleArrayHeapAllocator;

	template <class T, class Allocator = SimpleArrayHeapAllocator>
	class SimpleArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		constexpr SimpleArray() noexcept = default;

		constexpr ~SimpleArray() noexcept
		{
			deallocate_bytes();
		}

		constexpr SimpleArray(std::nullptr_t) noexcept
		{
		}

		explicit SimpleArray(size_type a_count) noexcept
		{
			allocate_bytes(a_count);
		}

		constexpr SimpleArray(const SimpleArray&) = delete;

		constexpr SimpleArray(SimpleArray&& a_rhs) noexcept
			: _data(std::exchange(a_rhs._data, nullptr))
		{
		}

		constexpr SimpleArray& operator=(const SimpleArray&) = delete;

		constexpr SimpleArray& operator=(SimpleArray&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			deallocate_bytes();
			_data = std::exchange(a_rhs._data, nullptr);

			return *this;
		}

		constexpr SimpleArray& operator=(std::nullptr_t) noexcept
		{
			deallocate_bytes();
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(SimpleArray);

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return _data != nullptr; }

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(_data != nullptr);
			return _data[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(_data != nullptr);
			return _data[a_index];
		}

		[[nodiscard]] constexpr pointer data() noexcept { return _data; }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data; }

		constexpr void allocate_bytes(size_type a_count)
		{
			Allocator::deallocate_bytes(_data);

			if (a_count == 0) {
				return;
			}

			auto* newData = calloc<value_type>(a_count);
			if (!newData) {
				throw std::bad_alloc();
			}

			_data = newData;
		}

		constexpr void deallocate_bytes() noexcept
		{
			if (_data) {
				Allocator::deallocate_bytes(_data);
				_data = nullptr;
			}
		}

		constexpr void swap(SimpleArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

	private:
		// members
		pointer _data{ nullptr }; // 00
	};
	static_assert(sizeof(SimpleArray<std::any>) == 0x08);

	template <class T, class Allocator = SimpleArrayHeapAllocator>
	constexpr void swap(SimpleArray<T, Allocator>& a_lhs, SimpleArray<T, Allocator>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	class SimpleArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		SimpleArrayHeapAllocator() = default;
		~SimpleArrayHeapAllocator() noexcept = default;

		SimpleArrayHeapAllocator(const SimpleArrayHeapAllocator&) = delete;
		SimpleArrayHeapAllocator(SimpleArrayHeapAllocator&&) = delete;

		SimpleArrayHeapAllocator& operator=(const SimpleArrayHeapAllocator&) = delete;
		SimpleArrayHeapAllocator& operator=(SimpleArrayHeapAllocator&&) = delete;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_bytes) noexcept
		{
			return calloc<std::byte>(a_bytes);
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<SimpleArrayHeapAllocator>);

	template <std::uint32_t N>
	class SimpleArrayAlignedHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		SimpleArrayAlignedHeapAllocator() = default;
		~SimpleArrayAlignedHeapAllocator() noexcept = default;

		SimpleArrayAlignedHeapAllocator(const SimpleArrayAlignedHeapAllocator&) = delete;
		SimpleArrayAlignedHeapAllocator(SimpleArrayAlignedHeapAllocator&&) = delete;

		SimpleArrayAlignedHeapAllocator& operator=(const SimpleArrayAlignedHeapAllocator&) = delete;
		SimpleArrayAlignedHeapAllocator& operator=(SimpleArrayAlignedHeapAllocator&&) = delete;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_bytes) noexcept
		{
			return aligned_alloc<std::byte>(a_bytes, static_cast<std::align_val_t>(N));
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			aligned_free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<SimpleArrayAlignedHeapAllocator<0x08>>);

	class SimpleArrayScrapAllocator
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;

		SimpleArrayScrapAllocator() = default;
		~SimpleArrayScrapAllocator() noexcept = default;

		SimpleArrayScrapAllocator(const SimpleArrayScrapAllocator&) = delete;
		SimpleArrayScrapAllocator(SimpleArrayScrapAllocator&&) = delete;

		SimpleArrayScrapAllocator& operator=(const SimpleArrayScrapAllocator&) = delete;
		SimpleArrayScrapAllocator& operator=(SimpleArrayScrapAllocator&&) = delete;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_bytes) noexcept
		{
			return scrap_calloc<std::byte>(a_bytes, SCRAP_HEAP_ALIGNMENT);
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			scrap_free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<SimpleArrayScrapAllocator>);
}
