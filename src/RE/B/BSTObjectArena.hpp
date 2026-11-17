#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSTObjectArenaHeapAllocator;

	inline constexpr auto DEFAULT_OBJECT_ARENA_PAGE_SIZE = 0x20;

	template <class T, class Allocator = BSTObjectArenaHeapAllocator, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	class BSTObjectArena
	{
	private:
		using super = Allocator;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		class Page
		{
		public:
			[[nodiscard]]
			auto begin() noexcept -> std::byte*
			{
				return buffer.data();
			}

			[[nodiscard]]
			auto begin() const noexcept -> const std::byte*
			{
				return buffer.data();
			}

			[[nodiscard]]
			auto cbegin() const noexcept -> const std::byte*
			{
				return buffer.data();
			}

			[[nodiscard]]
			auto end() noexcept -> std::byte*
			{
				return buffer.data() + buffer.size();
			}

			[[nodiscard]]
			auto end() const noexcept -> const std::byte*
			{
				return buffer.data() + buffer.size();
			}

			[[nodiscard]]
			auto cend() const noexcept -> const std::byte*
			{
				return buffer.data() + buffer.size();
			}

			// members
			std::array<std::byte, sizeof(value_type) * N> buffer{static_cast<std::byte>(0)}; // 0x00
			Page* next{nullptr};															 // 0x??
		};

		template <class U>
		class iterator_base
		{
		public:
			using value_type = std::remove_const_t<U>;
			using difference_type = std::int32_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_proxy(a_rhs._proxy),
				_first(a_rhs._first),
				_last(a_rhs._last)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(const iterator_base<V>& a_rhs) noexcept -> iterator_base&
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_proxy = a_rhs._proxy;
				_first = a_rhs._first;
				_last = a_rhs._last;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() const noexcept -> reference
			{
				REX::Assert(good());
				return *std::launder(reinterpret_cast<pointer>(_first));
			}

			[[nodiscard]]
			auto operator->() const noexcept -> pointer
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]]
			auto operator==(const iterator_base<V>& a_rhs) const noexcept -> bool
			{
				REX::Assert(_last == a_rhs._last);

				if (_first == a_rhs._first) {
					REX::Assert(_proxy == a_rhs._proxy);
					return true;
				}

				return false;
			}

			auto operator++() noexcept -> iterator_base&
			{
				REX::Assert(good());

				_first += sizeof(value_type);
				if (_first == _proxy->cend() && _first != _last) {
					_proxy = _proxy->next;
					_first = _proxy->begin();
				}

				return *this;
			}

			auto operator++(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		private:
			template <class, class, std::uint32_t>
			friend class BSTObjectArena;

			template <class>
			friend class iterator_base;

			iterator_base(Page* a_proxy, std::byte* a_first, std::byte* a_last) noexcept :
				_proxy(a_proxy),
				_first(a_first),
				_last(a_last)
			{
			}

			[[nodiscard]]
			auto good() const noexcept -> bool
			{
				return _proxy != nullptr &&
					   _first != nullptr &&
					   _last != nullptr &&
					   _first != _last &&
					   _first != _proxy->cend();
			}

			Page* _proxy{nullptr};
			std::byte* _first{nullptr};
			std::byte* _last{nullptr};
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		BSTObjectArena() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		~BSTObjectArena() noexcept
		{
			clear();
			free_resources();

			_tail = nullptr;
			_end = nullptr;
			_begin = nullptr;
		}

		template <std::input_iterator InputIt>
		BSTObjectArena(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		BSTObjectArena(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		BSTObjectArena(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		BSTObjectArena(const BSTObjectArena& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSTObjectArena(BSTObjectArena&& a_rhs) noexcept
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator.operator=(std::move(a_rhs));
				_head = std::exchange(a_rhs._head, nullptr);
				_next = std::exchange(a_rhs._next, std::addressof(_head));
				_tail = std::exchange(a_rhs._tail, nullptr);
				_free = std::exchange(a_rhs._free, nullptr);
				_end = std::exchange(a_rhs._end, nullptr);
				_begin = std::exchange(a_rhs._begin, nullptr);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				assign(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		auto operator=(std::initializer_list<value_type> a_rhs) -> BSTObjectArena&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(const BSTObjectArena& a_rhs) -> BSTObjectArena&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(BSTObjectArena&& a_rhs) noexcept -> BSTObjectArena&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();

			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator.operator=(std::move(a_rhs));
				_head = std::exchange(a_rhs._head, nullptr);
				_next = std::exchange(a_rhs._next, std::addressof(_head));
				_tail = std::exchange(a_rhs._tail, nullptr);
				_free = std::exchange(a_rhs._free, nullptr);
				_end = std::exchange(a_rhs._end, nullptr);
				_begin = std::exchange(a_rhs._begin, nullptr);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				assign(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTObjectArena);

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
			return empty() ? nullptr : std::launder(reinterpret_cast<pointer>(_begin));
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return empty() ? nullptr : std::launder(reinterpret_cast<const_pointer>(_begin));
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return make_iterator<iterator>();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>();
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
			return N;
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
			clear();

			for (; a_first != a_last; ++a_first) {
				emplace_back(*a_first);
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

		auto push_back(const value_type& a_value) -> iterator
		{
			return emplace(a_value);
		}

		auto push_back(value_type&& a_value) -> iterator
		{
			return emplace(std::move(a_value));
		}

		template <class... Args>
		auto emplace_back(Args&&... a_args) -> iterator
		{
			auto buffer = allocate_buffer();
			std::construct_at(reinterpret_cast<value_type*>(buffer.data()), std::forward<Args>(a_args)...);
			return iterator{_tail, buffer.data(), _end};
		}

		void clear() noexcept
		{
			for (; _size > 0; _size--) {
				std::destroy_at(reinterpret_cast<pointer>(_begin));

				_begin += sizeof(value_type);
				if (_begin != _head->cend()) {
					continue;
				}

				if (_head == _tail) { // reached the end
					_next = std::addressof(_head);
					_tail = nullptr;
					_end = nullptr;
					_begin = nullptr;
				}
				else { // update position to next page
					_begin = _head->next->begin();
				}

				// move head into free list, grab next page
				_head = std::exchange(_head->next, std::exchange(_free, _head));
			}

			REX::Assert(empty());
		}

		void swap(BSTObjectArena& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_head, a_other._head);
			std::swap(_next, a_other._next);
			std::swap(_tail, a_other._tail);
			std::swap(_free, a_other._free);
			std::swap(_end, a_other._end);
			std::swap(_begin, a_other._begin);
			std::swap(_size, a_other._size);
		}

	private:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It(_head, _begin, _end);
		}

		[[nodiscard]]
		auto allocate_buffer() -> std::span<std::byte>
		{
			if (!_tail || _end == _tail->cend()) {
				auto* page = _free ? std::exchange(_free, _free->next) : // pull from free list
									 std::construct_at<Page>(_allocator.allocate_bytes(sizeof(Page))); // go to heap

				if (page) {
					page->next = nullptr;
					*_next = page;
					_next = std::addressof(page->next);
				}

				_tail = page;
				_end = page->buffer;

				if (_begin == nullptr) {
					_begin = page->buffer;
				}
			}

			_size++;
			auto* buffer = _end;
			_end += sizeof(value_type);
			return std::span{buffer, sizeof(value_type)};
		}

		void free_resources() noexcept
		{
			const auto doDelete = [this](Page*& a_page) noexcept -> void {
				while (a_page != nullptr) {
					auto* next = a_page->next;
					_allocator.deallocate_bytes(a_page);
					a_page = next;
				}
			};

			doDelete(_head);
			doDelete(_free);
		}

		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		Allocator _allocator{};				 // 0x00
		Page* _head{nullptr};				 // 0x00 - head of active pages
		Page** _next{std::addressof(_head)}; // 0x?? - used to update next ptr when appending pages
		Page* _tail{nullptr};				 // 0x?? - tail of active pages
		Page* _free{nullptr};				 // 0x?? - local free list
		std::byte* _end{nullptr};			 // 0x?? - ptr to end of active lifetime elements
		std::byte* _begin{nullptr};			 // 0x?? - ptr to beginning of active lifetime elements
		size_type _size{0};					 // 0x??
	};

	class BSTObjectArenaHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTObjectArenaHeapAllocator() noexcept = default;
		~BSTObjectArenaHeapAllocator() noexcept = default;

		BSTObjectArenaHeapAllocator(const BSTObjectArenaHeapAllocator&) = delete;
		BSTObjectArenaHeapAllocator(BSTObjectArenaHeapAllocator&&) noexcept = default;

		auto operator=(const BSTObjectArenaHeapAllocator&) -> BSTObjectArenaHeapAllocator& = delete;
		auto operator=(BSTObjectArenaHeapAllocator&&) noexcept -> BSTObjectArenaHeapAllocator& = default;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			return malloc<std::byte>(a_count);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<BSTObjectArenaHeapAllocator>);

	template <std::uint32_t Alignment>
	class BSTObjectArenaAlignedAllocator
	{
	public:
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Alignment);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTObjectArenaAlignedAllocator() = default;
		~BSTObjectArenaAlignedAllocator() noexcept = default;

		BSTObjectArenaAlignedAllocator(const BSTObjectArenaAlignedAllocator&) = delete;
		BSTObjectArenaAlignedAllocator(BSTObjectArenaAlignedAllocator&&) noexcept = default;

		auto operator=(const BSTObjectArenaAlignedAllocator&) -> BSTObjectArenaAlignedAllocator& = delete;
		auto operator=(BSTObjectArenaAlignedAllocator&&) noexcept -> BSTObjectArenaAlignedAllocator& = default;

		// NOLINTBEGIN(readability-convert-member-functions-to-static)

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			return aligned_alloc<std::byte>(a_count, ALIGNMENT_SIZE);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			aligned_free(a_ptr);
		}

		// NOLINTEND(readability-convert-member-functions-to-static)
	};

	static_assert(std::is_empty_v<BSTObjectArenaAlignedAllocator<0x08>>);

	class BSTObjectArenaScrapAllocator
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTObjectArenaScrapAllocator() :
			_allocator(MemoryManager::GetSingleton().GetThreadScrapHeap())
		{
			REX::Assert(_allocator != nullptr);
		}

		~BSTObjectArenaScrapAllocator() noexcept = default;

		BSTObjectArenaScrapAllocator(const BSTObjectArenaScrapAllocator&) = delete;
		BSTObjectArenaScrapAllocator(BSTObjectArenaScrapAllocator&&) = delete;

		auto operator=(const BSTObjectArenaScrapAllocator&) -> BSTObjectArenaScrapAllocator& = delete;
		auto operator=(BSTObjectArenaScrapAllocator&&) -> BSTObjectArenaScrapAllocator& = delete;

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			REX::Assert(_allocator != nullptr);
			return _allocator->CountedAllocate<std::byte>(a_count, SCRAP_HEAP_ALIGNMENT);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			REX::Assert(_allocator != nullptr);
			_allocator->Deallocate(a_ptr);
		}

	private:
		// members
		ScrapHeap* _allocator{nullptr}; // 0x00
	};

	static_assert(sizeof(BSTObjectArenaScrapAllocator) == 0x08);

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTHeapObjectArena = BSTObjectArena<T, BSTObjectArenaHeapAllocator, N>;

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE, std::uint32_t Alignment = alignof(T)>
	using BSTAlignedObjectArena = BSTObjectArena<T, BSTObjectArenaAlignedAllocator<Alignment>, N>;

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTScrapObjectArena = BSTObjectArena<T, BSTObjectArenaScrapAllocator, N>;
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <class T, class Allocator, std::uint32_t N>
	struct script_traits<BSTObjectArena<T, Allocator, N>>
	{
		using is_array = std::true_type;
	};
}
