#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::Impl
{
	inline constexpr auto SCATTER_TABLE_SENTINEL = std::array{ 0xDEui8, 0xADui8, 0xBEui8, 0xEFui8 };
}

namespace RE
{
	// scatter table with chaining
	template <class Hash, class KeyEqual, class Traits, template <std::uint32_t, std::uint32_t> class Allocator>
	class BSTScatterTable
	{
	public:
		using hash_type = Hash;
		using key_equal = KeyEqual;
		using traits_type = Traits;
		using key_type = traits_type::key_type;
		using mapped_type = traits_type::mapped_type;
		using value_type = traits_type::value_type;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		static_assert(std::is_invocable_r_v<size_type, const hash_type&, const key_type&>);
		static_assert(std::is_invocable_r_v<bool, const key_equal&, const key_type&, const key_type&>);

	private:
		class entry_type
		{
		public:
			entry_type() = default;
			entry_type(const entry_type&) = delete;

			entry_type(entry_type&& a_rhs) //
				noexcept(std::is_nothrow_move_constructible_v<value_type> &&
						 std::is_nothrow_destructible_v<value_type>)
			{
				if (a_rhs.has_value()) {
					auto* rnext = a_rhs.next;
					emplace(std::move(a_rhs).steal(), rnext);
				}
			}

			~entry_type() noexcept { destroy(); }

			entry_type& operator=(const entry_type&) = delete;

			entry_type& operator=(entry_type&& a_rhs) //
				noexcept(std::is_nothrow_move_constructible_v<value_type> &&
						 std::is_nothrow_destructible_v<value_type>)
			{
				if (this == std::addressof(a_rhs)) {
					return *this;
				}

				destroy();
				if (a_rhs.has_value()) {
					auto* rnext = a_rhs.next;
					emplace(std::move(a_rhs).steal(), rnext);
				}

				return *this;
			}

			[[nodiscard]] bool has_value() const noexcept { return next != nullptr; }

			void destroy() //
				noexcept(std::is_nothrow_destructible_v<value_type>)
			{
				if (has_value()) {
					std::destroy_at(std::addressof(value));
					next = nullptr;
				}

				REX::Assert(!has_value());
			}

			template <class Arg>
			void emplace(Arg&& a_value, const entry_type* a_next) //
				noexcept(std::is_nothrow_constructible_v<value_type, Arg>)
			{
				static_assert(std::same_as<std::decay_t<Arg>, value_type>);
				destroy();
				std::construct_at(std::addressof(value), std::forward<Arg>(a_value));
				next = const_cast<entry_type*>(a_next);
				REX::Assert(has_value());
			}

			[[nodiscard]] value_type steal() && //
				noexcept(std::is_nothrow_move_constructible_v<value_type> &&
						 std::is_nothrow_destructible_v<value_type>)
			{
				REX::Assert(has_value());
				auto result = std::move(value);
				destroy();
				REX::Assert(!has_value());
				return result;
			}

			union
			{
				value_type value;
				std::array<std::byte, sizeof(value_type)> buffer{ static_cast<std::byte>(0) };
			};
			entry_type* next{ nullptr };
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
				: _first(a_rhs._first),
				  _last(a_rhs._last)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				REX::Assert(_last == a_rhs._last);
				_first = a_rhs._first;
				_last = a_rhs._last;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				REX::Assert(iterable());
				REX::Assert(_first->has_value());
				return _first->value;
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				REX::Assert(_last == a_rhs._last);
				return _first == a_rhs._first;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				seek();
				return *this;
			}

			iterator_base operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		protected:
			template <class, class, class, template <std::uint32_t, std::uint32_t> class>
			friend class BSTScatterTable;

			iterator_base(entry_type* a_first, entry_type* a_last) noexcept
				: _first(a_first),
				  _last(a_last)
			{
				REX::Assert(!!_first == !!_last); // both or neither have values
				REX::Assert(_first <= _last);

				if (iterable() && !_first->has_value()) {
					seek();
				}
			}

			[[nodiscard]] entry_type* get_entry() const noexcept
			{
				return _first;
			}

		private:
			template <class>
			friend class iterator_base;

			[[nodiscard]] bool iterable() const noexcept
			{
				return _first && _last && _first != _last;
			}

			void seek() noexcept
			{
				REX::Assert(iterable());

				do {
					_first++;
				}
				while (_first != _last && !_first->has_value());
			}

			entry_type* _first{ nullptr };
			entry_type* _last{ nullptr };
		};

	public:
		using allocator_type = Allocator<sizeof(entry_type), alignof(entry_type)>;
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSTScatterTable() = default;

		~BSTScatterTable()
		{
			free_resources();
		}

		BSTScatterTable(std::initializer_list<value_type> a_ilist)
		{
			insert(a_ilist.begin(), a_ilist.end());
		}

		BSTScatterTable(const BSTScatterTable& a_rhs)
		{
			insert(a_rhs.begin(), a_rhs.end());
		}

		BSTScatterTable(BSTScatterTable&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_capacity = std::exchange(a_rhs._capacity, 0);
				_free = std::exchange(a_rhs._free, 0);
				_good = std::exchange(a_rhs._good, 0);
			}
			else {
				insert(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		BSTScatterTable& operator=(std::initializer_list<value_type> a_ilist)
		{
			assign(a_ilist.begin(), a_ilist.end());
			return *this;
		}

		BSTScatterTable& operator=(const BSTScatterTable& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();
			insert(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		BSTScatterTable& operator=(BSTScatterTable&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			free_resources();

			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_capacity = std::exchange(a_rhs._capacity, 0);
				_free = std::exchange(a_rhs._free, 0);
				_good = std::exchange(a_rhs._good, 0);
			}
			else {
				insert(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		GAME_HEAP_REDEFINE_NEW(BSTScatterTable);

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(get_entries()); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(get_entries()); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return make_iterator<const_iterator>(get_entries()); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cend() const noexcept { return make_iterator<const_iterator>(); }

		[[nodiscard]] size_type size() const noexcept { return _capacity - _free; }
		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<std::make_signed_t<size_type>>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] auto& operator[](const key_type& a_key)
		{
			const auto it = find(a_key);
			if (it != end()) {
				return it->second;
			}

			auto [newIt, _] = insert(value_type(a_key, mapped_type()));
			return newIt->second;
		}

		[[nodiscard]] auto& at(const key_type& a_key)
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]] const auto& at(const key_type& a_key) const
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		std::pair<iterator, bool> insert(const value_type& a_value)
		{
			return do_insert(a_value);
		}

		std::pair<iterator, bool> insert(value_type&& a_value)
		{
			return do_insert(std::move(a_value));
		}

		template <std::input_iterator InputIt>
		void insert(InputIt a_first, InputIt a_last)
			requires(std::is_convertible_v<std::iter_reference_t<InputIt>, const_reference>)
		{
			reserve(size() + static_cast<size_type>(std::distance(a_first, a_last)));
			for (; a_first != a_last; a_first++) {
				insert(*std::move(a_first));
			}
		}

		template <class... Args>
		std::pair<iterator, bool> insert_or_assign(Args&&... a_args)
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return do_insert_or_assign(value_type(std::forward<Args>(a_args)...));
		}

		template <class... Args>
		std::pair<iterator, bool> emplace(Args&&... a_args)
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return insert(value_type(std::forward<Args>(a_args)...));
		}

		template <class... Args>
		std::pair<iterator, bool> try_emplace(const key_type& a_key, Args&&... a_args)
			requires(std::is_constructible_v<mapped_type, Args...>)
		{
			const auto it = find(a_key);
			if (it != end()) {
				return { it, false };
			}

			auto value = value_type(a_key, mapped_type(std::forward<Args>(a_args)...));
			return insert(std::move(value));
		}

		iterator erase(const_iterator a_position)
		{
			return do_erase(a_position);
		}

		iterator erase(iterator a_position)
		{
			return do_erase(a_position);
		}

		size_type erase(const key_type& a_key)
		{
			const auto pos = find(a_key);
			const auto result = pos != end() ? erase(pos) : pos;
			return result != end() ? 1 : 0;
		}

		void clear()
		{
			if (size() > 0) {
				auto* entries = get_entries();
				REX::Assert(entries != nullptr);

				for (auto i = static_cast<size_type>(0); i < _capacity; i++) {
					entries[i].destroy();
				}

				_free = _capacity;
				_good = 0;
			}

			REX::Assert(empty());
		}

		[[nodiscard]] iterator find(const key_type& a_key)
		{
			return do_find<iterator>(a_key);
		}

		[[nodiscard]] const_iterator find(const key_type& a_key) const
		{
			return do_find<const_iterator>(a_key);
		}

		[[nodiscard]] bool contains(const key_type& a_key) const
		{
			return find(a_key) != end();
		}

		void reserve(size_type a_count)
		{
			if (a_count <= _capacity) {
				return;
			}

			const auto oldCapacity = _capacity;
			auto* oldEntries = get_entries();

			auto&& [newCapacity, newEntries] = [this, a_count]() {
				constexpr auto MIN = static_cast<std::size_t>(allocator_type::min_size());
				static_assert(MIN > 0 && std::has_single_bit(MIN));

				const auto capacity = std::max(std::bit_ceil<std::size_t>(a_count), MIN);
				REX::Assert(capacity >= MIN);

				if (capacity > max_size()) [[unlikely]] {
					REX::Fail("Failed to reserve memory due to capacity overflow."sv);
				}

				auto* entries = allocate(static_cast<size_type>(capacity));
				if (!entries) [[unlikely]] {
					REX::AllocationFail();
				}

				return std::make_pair(static_cast<size_type>(capacity), entries);
			}();

			const auto setCapacity = [this](size_type a_newCap) {
				_capacity = a_newCap;
				_free = _capacity;
				_good = 0;
			};

			if (newEntries == oldEntries) {
				std::uninitialized_default_construct_n(oldEntries + oldCapacity, newCapacity - oldCapacity);
				auto todo = std::vector<value_type>();
				todo.reserve(size());

				for (auto i = static_cast<size_type>(0); i < oldCapacity; i++) {
					auto& entry = oldEntries[i];
					if (entry.has_value()) {
						todo.emplace_back(std::move(entry).steal());
					}
				}

				setCapacity(newCapacity);
				insert(
					std::make_move_iterator(todo.begin()),
					std::make_move_iterator(todo.end()));

				return;
			}

			// in with the new
			std::uninitialized_default_construct_n(newEntries, newCapacity);
			setCapacity(newCapacity);
			set_entries(newEntries);

			if (!oldEntries) { // out with the old
				return;
			}

			for (auto i = static_cast<size_type>(0); i < oldCapacity; i++) {
				auto& entry = oldEntries[i];
				if (entry.has_value()) {
					insert(std::move(entry).steal());
				}
			}

			std::destroy_n(oldEntries, oldCapacity);
			deallocate(oldEntries);
		}

		void swap(BSTScatterTable& a_other) noexcept
			requires(std::same_as<typename allocator_type::propagate_on_container_move_assignment, std::true_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_capacity, a_other._capacity);
			std::swap(_free, a_other._free);
			std::swap(_good, a_other._good);
			std::swap(_sentinel, a_other._sentinel);
			std::swap(_allocator, a_other._allocator);
		}

	private:
		template <class It>
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It(get_entries() + _capacity, get_entries() + _capacity);
		}

		template <class It>
		[[nodiscard]] It make_iterator(entry_type* a_first) const noexcept
		{
			return It(a_first, get_entries() + _capacity);
		}

		[[nodiscard]] static const key_type& unwrap_key(const value_type& a_value) noexcept
		{
			return traits_type::unwrap_key(a_value);
		}

		[[nodiscard]] entry_type* allocate(size_type a_count)
		{
			return static_cast<entry_type*>(_allocator.allocate_bytes(sizeof(entry_type) * a_count));
		}

		void deallocate(entry_type* a_entry)
		{
			_allocator.deallocate_bytes(a_entry);
		}

		template <class It>
		[[nodiscard]] It do_find(const key_type& a_key) const //
			noexcept(noexcept(hash_function(a_key)) && noexcept(key_eq(a_key, a_key)))
		{
			if (empty()) {
				return make_iterator<It>();
			}

			auto* entry = std::addressof(get_entry_for(a_key));
			if (entry->has_value()) {
				do { // follow chain
					if (key_eq(unwrap_key(entry->value), a_key)) {
						return make_iterator<It>(entry);
					}

					entry = entry->next;
				}
				while (entry != _sentinel);
			}

			return make_iterator<It>();
		}

		template <class P>
		[[nodiscard]] std::pair<iterator, bool> do_insert(P&& a_value)
			requires(std::same_as<std::decay_t<P>, value_type>)
		{
			const auto it = find(unwrap_key(a_value));
			if (it != end()) { // already exists
				return std::make_pair(it, false);
			}

			if (_free == 0) { // no free entries
				reserve(_capacity + 1);
				REX::Assert(_free > 0);
			}

			const auto decrement = REX::ScopeExit([this]() noexcept { --_free; });

			auto* entry = std::addressof(get_entry_for(unwrap_key(a_value)));
			if (entry->has_value()) { // slot is taken, resolve conflict
				auto* free = std::addressof(get_free_entry());
				auto* wouldHave = std::addressof(get_entry_for(unwrap_key(entry->value)));

				if (wouldHave == entry) { // hash collision
					free->emplace(std::forward<P>(a_value), std::exchange(entry->next, free));
					return std::make_pair(make_iterator<iterator>(free), true);
				}

				// how did we get here?
				auto* prev = wouldHave;
				while (prev->next != entry) {
					prev = prev->next;
				}

				// evict current value and detach from chain
				*free = std::move(*entry);
				prev->next = free;
				entry->emplace(std::forward<P>(a_value), _sentinel);

				return std::make_pair(make_iterator<iterator>(entry), true);
			}

			// its free realestate
			entry->emplace(std::forward<P>(a_value), _sentinel);
			return std::make_pair(make_iterator<iterator>(entry), true);
		}

		template <class P>
		[[nodiscard]] std::pair<iterator, bool> do_insert_or_assign(P&& a_value)
			requires(std::same_as<std::decay_t<P>, value_type>)
		{
			auto&& [it, hasInserted] = do_insert(std::forward<P>(a_value));
			if (!hasInserted) {
				it->second = std::forward<P>(a_value).second;
			}

			return std::make_pair(it, hasInserted);
		}

		[[nodiscard]] iterator do_erase(const_iterator a_position)
		{
			REX::Assert(a_position != end());
			auto* entry = a_position.get_entry();
			REX::Assert(entry != nullptr);
			REX::Assert(entry->has_value());

			if (entry->next == _sentinel) { // end of chain
				auto* prev = std::addressof(get_entry_for(unwrap_key(entry->value)));
				if (prev != entry) {
					while (prev->next != entry) {
						prev = prev->next;
					}

					prev->next = const_cast<entry_type*>(_sentinel); // detach from chain
				}

				entry->destroy();
			}
			else { // move next into current
				*entry = std::move(*entry->next);
			}

			_free++;
			return make_iterator<iterator>(entry + 1);
		}

		void free_resources()
		{
			if (_capacity > 0) {
				REX::Assert(get_entries() != nullptr);
				std::destroy_n(get_entries(), _capacity);
				deallocate(get_entries());
				set_entries(nullptr);
				_capacity = 0;
				_free = 0;
				_good = 0;
			}

			REX::Assert(get_entries() == nullptr);
			REX::Assert(_capacity == 0);
			REX::Assert(_free == 0);
		}

		[[nodiscard]] entry_type& get_entry_for(const key_type& a_key) const //
			noexcept(noexcept(hash_function(a_key)))
		{
			REX::Assert(get_entries() != nullptr);
			REX::Assert(std::has_single_bit(_capacity));

			const auto hash = hash_function(a_key);
			const auto index = hash & (_capacity - 1); // quick modulo
			return get_entries()[index];
		}

		[[nodiscard]] entry_type* get_entries() const noexcept
		{
			return static_cast<entry_type*>(_allocator.get_entries());
		}

		[[nodiscard]] entry_type& get_free_entry() noexcept
		{
			REX::Assert(_free > 0);
			REX::Assert(get_entries() != nullptr);
			REX::Assert(std::has_single_bit(_capacity));
			REX::Assert([this]() noexcept {
				const auto begin = get_entries();
				const auto end = get_entries() + _capacity;
				return std::find_if(begin, end, [](const entry_type& a_entry) noexcept {
					return !a_entry.has_value();
				}) != end;
			}());

			auto* entries = get_entries();
			while (entries[_good].has_value()) {
				_good = (_good + 1) & (_capacity - 1); // wrap around w/ quick modulo
			}

			return entries[_good];
		}

		[[nodiscard]] size_type hash_function(const key_type& a_key) const //
			noexcept(std::is_nothrow_constructible_v<hash_type> &&
					 std::is_nothrow_invocable_v<const hash_type&, const key_type&>)
		{
			return static_cast<size_type>(std::invoke(hash_type(), a_key));
		}

		[[nodiscard]] bool key_eq(const key_type& a_lhs, const key_type& a_rhs) const //
			noexcept(std::is_nothrow_constructible_v<key_equal> &&
					 std::is_nothrow_invocable_v<const key_equal&, const key_type&, const key_type&>)
		{
			return key_equal()(a_lhs, a_rhs);
		}

		void set_entries(entry_type* a_entries) noexcept
		{
			_allocator.set_entries(a_entries);
		}

		// members
		std::uint64_t _pad00{ 0 };																				 // 00
		std::uint32_t _pad08{ 0 };																				 // 08
		size_type _capacity{ 0 };																				 // 0C - total # of slots, always a power of 2
		size_type _free{ 0 };																					 // 10 - # of free slots
		size_type _good{ 0 };																					 // 14 - last free index
		const entry_type* _sentinel{ reinterpret_cast<const entry_type*>(Impl::SCATTER_TABLE_SENTINEL.data()) }; // 18 - signals end of chain
		allocator_type _allocator;																				 // 20
	};

	template <class Key, class T>
	class BSTScatterTableTraits
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTPair<const key_type, mapped_type>;

		// NOLINTNEXTLINE(bugprone-return-const-ref-from-parameter)
		[[nodiscard]] static const key_type& unwrap_key(const value_type& a_value) noexcept { return a_value.first; }
	};

	template <class Key>
	class BSTSetTraits
	{
	public:
		using key_type = Key;
		using mapped_type = void;
		using value_type = key_type;

		// NOLINTNEXTLINE(bugprone-return-const-ref-from-parameter)
		[[nodiscard]] static const key_type& unwrap_key(const value_type& a_value) noexcept { return a_value; }
	};

	template <std::uint32_t Size, std::uint32_t Align>
	class BSTScatterTableHeapAllocator
	{
	public:
		inline static constexpr auto SIZE = Size;
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Align);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTScatterTableHeapAllocator() = default;
		~BSTScatterTableHeapAllocator() noexcept = default;

		BSTScatterTableHeapAllocator(const BSTScatterTableHeapAllocator&) = delete;

		BSTScatterTableHeapAllocator(BSTScatterTableHeapAllocator&& a_rhs) noexcept
			: _entries(std::exchange(a_rhs._entries, nullptr))
		{
		}

		BSTScatterTableHeapAllocator& operator=(const BSTScatterTableHeapAllocator&) = delete;

		BSTScatterTableHeapAllocator& operator=(BSTScatterTableHeapAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_entries = std::exchange(a_rhs._entries, nullptr);
			return *this;
		}

		[[nodiscard]] static consteval size_type min_size() noexcept { return 1 << 3; }

		[[nodiscard]] void* get_entries() const noexcept { return _entries; }
		void set_entries(void* a_entries) noexcept { _entries = static_cast<std::byte*>(a_entries); }

		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* allocate_bytes(size_type a_count) noexcept
		{
			REX::Assert(a_count % SIZE == 0);

			auto* mem = calloc<std::byte>(a_count);
			if (!mem) [[unlikely]] {
				REX::AllocationFail();
			}

			return mem;
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}

	private:
		// members
		std::uint64_t _pad00{ 0 };		// 00 (20)
		std::byte* _entries{ nullptr }; // 08 (28)
	};

	template <std::uint32_t Size, std::uint32_t Align>
	class BSTScatterTableScrapAllocator
	{
	public:
		inline static constexpr auto SIZE = Size;
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Align);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTScatterTableScrapAllocator()
			: _allocator(MemoryManager::GetSingleton().GetThreadScrapHeap())
		{
			REX::Ensure(_allocator != nullptr);
		}

		~BSTScatterTableScrapAllocator() noexcept = default;

		BSTScatterTableScrapAllocator(const BSTScatterTableScrapAllocator&) = delete;

		BSTScatterTableScrapAllocator(BSTScatterTableScrapAllocator&& a_rhs) noexcept
			: _allocator(std::exchange(a_rhs._allocator, nullptr)),
			  _entries(std::exchange(a_rhs._entries, nullptr))
		{
		}

		BSTScatterTableScrapAllocator& operator=(const BSTScatterTableScrapAllocator&) = delete;

		BSTScatterTableScrapAllocator& operator=(BSTScatterTableScrapAllocator&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_allocator = std::exchange(a_rhs._allocator, nullptr);
			_entries = std::exchange(a_rhs._entries, nullptr);
			return *this;
		}

		[[nodiscard]] static consteval size_type min_size() noexcept { return 1 << 3; }

		[[nodiscard]] void* get_entries() const noexcept { return _entries; }
		void set_entries(void* a_entries) noexcept { _entries = static_cast<std::byte*>(a_entries); }

		[[nodiscard]] __declspec(allocator) __declspec(restrict) void* allocate_bytes(size_type a_count) noexcept
		{
			REX::Assert(a_count % SIZE == 0);
			REX::Assert(_allocator != nullptr);

			auto* mem = _allocator->Allocate(a_count, ALIGNMENT_SIZE);
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

			REX::Assert(_allocator != nullptr);
			_allocator->Deallocate(a_ptr);
		}

	private:
		// members
		ScrapHeap* _allocator{ nullptr }; // 00 (20)
		std::byte* _entries{ nullptr };	  // 08 (28)
	};

	template <std::uint32_t N>
	class BSTStaticHashMapAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		static_assert(MAX_SIZE > 0 && std::has_single_bit(MAX_SIZE), "Size must be a power of 2.");

		template <std::uint32_t Size, std::uint32_t Align>
		class Allocator
		{
		public:
			inline static constexpr auto SIZE = Size;
			inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Align);

			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using propagate_on_container_move_assignment = std::false_type;

			Allocator() = default;
			~Allocator() noexcept = default;

			Allocator(const Allocator&) = delete;

			Allocator(Allocator&& a_rhs) noexcept
				: _entries(std::exchange(a_rhs._entries, nullptr))
			{
			}

			Allocator& operator=(const Allocator&) = delete;

			Allocator& operator=(Allocator&& a_rhs) noexcept
			{
				if (this == std::addressof(a_rhs)) {
					return *this;
				}

				_entries = std::exchange(a_rhs._entries, nullptr);
				return *this;
			}

			[[nodiscard]] static consteval size_type min_size() noexcept { return MAX_SIZE; }

			[[nodiscard]] void* get_entries() const noexcept { return _entries; }

			void set_entries(void* a_entries) noexcept
			{
				REX::Assert(a_entries == _buffer.data() || a_entries == nullptr);
				_entries = static_cast<std::byte*>(a_entries);
			}

			[[nodiscard]] __declspec(allocator) void* allocate_bytes(size_type a_count) noexcept
			{
				REX::Assert(a_count % SIZE == 0);
				return a_count <= MAX_SIZE * SIZE ? _buffer.data() : nullptr;
			}

			__declspec(noalias) void deallocate_bytes([[maybe_unused]] void* a_ptr) noexcept
			{
				REX::Assert(a_ptr == _buffer.data());
			}

		private:
			// members
			alignas(ALIGNMENT_SIZE) std::array<std::byte, MAX_SIZE * SIZE> _buffer{ static_cast<std::byte>(0) }; // 00 (20)
			std::byte* _entries{ nullptr };																		 // ??
		};
	};

	template <class Key, class T, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTHashMap =
		BSTScatterTable<
			Hash,
			KeyEqual,
			BSTScatterTableTraits<Key, T>,
			BSTScatterTableHeapAllocator>;

	template <class Key, class T, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTScrapHashMap =
		BSTScatterTable<
			Hash,
			KeyEqual,
			BSTScatterTableTraits<Key, T>,
			BSTScatterTableScrapAllocator>;

	template <class Key, class T, std::uint32_t N, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTStaticHashMap =
		BSTScatterTable<
			Hash,
			KeyEqual,
			BSTScatterTableTraits<Key, T>,
			BSTStaticHashMapAllocator<N>::template Allocator>;

	template <class Key, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTSet =
		BSTScatterTable<
			Hash,
			KeyEqual,
			BSTSetTraits<Key>,
			BSTScatterTableHeapAllocator>;

	template <class Key, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTScrapSet =
		BSTScatterTable<
			Hash,
			KeyEqual,
			BSTSetTraits<Key>,
			BSTScatterTableScrapAllocator>;

	template <class Hash, class KeyEqual, class Traits, template <std::uint32_t, std::uint32_t> class Allocator>
	void swap(BSTScatterTable<Hash, KeyEqual, Traits, Allocator>& a_lhs, BSTScatterTable<Hash, KeyEqual, Traits, Allocator>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
