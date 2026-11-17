#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSTArrayHeapAllocator;

	template <class T, class Allocator = BSTArrayHeapAllocator>
	class BSTArray
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
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		BSTArray() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		~BSTArray() noexcept
		{
			if (capacity() == 0) {
				return;
			}

			clear();

			_allocator.deallocate_bytes(data());
			_allocator.set_data(nullptr);
			_allocator.set_capacity(0, 0);
		}

		explicit BSTArray(size_type a_count)
		{
			resize(a_count);
		}

		BSTArray(size_type a_count, const_reference a_value)
		{
			assign(a_count, a_value);
		}

		template <std::input_iterator InputIt>
		BSTArray(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		BSTArray(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		BSTArray(std::initializer_list<value_type> a_initList) :
			BSTArray{a_initList.begin(), a_initList.end()}
		{
		}

		BSTArray(const BSTArray& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSTArray(BSTArray&& a_rhs)
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>)
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				assign(end(), std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		auto operator=(std::initializer_list<value_type> a_rhs) -> BSTArray&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(const BSTArray& a_rhs) -> BSTArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(BSTArray&& a_rhs)
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>)
				-> BSTArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();

			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				assign(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTArray);

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
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
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
			return static_cast<pointer>(_allocator.data());
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return static_cast<const_pointer>(_allocator.data());
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
		auto capacity() const noexcept -> size_type
		{
			return _allocator.capacity();
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

		template <std::input_iterator InputIt>
		void assign(InputIt a_first, InputIt a_last)
		{
			auto out = begin();
			const auto outLast = end();

			for (; out != outLast && a_first != a_last; a_first++, out++) {
				*out = *a_first;
			}

			if (out != outLast) {
				erase(out, outLast);
			}

			if (a_first != a_last) {
				insert(end(), a_first, a_last);
			}
		}

		void assign(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void assign_range(Range&& a_range)
		{
			assign(std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void append_range(Range&& a_range)
		{
			insert(end(), std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <std::input_iterator InputIt>
		auto insert(const_iterator a_position, InputIt a_first, InputIt a_last) -> iterator
		{
			const auto distance = static_cast<size_type>(std::distance(a_first, a_last));
			if (distance == 0) {
				return decay_iterator(a_position);
			}

			const auto pos = static_cast<size_type>(std::distance(cbegin(), a_position));
			resize(size() + distance);

			const auto it = begin() + pos;
			std::move_backward(it, it + distance, end());
			std::copy(a_first, a_last, it);
			return it;
		}

		auto insert(const_iterator a_position, const value_type& a_value) -> iterator
		{
			return emplace(a_position, a_value);
		}

		auto insert(const_iterator a_position, value_type&& a_value) -> iterator
		{
			return emplace(a_position, std::move(a_value));
		}

		auto insert(const_iterator a_position, std::initializer_list<value_type> a_initList) -> iterator
		{
			return insert(a_position, a_initList.begin(), a_initList.end());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		constexpr void insert_range(size_type a_position, Range&& a_range)
		{
			insert(a_position, std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <class... Args>
		auto emplace(const_iterator a_position, Args&&... a_args) -> iterator
			requires(std::is_constructible_v<value_type, Args&&...>)
		{
			const auto pos = static_cast<size_type>(std::distance(cbegin(), a_position));
			if (pos < size()) {
				emplace_back(std::move(back()));
				std::move_backward(begin() + pos, end() - 2, end() - 1);
			}
			else {
				reserve_auto(size() + 1);
				_size += 1;
			}

			std::construct_at(data() + pos, std::forward<Args>(a_args)...);
			return begin() + pos;
		}

		auto erase(const_iterator a_first, const_iterator a_last) -> iterator
		{
			const auto first = decay_iterator(a_first);
			const auto last = decay_iterator(a_last);
			const auto distance = static_cast<size_type>(std::distance(first, last));

			if (distance == 0) {
				return last;
			}

			REX::Assert(distance <= size());
			std::move(last, end(), first);
			std::destroy(end() - distance, end());
			_size -= distance;
			return end();
		}

		auto erase(const_iterator a_position) -> iterator
		{
			return erase(a_position, std::next(a_position));
		}

		template <class... Args>
		auto emplace_back(Args&&... a_args) -> reference
			requires(std::is_constructible_v<value_type, Args&&...>)
		{
			return *emplace(end(), std::forward<Args>(a_args)...);
		}

		void push_back(const value_type& a_value)
		{
			emplace_back(a_value);
		}

		void push_back(value_type&& a_value)
		{
			emplace_back(std::move(a_value));
		}

		void pop_back()
		{
			erase(std::prev(end()));
		}

		void reserve(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			reserve_exact(a_newCapacity);
		}

		void resize(size_type a_newSize)
		{
			resize_impl(a_newSize, nullptr);
		}

		void resize(size_type a_newSize, const value_type& a_value)
		{
			resize_impl(a_newSize, std::addressof(a_value));
		}

		void shrink_to_fit()
		{
			reserve_exact(size());
		}

		void clear() noexcept
		{
			erase(begin(), end());
		}

		void swap(BSTArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_size, a_other._size);
		}

	private:
		template <class, class>
		friend class BSTArray;

		[[nodiscard]]
		auto decay_iterator(const_iterator a_it) noexcept -> iterator
		{
			return const_cast<pointer>(std::addressof(*a_it));
		}

		void reserve_auto(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			const auto grow = std::max(a_newCapacity, capacity() * 2);
			reserve_exact(grow);
		}

		void reserve_exact(size_type a_newCapacity)
		{
			REX::Assert(a_newCapacity >= size());
			if (a_newCapacity == capacity()) {
				return;
			}

			auto* newData = static_cast<pointer>(_allocator.allocate_bytes(a_newCapacity * sizeof(value_type)));
			if (!newData) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			auto* oldData = data();
			if (newData == oldData) {
				return;
			}

			std::uninitialized_move_n(oldData, size(), newData);
			std::destroy_n(oldData, size());

			_allocator.deallocate_bytes(oldData);
			_allocator.set_data(newData);
			_allocator.set_capacity(a_newCapacity, a_newCapacity * sizeof(value_type));
		}

		void resize_impl(size_type a_newSize, const value_type* a_value)
		{
			if (a_newSize == size()) {
				return;
			}

			if (a_newSize < size()) {
				erase(begin() + a_newSize, end());
				return;
			}

			reserve_auto(a_newSize);

			auto range = std::span<value_type>{data() + size(), a_newSize - size()};

			if (a_value) {
				std::uninitialized_fill(range.begin(), range.end(), *a_value);
			}
			else {
				std::uninitialized_default_construct(range.begin(), range.end());
			}

			_size = a_newSize;
		}

		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		allocator_type _allocator{}; // 0x00
		size_type _size{0};			 // 0x??
	};

	class BSTArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTArrayHeapAllocator() noexcept = default;
		~BSTArrayHeapAllocator() noexcept = default;

		BSTArrayHeapAllocator(const BSTArrayHeapAllocator&) = delete;

		BSTArrayHeapAllocator(BSTArrayHeapAllocator&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr)),
			_capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		auto operator=(const BSTArrayHeapAllocator&) -> BSTArrayHeapAllocator& = delete;

		auto operator=(BSTArrayHeapAllocator&& a_rhs) noexcept -> BSTArrayHeapAllocator&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]]
		auto data() noexcept -> void*
		{
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const void*
		{
			return _data;
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		void set_data(void* a_data) noexcept
		{
			_data = static_cast<std::byte*>(a_data);
		}

		void set_capacity(size_type a_newCapacity, [[maybe_unused]] size_type a_byteSize) noexcept
		{
			_capacity = a_newCapacity;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			return malloc<std::byte>(a_count);
		}

		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}

	private:
		// members
		std::byte* _data{nullptr}; // 0x00
		size_type _capacity{0};	   // 0x08
	};

	template <std::uint32_t Alignment>
	class BSTArrayAlignedAllocator
	{
	public:
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Alignment);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTArrayAlignedAllocator() noexcept = default;
		~BSTArrayAlignedAllocator() noexcept = default;

		BSTArrayAlignedAllocator(const BSTArrayAlignedAllocator&) = delete;

		BSTArrayAlignedAllocator(BSTArrayAlignedAllocator&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr)),
			_capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		auto operator=(const BSTArrayAlignedAllocator& a_rhs) -> BSTArrayAlignedAllocator& = delete;

		auto operator=(BSTArrayAlignedAllocator&& a_rhs) noexcept -> BSTArrayAlignedAllocator&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]]
		auto data() noexcept -> void*
		{
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const void*
		{
			return _data;
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		void set_data(void* a_data) noexcept
		{
			_data = static_cast<std::byte*>(a_data);
		}

		void set_capacity(size_type a_newCapacity, [[maybe_unused]] size_type a_byteSize) noexcept
		{
			_capacity = a_newCapacity;
		}

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			return aligned_alloc(a_count, ALIGNMENT_SIZE);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			aligned_free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)

	private:
		std::byte* _data{nullptr}; // 0x00
		size_type _capacity{0};	   // 0x08
	};

	static_assert(sizeof(BSTArrayAlignedAllocator<0x08>) == 0x10);

	class BSTArrayScrapAllocator
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		// The allocator is not initialized in the constructor, for some reason.

		BSTArrayScrapAllocator() noexcept = default;
		~BSTArrayScrapAllocator() noexcept = default;

		BSTArrayScrapAllocator(const BSTArrayScrapAllocator&) = delete;

		BSTArrayScrapAllocator(BSTArrayScrapAllocator&& a_rhs) noexcept :
			_allocator(std::exchange(a_rhs._allocator, nullptr)),
			_data(std::exchange(a_rhs._data, nullptr)),
			_capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		auto operator=(const BSTArrayScrapAllocator&) -> BSTArrayScrapAllocator& = delete;

		auto operator=(BSTArrayScrapAllocator&& a_rhs) noexcept -> BSTArrayScrapAllocator&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_allocator = std::exchange(a_rhs._allocator, nullptr);
			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]]
		auto data() noexcept -> void*
		{
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const void*
		{
			return _data;
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		void set_data(void* a_data) noexcept
		{
			_data = static_cast<std::byte*>(a_data);
		}

		void set_capacity(size_type a_newCapacity, [[maybe_unused]] size_type a_byteSize) noexcept
		{
			_capacity = a_newCapacity;
		}

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			if (!_allocator) {
				_allocator = MemoryManager::GetSingleton().GetThreadScrapHeap();
			}

			REX::Assert(_allocator != nullptr);
			return _allocator->CountedAllocate<std::byte>(a_count, SCRAP_HEAP_ALIGNMENT);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			if (!_allocator) {
				_allocator = MemoryManager::GetSingleton().GetThreadScrapHeap();
			}

			REX::Assert(_allocator != nullptr);
			_allocator->Deallocate(a_ptr);
		}

	private:
		// members
		ScrapHeap* _allocator{nullptr}; // 0x00
		std::byte* _data{nullptr};		// 0x08
		size_type _capacity{0};			// 0x10
	};

	static_assert(sizeof(BSTArrayScrapAllocator) == 0x18);

	template <std::uint32_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTSmallArrayHeapAllocator() noexcept = default;
		~BSTSmallArrayHeapAllocator() noexcept = default;

		BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator&) = delete;
		BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&&) = delete;

		auto operator=(const BSTSmallArrayHeapAllocator&) -> BSTSmallArrayHeapAllocator& = delete;
		auto operator=(BSTSmallArrayHeapAllocator&&) -> BSTSmallArrayHeapAllocator& = delete;

		[[nodiscard]]
		auto data() noexcept -> void*
		{
			return _local ? _buffer.stack.data() : _buffer.heap;
		}

		[[nodiscard]]
		auto data() const noexcept -> const void*
		{
			return _local ? _buffer.stack.data() : _buffer.heap;
		}

		[[nodiscard]]
		auto is_local() const noexcept -> bool
		{
			return _local;
		}

		[[nodiscard]]
		auto is_heap() const noexcept -> bool
		{
			return !is_local();
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		void set_data(void* a_data) noexcept
		{
			if (a_data != _buffer.stack.data()) {
				_buffer.heap = static_cast<std::byte*>(a_data);
			}
		}

		void set_capacity(size_type a_newCapacity, size_type a_byteSize) noexcept
		{
			_capacity = a_newCapacity;
			_local = a_byteSize <= MAX_SIZE;
		}

		[[nodiscard]]
		__declspec(allocator) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			if (a_count <= MAX_SIZE) {
				return _buffer.stack.data();
			}

			return malloc<std::byte>(a_count);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (a_ptr != _buffer.stack.data()) {
				free(a_ptr);
			}
		}

	private:
		// members
		size_type _capacity : 31 {MAX_SIZE};					// 0x00:00
		size_type _local	: 1 {static_cast<size_type>(true)}; // 0x00:31

		union
		{
		public:
			std::byte* heap;
			std::array<std::byte, MAX_SIZE> stack{};
		} _buffer; // 0x08
	};

	static_assert(sizeof(BSTSmallArrayHeapAllocator<0x08>) == 0x10);

	template <class T, std::uint32_t Alignment = alignof(T)>
	using BSTAlignedArray = BSTArray<T, BSTArrayAlignedAllocator<Alignment>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSTArrayScrapAllocator>;

	template <class T, std::uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<sizeof(T) * N>>;

	template <class T>
	class BSStaticArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		constexpr BSStaticArray() noexcept = default;
		constexpr ~BSStaticArray() noexcept = default;

		constexpr BSStaticArray(const BSStaticArray&) noexcept = default;
		constexpr BSStaticArray(BSStaticArray&&) noexcept = default;

		constexpr auto operator=(const BSStaticArray&) noexcept -> BSStaticArray& = default;
		constexpr auto operator=(BSStaticArray&&) noexcept -> BSStaticArray& = default;

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
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
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

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return empty() ? nullptr : data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return empty() ? nullptr : data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return empty() ? nullptr : data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return empty() ? nullptr : data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return _size;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return std::numeric_limits<size_type>::max();
		}

		constexpr void swap(BSStaticArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
			std::swap(_size, a_other._size);
		}

	private:
		// members
		pointer _data{nullptr}; // 0x00
		std::uint32_t _size{0}; // 0x08
	};

	static_assert(sizeof(BSStaticArray<std::any>) == 0x10);

	template <class T>
	class BSTSmallSharedArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		BSTSmallSharedArray() noexcept = default;

		~BSTSmallSharedArray() noexcept
		{
			if (size() > 1) {
				free(heap);
			}
		}

		BSTSmallSharedArray(const BSTSmallSharedArray&) = delete;

		BSTSmallSharedArray(BSTSmallSharedArray&& a_rhs) noexcept :
			_size(std::exchange(a_rhs._size, 0))
		{
			if (is_heap()) {
				heap = std::exchange(a_rhs.heap, nullptr);
			}
			else {
				local = a_rhs.local;
			}
		}

		auto operator=(const BSTSmallSharedArray&) -> BSTSmallSharedArray& = delete;

		auto operator=(BSTSmallSharedArray&& a_rhs) noexcept -> BSTSmallSharedArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			if (is_heap()) {
				free(heap);
			}

			_size = std::exchange(a_rhs._size, 0);

			if (is_heap()) {
				heap = std::exchange(a_rhs.heap, nullptr);
			}
			else {
				local = a_rhs.local;
			}

			return *this;
		}

		[[nodiscard]]
		auto operator[](size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		auto operator[](size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return is_heap() ? heap : std::addressof(local);
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return is_heap() ? heap : std::addressof(local);
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
			return data() + size();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return size() == 0;
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
		auto is_local() const noexcept -> bool
		{
			return size() <= 1;
		}

		[[nodiscard]]
		auto is_heap() const noexcept -> bool
		{
			return !is_local();
		}

		void swap(BSTSmallSharedArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			if (is_heap()) {
				std::swap(heap, a_other.heap);
			}
			else {
				std::swap(local, a_other.local);
			}

			std::swap(_size, a_other._size);
		}

	private:
		// members
		std::uint32_t _size{0}; // 0x00

		union
		{
		public:
			pointer heap{nullptr};
			value_type local;
		}; // 0x08
	};

	static_assert(sizeof(BSTSmallSharedArray<std::uint32_t>) == 0x10);
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <class T, class Allocator>
	struct script_traits<BSTArray<T, Allocator>>
	{
		using is_array = std::true_type;
	};
}
