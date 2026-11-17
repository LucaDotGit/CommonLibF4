#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::Impl
{
	inline constexpr auto SCATTER_TABLE_SENTINEL = std::array{
		static_cast<std::uint8_t>(0xDE),
		static_cast<std::uint8_t>(0xAD),
		static_cast<std::uint8_t>(0xBE),
		static_cast<std::uint8_t>(0xEF)
	};
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
			entry_type() noexcept = default;

			~entry_type() noexcept
			{
				destroy();
			}

			entry_type(const entry_type&) = delete;

			entry_type(entry_type&& a_rhs)
				noexcept(std::is_nothrow_move_constructible_v<value_type> && std::is_nothrow_destructible_v<value_type>)
			{
				if (a_rhs.has_value()) {
					auto* rnext = a_rhs.next;
					emplace(std::move(a_rhs).steal(), rnext);
				}
			}

			auto operator=(const entry_type&) -> entry_type& = delete;

			auto operator=(entry_type&& a_rhs)
				noexcept(std::is_nothrow_move_constructible_v<value_type> && std::is_nothrow_destructible_v<value_type>)
					-> entry_type&
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

			[[nodiscard]]
			auto has_value() const noexcept -> bool
			{
				return next != nullptr;
			}

			void destroy() noexcept(std::is_nothrow_destructible_v<value_type>)
			{
				if (has_value()) {
					std::destroy_at(std::addressof(value));
					next = nullptr;
				}

				REX::Assert(!has_value());
			}

			template <class Arg>
			void emplace(Arg&& a_value, const entry_type* a_next)
				noexcept(std::is_nothrow_constructible_v<value_type, Arg>)
			{
				static_assert(std::same_as<std::decay_t<Arg>, value_type>);
				destroy();
				std::construct_at(std::addressof(value), std::forward<Arg>(a_value));
				next = const_cast<entry_type*>(a_next);
				REX::Assert(has_value());
			}

			[[nodiscard]]
			auto steal() && //
				noexcept(std::is_nothrow_move_constructible_v<value_type> && std::is_nothrow_destructible_v<value_type>)
					-> value_type
			{
				REX::Assert(has_value());
				auto result = std::move(value);
				destroy();
				REX::Assert(!has_value());
				return result;
			}

			union
			{
			public:
				value_type value;
				std::array<std::byte, sizeof(value_type)> buffer{static_cast<std::byte>(0)};
			};

			entry_type* next{nullptr};
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
				REX::Assert(_last == a_rhs._last);
				_first = a_rhs._first;
				_last = a_rhs._last;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() const noexcept -> reference
			{
				REX::Assert(iterable());
				REX::Assert(_first->has_value());
				return _first->value;
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
				return _first == a_rhs._first;
			}

			auto operator++() noexcept -> iterator_base&
			{
				seek();
				return *this;
			}

			auto operator++(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		private:
			template <class, class, class, template <std::uint32_t, std::uint32_t> class>
			friend class BSTScatterTable;

			template <class>
			friend class iterator_base;

			iterator_base(entry_type* a_first, entry_type* a_last) noexcept :
				_first(a_first),
				_last(a_last)
			{
				REX::Assert(!(_first == nullptr) == !(_last == nullptr)); // both or neither have values
				REX::Assert(_first <= _last);

				if (iterable() && !_first->has_value()) {
					seek();
				}
			}

			[[nodiscard]]
			auto get_entry() const noexcept -> entry_type*
			{
				return _first;
			}

			[[nodiscard]]
			auto iterable() const noexcept -> bool
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

			entry_type* _first{nullptr};
			entry_type* _last{nullptr};
		};

	public:
		using allocator_type = Allocator<sizeof(entry_type), alignof(entry_type)>;
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSTScatterTable() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		~BSTScatterTable() noexcept
		{
			free_resources();
		}

		template <std::input_iterator InputIt>
		BSTScatterTable(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		BSTScatterTable(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		BSTScatterTable(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		BSTScatterTable(const BSTScatterTable& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSTScatterTable(BSTScatterTable&& a_rhs)
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>)
		{
			if constexpr (allocator_type::propagate_on_container_move_assignment::value) {
				_allocator = std::move(a_rhs._allocator);
				_capacity = std::exchange(a_rhs._capacity, 0);
				_free = std::exchange(a_rhs._free, 0);
				_good = std::exchange(a_rhs._good, 0);
			}
			else {
				assign(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}
		}

		auto operator=(std::initializer_list<value_type> a_rhs) -> BSTScatterTable&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(const BSTScatterTable& a_rhs) -> BSTScatterTable&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(BSTScatterTable&& a_rhs)
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>)
				-> BSTScatterTable&
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
				assign(std::make_move_iterator(a_rhs.begin()), std::make_move_iterator(a_rhs.end()));
				a_rhs.clear();
			}

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTScatterTable);

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>(get_entries());
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(get_entries());
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(get_entries());
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
			return make_iterator<const_iterator>();
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _capacity - _free;
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
			return std::numeric_limits<size_type>::max();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		[[nodiscard]]
		auto operator[](const key_type& a_key) -> auto&
		{
			const auto it = find(a_key);
			if (it != end()) {
				return it->second;
			}

			auto&& [newIt, _] = insert(value_type(a_key, mapped_type()));
			return newIt->second;
		}

		[[nodiscard]]
		auto at(const key_type& a_key) -> auto&
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]]
		auto at(const key_type& a_key) const -> const auto&
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		template <std::input_iterator InputIt>
		void assign(InputIt a_first, InputIt a_last)
		{
			clear();
			reserve(static_cast<size_type>(std::distance(a_first, a_last)));

			for (; a_first != a_last; a_first++) {
				insert(*std::move(a_first));
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

		auto insert(const value_type& a_value) -> std::pair<iterator, bool>
		{
			return do_insert(a_value);
		}

		auto insert(value_type&& a_value) -> std::pair<iterator, bool>
		{
			return do_insert(std::move(a_value));
		}

		template <std::input_iterator InputIt>
		void insert(InputIt a_first, InputIt a_last)
		{
			reserve(size() + static_cast<size_type>(std::distance(a_first, a_last)));

			for (; a_first != a_last; a_first++) {
				insert(*std::move(a_first));
			}
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void insert_range(Range&& a_range)
		{
			insert(std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <class... Args>
		auto insert_or_assign(Args&&... a_args) -> std::pair<iterator, bool>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return do_insert_or_assign(value_type(std::forward<Args>(a_args)...));
		}

		template <class... Args>
		auto emplace(Args&&... a_args) -> std::pair<iterator, bool>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return insert(value_type(std::forward<Args>(a_args)...));
		}

		template <class... Args>
		auto try_emplace(const key_type& a_key, Args&&... a_args) -> std::pair<iterator, bool>
			requires(std::is_constructible_v<mapped_type, Args...>)
		{
			const auto it = find(a_key);
			if (it != end()) {
				return {it, false};
			}

			auto value = value_type(a_key, mapped_type(std::forward<Args>(a_args)...));
			return insert(std::move(value));
		}

		auto erase(const_iterator a_position) -> iterator
		{
			return do_erase(a_position);
		}

		auto erase(iterator a_position) -> iterator
		{
			return do_erase(a_position);
		}

		auto erase(const key_type& a_key) -> size_type
		{
			const auto keyIt = find(a_key);
			const auto resultIt = keyIt != end() ? erase(keyIt) : keyIt;
			return resultIt != end() ? 1 : 0;
		}

		void clear() noexcept
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

		[[nodiscard]]
		auto find(const key_type& a_key) -> iterator
		{
			return do_find<iterator>(a_key);
		}

		[[nodiscard]]
		auto find(const key_type& a_key) const -> const_iterator
		{
			return do_find<const_iterator>(a_key);
		}

		[[nodiscard]]
		auto contains(const key_type& a_key) const -> bool
		{
			return find(a_key) != end();
		}

		void reserve(size_type a_newCapacity)
		{
			if (a_newCapacity <= _capacity) {
				return;
			}

			const auto oldCapacity = _capacity;
			auto* oldEntries = get_entries();

			auto&& [newCapacity, newEntries] = [this, a_newCapacity]() -> std::pair<size_type, entry_type*> {
				constexpr auto MIN_SIZE = static_cast<std::size_t>(allocator_type::min_size());
				static_assert(MIN_SIZE > 0 && std::has_single_bit(MIN_SIZE));

				const auto capacity = std::max(std::bit_ceil<std::size_t>(a_newCapacity), MIN_SIZE);
				REX::Assert(capacity >= MIN_SIZE);

				if (capacity > max_size()) [[unlikely]] {
					REX::Throw<std::length_error>("The capacity exceeds the maximum size of the container."sv);
				}

				auto* entries = allocate(static_cast<size_type>(capacity));
				if (!entries) [[unlikely]] {
					REX::Throw<std::bad_alloc>();
				}

				return std::make_pair(static_cast<size_type>(capacity), entries);
			}();

			const auto setCapacity = [this](size_type a_newCap) noexcept -> void {
				_capacity = a_newCap;
				_free = _capacity;
				_good = 0;
			};

			if (newEntries == oldEntries) {
				std::uninitialized_default_construct_n(oldEntries + oldCapacity, newCapacity - oldCapacity);

				auto toDo = std::vector<value_type, StlAllocator<value_type>>();
				toDo.reserve(size());

				for (auto i = static_cast<size_type>(0); i < oldCapacity; i++) {
					auto& entry = oldEntries[i];
					if (entry.has_value()) {
						toDo.emplace_back(std::move(entry).steal());
					}
				}

				setCapacity(newCapacity);
				insert(std::make_move_iterator(toDo.begin()), std::make_move_iterator(toDo.end()));

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
			std::swap(_allocator, a_other._allocator);
		}

	private:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It(get_entries() + _capacity, get_entries() + _capacity);
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(entry_type* a_first) const noexcept -> It
		{
			return It(a_first, get_entries() + _capacity);
		}

		[[nodiscard]]
		static auto unwrap_key(const value_type& a_value) noexcept -> const key_type&
		{
			return traits_type::unwrap_key(a_value);
		}

		[[nodiscard]]
		auto allocate(size_type a_count) -> entry_type*
		{
			return static_cast<entry_type*>(_allocator.allocate_bytes(sizeof(entry_type) * a_count));
		}

		void deallocate(entry_type* a_entry) noexcept
		{
			_allocator.deallocate_bytes(a_entry);
		}

		template <class It>
		[[nodiscard]]
		auto do_find(const key_type& a_key) const //
			noexcept(noexcept(hash_function(a_key)) && noexcept(key_eq(a_key, a_key))) -> It
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
		[[nodiscard]]
		auto do_insert(P&& a_value) -> std::pair<iterator, bool>
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

			const auto decrement = REX::ScopeExit([this]() noexcept -> void {
				_free--;
			});

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

			// its free real-estate
			entry->emplace(std::forward<P>(a_value), _sentinel);
			return std::make_pair(make_iterator<iterator>(entry), true);
		}

		template <class P>
		[[nodiscard]]
		auto do_insert_or_assign(P&& a_value) -> std::pair<iterator, bool>
			requires(std::same_as<std::decay_t<P>, value_type>)
		{
			auto&& [it, hasInserted] = do_insert(std::forward<P>(a_value));
			if (!hasInserted) {
				it->second = std::forward<P>(a_value).second;
			}

			return std::make_pair(it, hasInserted);
		}

		[[nodiscard]]
		auto do_erase(const_iterator a_position) -> iterator
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

		void free_resources() noexcept
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

		[[nodiscard]]
		auto get_entry_for(const key_type& a_key) const //
			noexcept(noexcept(hash_function(a_key))) -> entry_type&
		{
			REX::Assert(get_entries() != nullptr);
			REX::Assert(std::has_single_bit(_capacity));

			const auto hash = hash_function(a_key);
			const auto index = hash & (_capacity - 1); // quick modulo
			return get_entries()[index];
		}

		[[nodiscard]]
		auto get_entries() const noexcept -> entry_type*
		{
			return static_cast<entry_type*>(_allocator.get_entries());
		}

		[[nodiscard]]
		auto get_free_entry() noexcept -> entry_type&
		{
			REX::Assert(_free > 0);
			REX::Assert(get_entries() != nullptr);
			REX::Assert(std::has_single_bit(_capacity));
			REX::Assert([this]() noexcept -> bool {
				const auto begin = get_entries();
				const auto end = get_entries() + _capacity;
				return std::find_if(begin, end, [](const entry_type& a_entry) noexcept -> bool {
						   return !a_entry.has_value();
					   }) != end;
			}());

			auto* entries = get_entries();
			while (entries[_good].has_value()) {
				_good = (_good + 1) & (_capacity - 1); // wrap around with quick modulo
			}

			return entries[_good];
		}

		[[nodiscard]]
		auto hash_function(const key_type& a_key) const //
			noexcept(
				std::is_nothrow_constructible_v<hash_type> &&
				std::is_nothrow_invocable_v<const hash_type&, const key_type&>) -> size_type
		{
			return static_cast<size_type>(std::invoke(hash_type(), a_key));
		}

		[[nodiscard]]
		auto key_eq(const key_type& a_lhs, const key_type& a_rhs) const //
			noexcept(
				std::is_nothrow_constructible_v<key_equal> &&
				std::is_nothrow_invocable_v<const key_equal&, const key_type&, const key_type&>) -> bool
		{
			return key_equal()(a_lhs, a_rhs);
		}

		void set_entries(entry_type* a_entries) noexcept
		{
			_allocator.set_entries(a_entries);
		}

		// members
		std::uint64_t _pad00{0}; // 0x00
		std::uint32_t _pad08{0}; // 0x08
		size_type _capacity{0};	 // 0x0C - total number of slots, always a power of 2
		size_type _free{0};		 // 0x10 - number of free slots
		size_type _good{0};		 // 0x14 - last free index
		const entry_type* _sentinel{reinterpret_cast<const entry_type*>(
			Impl::SCATTER_TABLE_SENTINEL.data())}; // 0x18 - signals end of chain
		allocator_type _allocator{};			   // 0x20
	};

	template <class Key, class T>
	class BSTScatterTableTraits
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTPair<const key_type, mapped_type>;

		// NOLINTNEXTLINE(bugprone-return-const-ref-from-parameter)
		[[nodiscard]]
		static auto unwrap_key(const value_type& a_value) noexcept -> const key_type&
		{
			return a_value.first;
		}
	};

	template <class Key>
	class BSTSetTraits
	{
	public:
		using key_type = Key;
		using mapped_type = void;
		using value_type = key_type;

		[[nodiscard]]
		static auto unwrap_key(const value_type& a_value) noexcept -> const key_type&
		{
			// NOLINTNEXTLINE(bugprone-return-const-ref-from-parameter)
			return a_value;
		}
	};

	template <std::uint32_t Size, std::uint32_t Alignment>
	class BSTScatterTableHeapAllocator
	{
	public:
		inline static constexpr auto SIZE = Size;
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Alignment);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::true_type;

		BSTScatterTableHeapAllocator() noexcept = default;
		~BSTScatterTableHeapAllocator() noexcept = default;

		BSTScatterTableHeapAllocator(const BSTScatterTableHeapAllocator&) = delete;

		BSTScatterTableHeapAllocator(BSTScatterTableHeapAllocator&& a_rhs) noexcept :
			_entries(std::exchange(a_rhs._entries, nullptr))
		{
		}

		auto operator=(const BSTScatterTableHeapAllocator&) -> BSTScatterTableHeapAllocator& = delete;

		auto operator=(BSTScatterTableHeapAllocator&& a_rhs) noexcept -> BSTScatterTableHeapAllocator&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_entries = std::exchange(a_rhs._entries, nullptr);
			return *this;
		}

		[[nodiscard]]
		static consteval auto min_size() noexcept -> size_type
		{
			return 1 << 3;
		}

		[[nodiscard]]
		auto get_entries() const noexcept -> void*
		{
			return _entries;
		}

		void set_entries(void* a_entries) noexcept
		{
			_entries = static_cast<std::byte*>(a_entries);
		}

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			REX::Assert(a_count % SIZE == 0);
			return malloc<std::byte>(a_count);
		}

		__declspec(noalias) void deallocate_bytes(void* a_ptr) noexcept
		{
			free(a_ptr);
		}

	private:
		// members
		std::uint64_t _pad00{0};	  // 0x00 (20)
		std::byte* _entries{nullptr}; // 0x08 (28)
	};

	template <std::uint32_t Size, std::uint32_t Alignment>
	class BSTScatterTableScrapAllocator
	{
	public:
		inline static constexpr auto SIZE = Size;
		inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Alignment);

		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTScatterTableScrapAllocator() :
			_allocator(MemoryManager::GetSingleton().GetThreadScrapHeap())
		{
			REX::Assert(_allocator != nullptr);
		}

		~BSTScatterTableScrapAllocator() noexcept = default;

		BSTScatterTableScrapAllocator(const BSTScatterTableScrapAllocator&) = delete;
		BSTScatterTableScrapAllocator(BSTScatterTableScrapAllocator&&) = delete;

		auto operator=(const BSTScatterTableScrapAllocator&) -> BSTScatterTableScrapAllocator& = delete;
		auto operator=(BSTScatterTableScrapAllocator&&) -> BSTScatterTableScrapAllocator& = delete;

		[[nodiscard]]
		static consteval auto min_size() noexcept -> size_type
		{
			return 1 << 3;
		}

		[[nodiscard]]
		auto get_entries() const noexcept -> void*
		{
			return _entries;
		}

		void set_entries(void* a_entries) noexcept
		{
			_entries = static_cast<std::byte*>(a_entries);
		}

		[[nodiscard]]
		__declspec(allocator) __declspec(restrict) auto allocate_bytes(size_type a_count) noexcept -> void*
		{
			REX::Assert(a_count % SIZE == 0);
			REX::Assert(_allocator != nullptr);
			return _allocator->CountedAllocate<std::byte>(a_count, ALIGNMENT_SIZE);
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
		ScrapHeap* _allocator{nullptr}; // 0x00 (20)
		std::byte* _entries{nullptr};	// 0x08 (28)
	};

	template <std::uint32_t N>
	class BSTStaticHashMapAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		static_assert(MAX_SIZE > 0 && std::has_single_bit(MAX_SIZE), "Size must be a power of 2.");

		template <std::uint32_t Size, std::uint32_t Alignment>
		class Allocator
		{
		public:
			inline static constexpr auto SIZE = Size;
			inline static constexpr auto ALIGNMENT_SIZE = static_cast<std::align_val_t>(Alignment);

			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using propagate_on_container_move_assignment = std::false_type;

			Allocator() noexcept = default;
			~Allocator() noexcept = default;

			Allocator(const Allocator&) = delete;
			Allocator(Allocator&&) = delete;

			auto operator=(const Allocator&) -> Allocator& = delete;
			auto operator=(Allocator&&) -> Allocator& = delete;

			[[nodiscard]]
			static consteval auto min_size() noexcept -> size_type
			{
				return MAX_SIZE;
			}

			[[nodiscard]]
			auto get_entries() const noexcept -> void*
			{
				return _entries;
			}

			void set_entries(void* a_entries) noexcept
			{
				REX::Assert(a_entries == _buffer.data() || a_entries == nullptr);
				_entries = static_cast<std::byte*>(a_entries);
			}

			[[nodiscard]]
			__declspec(allocator) /*__declspec(restrict)*/ auto allocate_bytes(size_type a_count) noexcept -> void*
			{
				REX::Assert(a_count % SIZE == 0);

				if (a_count > MAX_SIZE * SIZE) {
					return nullptr;
				}

				return _buffer.data();
			}

			__declspec(noalias) void deallocate_bytes([[maybe_unused]] void* a_ptr) noexcept
			{
				REX::Assert(a_ptr == _buffer.data());
			}

		private:
			// members
			alignas(ALIGNMENT_SIZE) std::array<std::byte, MAX_SIZE * SIZE> _buffer{
				static_cast<std::byte>(0)
			}; // 0x00 (20)
			std::byte* _entries{nullptr}; // 0x??
		};
	};

	template <class Key, class T, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTHashMap = BSTScatterTable<Hash, KeyEqual, BSTScatterTableTraits<Key, T>, BSTScatterTableHeapAllocator>;

	template <class Key, class T, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTScrapHashMap =
		BSTScatterTable<Hash, KeyEqual, BSTScatterTableTraits<Key, T>, BSTScatterTableScrapAllocator>;

	template <class Key, class T, std::uint32_t N, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTStaticHashMap = BSTScatterTable<
		Hash,
		KeyEqual,
		BSTScatterTableTraits<Key, T>,
		BSTStaticHashMapAllocator<N>::template Allocator>;

	template <class Key, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTSet = BSTScatterTable<Hash, KeyEqual, BSTSetTraits<Key>, BSTScatterTableHeapAllocator>;

	template <class Key, class Hash = BSCRC32<Key>, class KeyEqual = std::equal_to<Key>>
	using BSTScrapSet = BSTScatterTable<Hash, KeyEqual, BSTSetTraits<Key>, BSTScatterTableScrapAllocator>;
}
