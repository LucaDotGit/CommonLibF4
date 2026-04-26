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

		BSTArray() = default;

		~BSTArray()
		{
			if (capacity() == 0) {
				return;
			}

			clear();
			_allocator.deallocate_bytes(data());
			_allocator.data(nullptr);
			_allocator.capacity(0, 0);
		}

		explicit BSTArray(size_type a_count)
		{
			resize(a_count);
		}

		BSTArray(size_type a_count, const_reference a_value)
		{
			assign(a_count, a_value);
		}

		template <class InputIt>
		BSTArray(InputIt a_first, InputIt a_last)
			requires(std::derived_from<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>)
		{
			assign(a_first, a_last);
		}

		BSTArray(const BSTArray& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSTArray(BSTArray&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				reserve_exact(a_rhs.size());
				insert(end(), std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		BSTArray(std::initializer_list<T> a_ilist)
			: BSTArray(a_ilist.begin(), a_ilist.end())
		{
		}

		BSTArray& operator=(const BSTArray& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		BSTArray& operator=(BSTArray&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
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
				reserve_exact(a_rhs.size());
				insert(end(), std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTArray);

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] reference front() noexcept { return at(0); }
		[[nodiscard]] const_reference front() const noexcept { return at(0); }

		[[nodiscard]] reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] pointer data() noexcept { return static_cast<pointer>(_allocator.data()); }
		[[nodiscard]] const_pointer data() const noexcept { return static_cast<const_pointer>(_allocator.data()); }

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
		[[nodiscard]] size_type capacity() const noexcept { return _allocator.capacity(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		template <class ForwardIt>
		void assign(ForwardIt a_first, ForwardIt a_last)
		{
			auto out = begin();
			const auto out_last = end();
			for (; out != out_last && a_first != a_last; a_first++, out++) {
				*out = *a_first;
			}

			if (out != out_last) {
				erase(out, out_last);
			}

			if (a_first != a_last) {
				insert(end(), a_first, a_last);
			}
		}

		void assign(std::initializer_list<value_type> a_ilist)
		{
			assign(a_ilist.begin(), a_ilist.end());
		}

		template <class ForwardIt>
		iterator insert(const_iterator a_position, ForwardIt a_first, ForwardIt a_last)
			requires(std::derived_from<typename std::iterator_traits<ForwardIt>::iterator_category, std::forward_iterator_tag>)
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

		iterator insert(const_iterator a_position, const value_type& a_value)
		{
			return emplace(a_position, a_value);
		}

		iterator insert(const_iterator a_position, value_type&& a_value)
		{
			return emplace(a_position, std::move(a_value));
		}

		iterator insert(const_iterator a_position, std::initializer_list<value_type> a_ilist)
		{
			return insert(a_position, a_ilist.begin(), a_ilist.end());
		}

		template <class... Args>
		iterator emplace(const_iterator a_position, Args&&... a_args)
			requires(std::is_constructible_v<value_type, Args && ...>)
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

		iterator erase(const_iterator a_first, const_iterator a_last)
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

		iterator erase(const_iterator a_position)
		{
			return erase(a_position, std::next(a_position));
		}

		template <class... Args>
		reference emplace_back(Args&&... a_args)
			requires(std::is_constructible_v<value_type, Args && ...>)
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

		void reserve(size_type a_capacity)
		{
			if (a_capacity > capacity()) {
				reserve_exact(a_capacity);
			}
		}

		void resize(size_type a_count)
		{
			resize_impl(a_count, nullptr);
		}

		void resize(size_type a_count, const value_type& a_value)
		{
			resize_impl(a_count, std::addressof(a_value));
		}

		void shrink_to_fit()
		{
			reserve_exact(size());
		}

		void clear()
		{
			erase(begin(), end());
		}

		void swap(BSTArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap_ranges(begin(), end(), a_other.begin());
			std::swap(_allocator, a_other._allocator);
			std::swap(_size, a_other._size);
		}

	private:
		template <class, class>
		friend class BSTArray;

		[[nodiscard]] iterator decay_iterator(const_iterator a_iter) noexcept
		{
			return const_cast<pointer>(std::addressof(*a_iter));
		}

		void reserve_auto(size_type a_capacity)
		{
			if (a_capacity > capacity()) {
				const auto grow = std::max(a_capacity, capacity() * 2);
				reserve_exact(grow);
			}
		}

		void reserve_exact(size_type a_capacity)
		{
			REX::Assert(a_capacity >= size());
			if (a_capacity == capacity()) {
				return;
			}

			auto* newData = static_cast<pointer>(_allocator.allocate_bytes(a_capacity * sizeof(value_type)));
			auto* oldData = data();

			if (newData == oldData) {
				return;
			}

			std::uninitialized_move_n(oldData, size(), newData);
			std::destroy_n(oldData, size());

			_allocator.deallocate_bytes(oldData);
			_allocator.data(newData);
			_allocator.capacity(a_capacity, a_capacity * sizeof(value_type));
		}

		void resize_impl(size_type a_count, const value_type* a_value)
		{
			if (a_count == size()) {
				return;
			}

			if (a_count < size()) {
				erase(begin() + a_count, end());
				return;
			}

			reserve_auto(a_count);
			auto range = std::span<value_type>{ data() + _size, a_count - _size };

			if (a_value) {
				std::uninitialized_fill(range.begin(), range.end(), *a_value);
			}
			else {
				std::uninitialized_default_construct(
					range.begin(),
					range.end());
			}

			_size = a_count;
		}

		// members
		allocator_type _allocator; // 00
		size_type _size{ 0 };	   // ??
	};

	template <class T, class Allocator>
	void swap(BSTArray<T, Allocator>& a_lhs, BSTArray<T, Allocator>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	class BSTArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTArrayHeapAllocator() = default;
		~BSTArrayHeapAllocator() noexcept = default;

		BSTArrayHeapAllocator(const BSTArrayHeapAllocator&) = delete;

		BSTArrayHeapAllocator(BSTArrayHeapAllocator&& a_rhs) noexcept
			: _data(std::exchange(a_rhs._data, nullptr)),
			  _capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		BSTArrayHeapAllocator& operator=(const BSTArrayHeapAllocator&) = delete;

		BSTArrayHeapAllocator& operator=(BSTArrayHeapAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]] void* data() noexcept { return _data; }
		[[nodiscard]] const void* data() const noexcept { return _data; }
		void data(void* a_data) noexcept { _data = static_cast<std::byte*>(a_data); }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		void capacity(size_type a_capacity, [[maybe_unused]] size_type a_bytes) noexcept { _capacity = a_capacity; }

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

	private:
		// members
		std::byte* _data{ nullptr }; // 00
		size_type _capacity{ 0 };	 // 08
	};

	template <std::uint32_t Align>
	class BSTAlignedHeapArrayAllocator
	{
	public:
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Align);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTAlignedHeapArrayAllocator() = default;
		~BSTAlignedHeapArrayAllocator() noexcept = default;

		BSTAlignedHeapArrayAllocator(const BSTAlignedHeapArrayAllocator&) = delete;

		BSTAlignedHeapArrayAllocator(BSTAlignedHeapArrayAllocator&& a_rhs) noexcept
			: _data(std::exchange(a_rhs._data, nullptr)),
			  _capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		BSTAlignedHeapArrayAllocator& operator=(const BSTAlignedHeapArrayAllocator& a_rhs) = delete;

		BSTAlignedHeapArrayAllocator& operator=(BSTAlignedHeapArrayAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]] void* data() noexcept { return _data; }
		[[nodiscard]] const void* data() const noexcept { return _data; }
		void data(void* a_data) noexcept { _data = static_cast<std::byte*>(a_data); }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		void capacity(size_type a_capacity, [[maybe_unused]] size_type a_bytes) noexcept { _capacity = a_capacity; }

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_count) noexcept
		{
			auto* mem = aligned_alloc(a_count, ALIGNMENT_SIZE);
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			aligned_free(a_ptr);
		}

	private:
		std::byte* _data{ nullptr }; // 00
		size_type _capacity{ 0 };	 // 08
	};
	static_assert(sizeof(BSTAlignedHeapArrayAllocator<0x08>) == 0x10);

	class BSScrapArrayAllocator
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSScrapArrayAllocator() = default; // The allocator is not initialized in the constructor, for some reason.
		~BSScrapArrayAllocator() noexcept = default;

		BSScrapArrayAllocator(const BSScrapArrayAllocator&) = delete;

		BSScrapArrayAllocator(BSScrapArrayAllocator&& a_rhs) noexcept
			: _allocator(std::exchange(a_rhs._allocator, nullptr)),
			  _data(std::exchange(a_rhs._data, nullptr)),
			  _capacity(std::exchange(a_rhs._capacity, 0))
		{
		}

		BSScrapArrayAllocator& operator=(const BSScrapArrayAllocator&) = delete;

		BSScrapArrayAllocator& operator=(BSScrapArrayAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_allocator = std::exchange(a_rhs._allocator, nullptr);
			_data = std::exchange(a_rhs._data, nullptr);
			_capacity = std::exchange(a_rhs._capacity, 0);
			return *this;
		}

		[[nodiscard]] void* data() noexcept { return _data; }
		[[nodiscard]] const void* data() const noexcept { return _data; }
		void data(void* a_data) noexcept { _data = static_cast<std::byte*>(a_data); }

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		void capacity(size_type a_capacity, [[maybe_unused]] size_type a_bytes) noexcept { _capacity = a_capacity; }

		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* allocate_bytes(size_type a_count) noexcept
		{
			if (!_allocator) {
				_allocator = MemoryManager::GetSingleton().GetThreadScrapHeap();
				REX::Ensure(_allocator != nullptr);
			}

			auto* mem = _allocator->Allocate(a_count, SCRAP_HEAP_ALIGNMENT);
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			REL::MemWriteZero(mem, a_count);
			return mem;
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			if (!_allocator) {
				_allocator = MemoryManager::GetSingleton().GetThreadScrapHeap();
				REX::Ensure(_allocator != nullptr);
			}

			_allocator->Deallocate(a_ptr);
		}

	private:
		// members
		ScrapHeap* _allocator{ nullptr }; // 00
		std::byte* _data{ nullptr };	  // 08
		size_type _capacity{ 0 };		  // 10
	};
	static_assert(sizeof(BSScrapArrayAllocator) == 0x18);

	template <std::uint32_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTSmallArrayHeapAllocator() = default;
		~BSTSmallArrayHeapAllocator() noexcept = default;

		BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator&) = delete;

		BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&& a_rhs) noexcept
			: _local(a_rhs._local),
			  _capacity(a_rhs._capacity)
		{
			if (_local) {
				std::copy(std::begin(a_rhs._stack), std::end(a_rhs._stack), std::begin(_stack));
			}
			else {
				_heap = std::exchange(a_rhs._heap, nullptr);
			}
		}

		BSTSmallArrayHeapAllocator& operator=(const BSTSmallArrayHeapAllocator&) = delete;

		BSTSmallArrayHeapAllocator& operator=(BSTSmallArrayHeapAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_local = a_rhs._local;
			_capacity = a_rhs._capacity;

			if (_local) {
				std::copy(std::begin(a_rhs._stack), std::end(a_rhs._stack), std::begin(_stack));
			}
			else {
				_heap = std::exchange(a_rhs._heap, nullptr);
			}

			return *this;
		}

		[[nodiscard]] void* data() noexcept { return _local ? _stack.data() : _heap; }
		[[nodiscard]] const void* data() const noexcept { return _local ? _stack.data() : _heap; }

		void data(void* a_data) noexcept
		{
			if (a_data != _stack.data()) {
				_heap = static_cast<std::byte*>(a_data);
			}
		}

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }

		void capacity(size_type a_capacity, size_type a_bytes) noexcept
		{
			_local = a_bytes <= MAX_SIZE;
			_capacity = a_capacity;
		}

		[[nodiscard]] __declspec(allocator) void* allocate_bytes(size_type a_count) noexcept
		{
			if (a_count <= MAX_SIZE) {
				return _stack.data();
			}

			auto* mem = calloc<std::byte>(a_count);
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (a_ptr != _stack.data()) {
				free(a_ptr);
			}
		}

	private:
		// members
		size_type _capacity : 31 { 0 }; // 00:00
		size_type _local	: 1 { 0 };	// 00:31
		union
		{
			std::byte* _heap{ nullptr };
			std::array<std::byte, MAX_SIZE> _stack;
		}; // 08
	};
	static_assert(sizeof(BSTSmallArrayHeapAllocator<0x08>) == 0x10);

	template <class T, std::uint32_t Align = alignof(T)>
	using BSTAlignedArray = BSTArray<T, BSTAlignedHeapArrayAllocator<Align>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSScrapArrayAllocator>;

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

		constexpr BSStaticArray& operator=(const BSStaticArray&) noexcept = default;
		constexpr BSStaticArray& operator=(BSStaticArray&&) noexcept = default;

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] constexpr reference front() noexcept { return at(0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return at(0); }

		[[nodiscard]] constexpr reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data; }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data; }

		[[nodiscard]] constexpr iterator begin() noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return empty() ? nullptr : data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return empty() ? nullptr : data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		constexpr void swap(BSStaticArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap_ranges(begin(), end(), a_other.begin());
			std::swap(_size, a_other._size);
		}

	private:
		// members
		pointer _data{ nullptr }; // 00
		std::uint32_t _size{ 0 }; // 08
	};
	static_assert(sizeof(BSStaticArray<std::any>) == 0x10);

	template <class T>
	void swap(BSStaticArray<T>& a_lhs, BSStaticArray<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

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

		BSTSmallSharedArray() = default;

		~BSTSmallSharedArray()
		{
			if (size() > 1) {
				free(heap);
			}
		}

		BSTSmallSharedArray(const BSTSmallSharedArray&) = delete;

		BSTSmallSharedArray(BSTSmallSharedArray&& a_rhs) noexcept
			: _size(std::exchange(a_rhs._size, 0))
		{
			if (is_heap()) {
				heap = std::exchange(a_rhs.heap, nullptr);
			}
			else {
				local = a_rhs.local;
			}
		}

		BSTSmallSharedArray& operator=(const BSTSmallSharedArray&) = delete;

		BSTSmallSharedArray& operator=(BSTSmallSharedArray&& a_rhs) noexcept
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

		[[nodiscard]] reference operator[](size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] pointer data() noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] const_pointer data() const noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] iterator begin() noexcept { return data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return data() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool is_local() const noexcept { return !is_heap(); }
		[[nodiscard]] bool is_heap() const noexcept { return size() > 1; }

		void swap(BSTSmallSharedArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap_ranges(begin(), end(), a_other.begin());
			std::swap(_size, a_other._size);
		}

	private:
		// members
		std::uint32_t _size{ 0 }; // 00
		union
		{
			pointer heap{ 0 };
			value_type local;
		}; // 08
	};
	static_assert(sizeof(BSTSmallSharedArray<std::uint32_t>) == 0x10);

	template <class T>
	void swap(BSTSmallSharedArray<T>& a_lhs, BSTSmallSharedArray<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
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
