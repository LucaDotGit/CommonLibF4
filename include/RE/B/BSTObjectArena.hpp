#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSTObjectArenaHeapAlloc;

	inline constexpr auto DEFAULT_OBJECT_ARENA_PAGE_SIZE = 32;

	template <class T, class Allocator = BSTObjectArenaHeapAlloc, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	class BSTObjectArena
		: private Allocator // 00
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
			[[nodiscard]] std::byte* begin() noexcept { return buffer.data(); }
			[[nodiscard]] const std::byte* begin() const noexcept { return buffer.data(); }
			[[nodiscard]] const std::byte* cbegin() const noexcept { return buffer.data(); }

			[[nodiscard]] std::byte* end() noexcept { return buffer.data() + buffer.size(); }
			[[nodiscard]] const std::byte* end() const noexcept { return buffer.data() + buffer.size(); }
			[[nodiscard]] const std::byte* cend() const noexcept { return buffer.data() + buffer.size(); }

			// members
			std::array<std::byte, sizeof(value_type) * N> buffer{ static_cast<std::byte>(0) }; // 00
			Page* next{ nullptr };															   // ??
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
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _proxy(a_rhs._proxy),
				  _first(a_rhs._first),
				  _last(a_rhs._last)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_proxy = a_rhs._proxy;
				_first = a_rhs._first;
				_last = a_rhs._last;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				REX::Assert(good());
				return *std::launder(reinterpret_cast<pointer>(_first));
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				REX::Assert(_last == a_rhs._last);

				if (_first == a_rhs._first) {
					REX::Assert(_proxy == a_rhs._proxy);
					return true;
				}

				return false;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				REX::Assert(good());

				_first += sizeof(value_type);
				if (_first == _proxy->cend() && _first != _last) {
					_proxy = _proxy->next;
					_first = _proxy->begin();
				}

				return *this;
			}

			iterator_base operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		protected:
			template <class, class, std::uint32_t>
			friend class BSTObjectArena;

			iterator_base(Page* a_proxy, std::byte* a_first, std::byte* a_last) noexcept
				: _proxy(a_proxy),
				  _first(a_first),
				  _last(a_last)
			{
			}

		private:
			template <class>
			friend class iterator_base;

			[[nodiscard]] bool good() const noexcept
			{
				return _proxy != nullptr &&
					   _first != nullptr &&
					   _last != nullptr &&
					   _first != _last &&
					   _first != _proxy->cend();
			}

			Page* _proxy{ nullptr };
			std::byte* _first{ nullptr };
			std::byte* _last{ nullptr };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		BSTObjectArena() = default;

		~BSTObjectArena()
		{
			const auto doDelete = [this](Page*& a_page) -> void {
				while (a_page != nullptr) {
					auto* next = a_page->next;
					allocator_type::deallocate_bytes(a_page);
					a_page = next;
				}
			};

			clear();

			doDelete(_head);
			doDelete(_free);

			_tail = nullptr;
			_end = nullptr;
			_begin = nullptr;
		}

		BSTObjectArena(const BSTObjectArena& a_rhs)
		{
			for (const auto& element : a_rhs) {
				emplace_back(element);
			}
		}

		BSTObjectArena(BSTObjectArena&& a_rhs) noexcept
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				allocator_type::operator=(std::move(a_rhs));
				_head = std::exchange(a_rhs._head, nullptr);
				_next = std::exchange(a_rhs._next, std::addressof(_head));
				_tail = std::exchange(a_rhs._tail, nullptr);
				_free = std::exchange(a_rhs._free, nullptr);
				_end = std::exchange(a_rhs._end, nullptr);
				_begin = std::exchange(a_rhs._begin, nullptr);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				for (auto& element : a_rhs) {
					push_back(std::move(element));
				}

				a_rhs.clear();
			}
		}

		BSTObjectArena& operator=(const BSTObjectArena& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();

			for (const auto& element : a_rhs) {
				emplace_back(element);
			}

			return *this;
		}

		BSTObjectArena& operator=(BSTObjectArena&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();

			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				allocator_type::operator=(std::move(a_rhs));
				_head = std::exchange(a_rhs._head, nullptr);
				_next = std::exchange(a_rhs._next, std::addressof(_head));
				_tail = std::exchange(a_rhs._tail, nullptr);
				_free = std::exchange(a_rhs._free, nullptr);
				_end = std::exchange(a_rhs._end, nullptr);
				_begin = std::exchange(a_rhs._begin, nullptr);
				_size = std::exchange(a_rhs._size, 0);
			}
			else {
				for (auto& element : a_rhs) {
					push_back(std::move(element));
				}

				a_rhs.clear();
			}
		}

		GAME_HEAP_REDEFINE_NEW(BSTObjectArena);

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

		[[nodiscard]] pointer data() noexcept { return empty() ? nullptr : std::launder(reinterpret_cast<pointer>(_begin)); }
		[[nodiscard]] const_pointer data() const noexcept { return empty() ? nullptr : std::launder(reinterpret_cast<const_pointer>(_begin)); }

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] size_type capacity() const noexcept { return N; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		iterator push_back(const value_type& a_value) { return emplace(a_value); }
		iterator push_back(value_type&& a_value) { return emplace(std::move(a_value)); }

		template <class... Args>
		iterator emplace_back(Args&&... a_args)
		{
			auto buffer = allocate_buffer();
			std::construct_at(
				reinterpret_cast<value_type*>(buffer.data()),
				std::forward<Args>(a_args)...);
			return iterator{ _tail, buffer.data(), _end };
		}

		void clear()
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
				else { // update pos to next page
					_begin = _head->next->begin();
				}

				// move head into free list, grab next page
				_head =
					std::exchange(_head->next,
						std::exchange(_free, _head));
			}

			REX::Assert(empty());
		}

		void swap(BSTObjectArena& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

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
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It(_head, _begin, _end);
		}

		[[nodiscard]] auto allocate_buffer() -> std::span<std::byte>
		{
			if (!_tail || _end == _tail->cend()) {
				auto* page =
					_free ?
						std::exchange(_free, _free->next) :									   // pull from free list
						std::construct_at<Page>(allocator_type::allocate_bytes(sizeof(Page))); // go to heap

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
			return std::span{ buffer, sizeof(value_type) };
		}

		// members
		Page* _head{ nullptr };				   // ?? - head of active pages
		Page** _next{ std::addressof(_head) }; // ?? - used to update next ptr when appending pages
		Page* _tail{ nullptr };				   // ?? - tail of active pages
		Page* _free{ nullptr };				   // ?? - local free list
		std::byte* _end{ nullptr };			   // ?? - ptr to end of active lifetime elements
		std::byte* _begin{ nullptr };		   // ?? - ptr to beginning of active lifetime elements
		size_type _size{ 0 };				   // ??
	};

	template <class T, class Allocator = BSTObjectArenaHeapAlloc, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	void swap(BSTObjectArena<T, Allocator, N>& a_lhs, BSTObjectArena<T, Allocator, N>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	class BSTObjectArenaHeapAlloc
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTObjectArenaHeapAlloc() = default;
		~BSTObjectArenaHeapAlloc() noexcept = default;

		BSTObjectArenaHeapAlloc(const BSTObjectArenaHeapAlloc&) = delete;
		BSTObjectArenaHeapAlloc(BSTObjectArenaHeapAlloc&&) noexcept = default;

		BSTObjectArenaHeapAlloc& operator=(const BSTObjectArenaHeapAlloc&) = delete;
		BSTObjectArenaHeapAlloc& operator=(BSTObjectArenaHeapAlloc&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_count) noexcept
		{
			return calloc<std::byte>(a_count);
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<BSTObjectArenaHeapAlloc>);

	template <std::uint32_t Align>
	class BSTObjectArenaHeapAlignAlloc
	{
	public:
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Align);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTObjectArenaHeapAlignAlloc() = default;
		~BSTObjectArenaHeapAlignAlloc() noexcept = default;

		BSTObjectArenaHeapAlignAlloc(const BSTObjectArenaHeapAlignAlloc&) = delete;
		BSTObjectArenaHeapAlignAlloc(BSTObjectArenaHeapAlignAlloc&&) noexcept = default;

		BSTObjectArenaHeapAlignAlloc& operator=(const BSTObjectArenaHeapAlignAlloc&) = delete;
		BSTObjectArenaHeapAlignAlloc& operator=(BSTObjectArenaHeapAlignAlloc&&) noexcept = default;

		[[nodiscard]] __declspec(allocator) __declspec(restrict) static void* allocate_bytes(size_type a_count) noexcept
		{
			return aligned_alloc<std::byte>(a_count, ALIGNMENT_SIZE);
		}

		__declspec(noalias) static void deallocate_bytes(void* a_ptr) noexcept
		{
			if (!a_ptr) {
				return;
			}

			aligned_free(a_ptr);
		}
	};
	static_assert(std::is_empty_v<BSTObjectArenaHeapAlignAlloc<0x08>>);

	class BSTObjectArenaScrapAlloc
	{
	public:
		inline static constexpr auto SCRAP_HEAP_ALIGNMENT = static_cast<std::align_val_t>(sizeof(std::uintptr_t));

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTObjectArenaScrapAlloc()
			: _allocator(MemoryManager::GetSingleton().GetThreadScrapHeap())
		{
			REX::Assert(_allocator != nullptr);
		}

		~BSTObjectArenaScrapAlloc() noexcept = default;

		BSTObjectArenaScrapAlloc(const BSTObjectArenaScrapAlloc&) = delete;

		BSTObjectArenaScrapAlloc(BSTObjectArenaScrapAlloc&& a_rhs) noexcept
			: _allocator(std::exchange(a_rhs._allocator, nullptr))
		{
		}

		BSTObjectArenaScrapAlloc& operator=(const BSTObjectArenaScrapAlloc&) = delete;

		BSTObjectArenaScrapAlloc& operator=(BSTObjectArenaScrapAlloc&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_allocator = std::exchange(a_rhs._allocator, nullptr);
			return *this;
		}

		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* allocate_bytes(size_type a_count) noexcept
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
		ScrapHeap* _allocator{ nullptr }; // 00
	};
	static_assert(sizeof(BSTObjectArenaScrapAlloc) == 0x08);

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTHeapObjectArena = BSTObjectArena<T, BSTObjectArenaHeapAlloc, N>;

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE, std::uint32_t Align = alignof(T)>
	using BSTAlignedObjectArena = BSTObjectArena<T, BSTObjectArenaHeapAlignAlloc<Align>, N>;

	template <class T, std::uint32_t N = DEFAULT_OBJECT_ARENA_PAGE_SIZE>
	using BSTScrapObjectArena = BSTObjectArena<T, BSTObjectArenaScrapAlloc, N>;
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
