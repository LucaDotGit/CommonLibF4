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
			std::uint32_t size : 24; // 0:00
			std::uint32_t id   : 8;	 // 0:24
		};
		static_assert(sizeof(Block) == 0x04);

		BSTDataBuffer() = default;

		~BSTDataBuffer() noexcept
		{
			free_buffer();
		}

		BSTDataBuffer(const BSTDataBuffer& a_rhs) = delete;

		BSTDataBuffer(BSTDataBuffer&& a_rhs) noexcept
			: _buffer(std::exchange(a_rhs._buffer, nullptr)),
			  _size(std::exchange(a_rhs._size, 0))
		{
		}

		BSTDataBuffer& operator=(const BSTDataBuffer& a_rhs) = delete;

		BSTDataBuffer& operator=(BSTDataBuffer&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			free_buffer();

			_buffer = std::exchange(a_rhs._buffer, nullptr);
			_size = std::exchange(a_rhs._size, 0);
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTDataBuffer);

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] reference at(size_type a_index) noexcept
		{
			REX::Assert(data() && a_index < _size);
			return data()[a_index];
		}

		[[nodiscard]] const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(data() && a_index < _size);
			return data()[a_index];
		}

		[[nodiscard]] reference front() noexcept { return at(0); }
		[[nodiscard]] const_reference front() const noexcept { return at(0); }

		[[nodiscard]] reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] pointer data() noexcept { return _buffer; }
		[[nodiscard]] const_pointer data() const noexcept { return _buffer; }

		[[nodiscard]] iterator begin() noexcept { return data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return begin() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return begin() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] bool has_block(std::uint8_t a_id) const noexcept
		{
			if (!_buffer || a_id == INVALID_ID) {
				return false;
			}

			auto* blocks = reinterpret_cast<Block*>(_buffer + _size);

			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				const auto& block = blocks[i];
				if (block.id == a_id) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]] std::pair<Block*, std::uint32_t> get_block(std::uint8_t a_id) noexcept
		{
			if (!_buffer || a_id == INVALID_ID) {
				return { nullptr, 0 };
			}

			auto* blocks = reinterpret_cast<Block*>(_buffer + _size);

			auto offset = static_cast<size_type>(0);
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				auto& block = blocks[i];
				if (block.id == a_id) {
					return { std::addressof(block), offset };
				}

				offset += block.size;
			}

			return { nullptr, 0 };
		}

		[[nodiscard]] std::pair<const Block*, std::uint32_t> get_block(std::uint8_t a_id) const noexcept
		{
			if (!_buffer || a_id == INVALID_ID) {
				return { nullptr, 0 };
			}

			const auto* blocks = reinterpret_cast<const Block*>(_buffer + _size);

			auto offset = static_cast<size_type>(0);
			for (auto i = static_cast<size_type>(0); i < MAX_SIZE; i++) {
				const auto& block = blocks[i];
				if (block.id == a_id) {
					return { std::addressof(block), offset };
				}

				offset += block.size;
			}

			return { nullptr, 0 };
		}

		template <class T>
		[[nodiscard]] std::span<T> get_buffer(std::uint8_t a_id) noexcept
		{
			auto&& [block, offset] = get_block(a_id);
			if (!block) {
				return {};
			}

			return { reinterpret_cast<T*>(_buffer + offset), block->size / sizeof(T) };
		}

		template <class T>
		[[nodiscard]] std::span<const T> get_buffer(std::uint8_t a_id) const noexcept
		{
			const auto&& [block, offset] = get_block(a_id);
			if (!block) {
				return {};
			}

			return { reinterpret_cast<const T*>(_buffer + offset), block->size / sizeof(T) };
		}

		void swap(BSTDataBuffer& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_buffer, a_other._buffer);
			std::swap(_size, a_other._size);
		}

	private:
		void free_buffer()
		{
			if (_buffer) {
				Allocator::deallocate_bytes(_buffer);
				_buffer = nullptr;
			}

			_size = 0;
		}

		// members
		value_type* _buffer{ nullptr }; // 00
		size_type _size{ 0 };			// 08
	};

	extern template class BSTDataBuffer<1>;
	extern template class BSTDataBuffer<2>;

	template <std::uint32_t N>
	void swap(BSTDataBuffer<N>& a_lhs, BSTDataBuffer<N>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	class BSTDataBufferHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;

		BSTDataBufferHeapAllocator() = default;
		~BSTDataBufferHeapAllocator() noexcept = default;

		BSTDataBufferHeapAllocator(const BSTDataBufferHeapAllocator&) = delete;
		BSTDataBufferHeapAllocator(BSTDataBufferHeapAllocator&&) noexcept = default;

		BSTDataBufferHeapAllocator& operator=(const BSTDataBufferHeapAllocator&) = delete;
		BSTDataBufferHeapAllocator& operator=(BSTDataBufferHeapAllocator&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_count) noexcept
		{
			auto* mem = calloc<std::byte>(a_count);
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<BSTDataBufferHeapAllocator>);
}
