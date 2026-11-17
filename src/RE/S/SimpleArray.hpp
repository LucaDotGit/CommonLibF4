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
		using allocator_type = Allocator;
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

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr SimpleArray(std::nullptr_t) noexcept
		{
		}

		explicit SimpleArray(size_type a_count)
		{
			allocate_bytes(a_count);
		}

		constexpr SimpleArray(const SimpleArray&) = delete;

		constexpr SimpleArray(SimpleArray&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr))
		{
		}

		constexpr auto operator=(const SimpleArray&) -> SimpleArray& = delete;

		constexpr auto operator=(SimpleArray&& a_rhs) noexcept -> SimpleArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			deallocate_bytes();
			_data = std::exchange(a_rhs._data, nullptr);

			return *this;
		}

		constexpr auto operator=(std::nullptr_t) noexcept -> SimpleArray&
		{
			deallocate_bytes();
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(SimpleArray);

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return _data != nullptr;
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(_data != nullptr);
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(_data != nullptr);
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data;
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data;
		}

		constexpr void allocate_bytes(size_type a_count)
		{
			_allocator.deallocate_bytes(_data);

			if (a_count == 0) {
				return;
			}

			auto* newData = static_cast<pointer>(_allocator.allocate_bytes(a_count * sizeof(value_type)));
			if (!newData) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			_data = newData;
		}

		constexpr void deallocate_bytes() noexcept
		{
			if (_data) {
				_allocator.deallocate_bytes(_data);
				_data = nullptr;
			}
		}

		constexpr void swap(SimpleArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_data, a_other._data);
		}

	private:
		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		allocator_type _allocator{}; // 0x00
		pointer _data{nullptr};		 // 0x00
	};

	class SimpleArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		SimpleArrayHeapAllocator() noexcept = default;
		~SimpleArrayHeapAllocator() noexcept = default;

		SimpleArrayHeapAllocator(const SimpleArrayHeapAllocator&) = delete;
		SimpleArrayHeapAllocator(SimpleArrayHeapAllocator&&) = delete;

		auto operator=(const SimpleArrayHeapAllocator&) -> SimpleArrayHeapAllocator& = delete;
		auto operator=(SimpleArrayHeapAllocator&&) -> SimpleArrayHeapAllocator& = delete;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_bytes) noexcept -> void*
		{
			return malloc<std::byte>(a_bytes);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<SimpleArrayHeapAllocator>);

	template <std::uint32_t N>
	class SimpleArrayAlignedHeapAllocator
	{
	public:
		using size_type = std::uint32_t;

		SimpleArrayAlignedHeapAllocator() noexcept = default;
		~SimpleArrayAlignedHeapAllocator() noexcept = default;

		SimpleArrayAlignedHeapAllocator(const SimpleArrayAlignedHeapAllocator&) = delete;
		SimpleArrayAlignedHeapAllocator(SimpleArrayAlignedHeapAllocator&&) = delete;

		auto operator=(const SimpleArrayAlignedHeapAllocator&) -> SimpleArrayAlignedHeapAllocator& = delete;
		auto operator=(SimpleArrayAlignedHeapAllocator&&) -> SimpleArrayAlignedHeapAllocator& = delete;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_bytes) noexcept -> void*
		{
			return aligned_alloc<std::byte>(a_bytes, static_cast<std::align_val_t>(N));
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			aligned_free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<SimpleArrayAlignedHeapAllocator<0x08>>);

	class SimpleArrayScrapAllocator
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;

		SimpleArrayScrapAllocator() noexcept = default;
		~SimpleArrayScrapAllocator() noexcept = default;

		SimpleArrayScrapAllocator(const SimpleArrayScrapAllocator&) = delete;
		SimpleArrayScrapAllocator(SimpleArrayScrapAllocator&&) = delete;

		auto operator=(const SimpleArrayScrapAllocator&) -> SimpleArrayScrapAllocator& = delete;
		auto operator=(SimpleArrayScrapAllocator&&) -> SimpleArrayScrapAllocator& = delete;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_bytes) noexcept -> void*
		{
			return scrap_alloc<std::byte>(a_bytes, SCRAP_HEAP_ALIGNMENT);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			scrap_free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<SimpleArrayScrapAllocator>);

	template <class T, std::uint32_t Alignment = alignof(T)>
	using SimpleAlignedArray = SimpleArray<T, SimpleArrayAlignedHeapAllocator<Alignment>>;

	template <class T>
	using SimpleScrapArray = SimpleArray<T, SimpleArrayScrapAllocator>;
}
