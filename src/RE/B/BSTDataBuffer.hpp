#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSTDataBufferHeapAllocator;

	template <std::uint32_t N, class Allocator = BSTDataBufferHeapAllocator>
	class BSTDataBuffer
	{
	public:
		inline static constexpr auto MAX_SIZE = N;
		inline static constexpr auto INVALID_ID = static_cast<std::uint32_t>(std::numeric_limits<std::uint8_t>::max());

		using value_type = std::byte;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		class Block
		{
		public:
			// members
			std::uint32_t size : 24; // 0x00:00
			std::uint32_t id   : 8;	 // 0x00:24
		};

		static_assert(sizeof(Block) == 0x04);

		BSTDataBuffer() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		~BSTDataBuffer() noexcept
		{
			free_buffer();
		}

		BSTDataBuffer(const BSTDataBuffer& a_rhs) = delete;

		BSTDataBuffer(BSTDataBuffer&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr)),
			_size(std::exchange(a_rhs._size, 0))
		{
		}

		auto operator=(const BSTDataBuffer& a_rhs) -> BSTDataBuffer& = delete;

		auto operator=(BSTDataBuffer&& a_rhs) noexcept -> BSTDataBuffer&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			free_buffer();

			_data = std::exchange(a_rhs._data, nullptr);
			_size = std::exchange(a_rhs._size, 0);
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTDataBuffer);

		[[nodiscard]]
		auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(data() && a_index < _size);
			return data()[a_index];
		}

		[[nodiscard]]
		auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(data() && a_index < _size);
			return data()[a_index];
		}

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return _data;
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return data();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return begin() + size();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return begin() + size();
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _size;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		[[nodiscard]]
		auto has_block(std::uint8_t a_id) const noexcept -> bool
		{
			if (!_data || a_id == INVALID_ID) {
				return false;
			}

			auto* blocks = reinterpret_cast<Block*>(_data + _size);

			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				const auto& block = blocks[i];
				if (block.id == a_id) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]]
		auto get_block(std::uint8_t a_id) noexcept -> std::pair<Block*, std::uint32_t>
		{
			if (!_data || a_id == INVALID_ID) {
				return {nullptr, 0};
			}

			auto* blocks = reinterpret_cast<Block*>(_data + _size);

			auto offset = static_cast<size_type>(0);
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				auto& block = blocks[i];
				if (block.id == a_id) {
					return {std::addressof(block), offset};
				}

				offset += block.size;
			}

			return {nullptr, 0};
		}

		[[nodiscard]]
		auto get_block(std::uint8_t a_id) const noexcept -> std::pair<const Block*, std::uint32_t>
		{
			if (!_data || a_id == INVALID_ID) {
				return {nullptr, 0};
			}

			const auto* blocks = reinterpret_cast<const Block*>(_data + _size);

			auto offset = static_cast<size_type>(0);
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				const auto& block = blocks[i];
				if (block.id == a_id) {
					return {std::addressof(block), offset};
				}

				offset += block.size;
			}

			return {nullptr, 0};
		}

		template <class T>
		[[nodiscard]]
		auto get_buffer(std::uint8_t a_id) noexcept -> std::span<T>
		{
			auto&& [block, offset] = get_block(a_id);
			if (!block) {
				return {};
			}

			return {reinterpret_cast<T*>(_data + offset), block->size / sizeof(T)};
		}

		template <class T>
		[[nodiscard]]
		auto get_buffer(std::uint8_t a_id) const noexcept -> std::span<const T>
		{
			const auto&& [block, offset] = get_block(a_id);
			if (!block) {
				return {};
			}

			return {reinterpret_cast<const T*>(_data + offset), block->size / sizeof(T)};
		}

		void swap(BSTDataBuffer& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_data, a_other._data);
			std::swap(_size, a_other._size);
		}

	private:
		template <std::uint32_t, class>
		friend class BSTDataBuffer;

		void free_buffer() noexcept
		{
			if (_data) {
				_allocator.deallocate_bytes(_data);
				_data = nullptr;
			}

			_size = 0;
		}

		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		Allocator _allocator{}; // 0x00
		pointer _data{nullptr}; // 0x00
		size_type _size{0};		// 0x08
	};

	class BSTDataBufferHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;

		BSTDataBufferHeapAllocator() noexcept = default;
		~BSTDataBufferHeapAllocator() noexcept = default;

		BSTDataBufferHeapAllocator(const BSTDataBufferHeapAllocator&) = delete;
		BSTDataBufferHeapAllocator(BSTDataBufferHeapAllocator&&) noexcept = default;

		auto operator=(const BSTDataBufferHeapAllocator&) -> BSTDataBufferHeapAllocator& = delete;
		auto operator=(BSTDataBufferHeapAllocator&&) noexcept -> BSTDataBufferHeapAllocator& = default;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			return malloc<std::byte>(a_count);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<BSTDataBufferHeapAllocator>);
}
