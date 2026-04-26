#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T>
	class BSSimpleList
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		class node_type
		{
		public:
			GAME_HEAP_REDEFINE_NEW(node_type);

			// members
			value_type value{};			// 00
			node_type* next{ nullptr }; // ??
		};

		template <class U>
		class iterator_base
		{
		public:
			using difference_type = std::int32_t;
			using value_type = std::remove_const_t<U>;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			iterator_base(iterator_base<V> a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _proxy(a_rhs._proxy),
				  _current(a_rhs._current)
			{
			}

			template <class V>
			iterator_base& operator=(iterator_base<V> a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_current = a_rhs._current;
				return *this;
			}

			[[nodiscard]] reference operator*() noexcept
			{
				REX::Assert(_current && _current != nullptr);
				return get()->value;
			}

			[[nodiscard]] pointer operator->() noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				REX::Assert(_proxy == a_rhs._proxy);
				return _current == a_rhs._current;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				if (_current) {
					REX::Assert(_current != nullptr);
					_current = get()->next;
				}
				else {
					*this = _proxy->begin();
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
			template <class>
			friend class BSSimpleList;

			iterator_base(BSSimpleList<value_type>* a_proxy, node_type* a_current) noexcept
				: _proxy(a_proxy),
				  _current(a_current)
			{
			}

			iterator_base(BSSimpleList<value_type>* a_proxy, std::optional<node_type*> a_current) noexcept
				: _proxy(a_proxy),
				  _current(a_current)
			{
			}

			[[nodiscard]] node_type* get() const noexcept
			{
				REX::Assert(_current && _current != nullptr);
				return _current.value();
			}

			[[nodiscard]] auto make_mutable() const noexcept
			{
				return iterator_base<std::remove_const_t<value_type>>(_proxy, _current);
			}

		private:
			// members
			BSSimpleList<value_type>* _proxy{ nullptr };   // 00
			std::optional<node_type*> _current{ nullptr }; // 08
		};

		template <class F>
		class counted_function_iterator
		{
		public:
			using value_type = std::remove_const_t<std::remove_reference_t<decltype(std::declval<F>()())>>;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;

			counted_function_iterator() = default;

			counted_function_iterator(F a_func, size_type a_count)
				: _func(std::move(a_func)),
				  _left(a_count)
			{
			}

			~counted_function_iterator() noexcept = default;

			counted_function_iterator(const counted_function_iterator&) = default;
			counted_function_iterator(counted_function_iterator&&) noexcept = default;

			counted_function_iterator& operator=(const counted_function_iterator&) = default;
			counted_function_iterator& operator=(counted_function_iterator&&) noexcept = default;

			[[nodiscard]] reference operator*() const
				noexcept(noexcept(std::declval<F>()()))
			{
				REX::Assert(_func != std::nullopt);
				return std::invoke(*_func);
			}

			[[nodiscard]] pointer operator->() const
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			[[nodiscard]] friend bool operator==(
				const counted_function_iterator& a_lhs,
				const counted_function_iterator& a_rhs) noexcept
			{
				return a_lhs._left == a_rhs._left;
			}

			counted_function_iterator& operator++() noexcept
			{
				REX::Assert(_left > 0);
				_left -= 1;
				return *this;
			}

			counted_function_iterator operator++(std::int32_t) noexcept
			{
				auto temp = counted_function_iterator(*this);
				operator++();
				return temp;
			}

		private:
			// members
			std::optional<F> _func; // 00
			size_type _left{ 0 };	// ??
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSSimpleList() = default;

		~BSSimpleList()
		{
			clear();
		}

		explicit BSSimpleList(size_type a_count)
		{
			assign(a_count, value_type());
		}

		template <class InputIt>
		BSSimpleList(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		BSSimpleList(std::initializer_list<value_type> a_init)
		{
			assign(a_init.begin(), a_init.end());
		}

		BSSimpleList(const BSSimpleList& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSSimpleList(BSSimpleList&& a_rhs) noexcept
			: _root(std::exchange(a_rhs._root, node_type()))
		{
		}

		BSSimpleList& operator=(std::initializer_list<value_type> a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		BSSimpleList& operator=(const BSSimpleList& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		BSSimpleList& operator=(BSSimpleList&& a_rhs) noexcept
		{
			clear();
			_root = std::exchange(a_rhs._root, node_type());
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSSimpleList);

		void assign(size_type a_count, const_reference a_value)
		{
			clear();
			insert_after(cbefore_begin(), a_count, a_value);
		}

		template <class InputIt>
		void assign(InputIt a_first, InputIt a_last)
		{
			clear();
			insert_after(cbefore_begin(), std::move(a_first), std::move(a_last));
		}

		void assign(std::initializer_list<value_type> a_ilist)
		{
			assign(a_ilist.begin(), a_ilist.end());
		}

		[[nodiscard]] reference front() noexcept
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]] reference back() noexcept
		{
			REX::Assert(!empty());
			return *std::prev(end());
		}

		[[nodiscard]] const_reference front() const noexcept
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]] const_reference back() const noexcept
		{
			REX::Assert(!empty());
			return *std::prev(end());
		}

		[[nodiscard]] iterator before_begin() noexcept { return make_iterator<iterator>(std::nullopt); }
		[[nodiscard]] const_iterator before_begin() const noexcept { return make_iterator<const_iterator>(std::nullopt); }
		[[nodiscard]] const_iterator cbefore_begin() const noexcept { return before_begin(); }

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(nullptr); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(nullptr); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return !_root.next && !_root.value; }

		iterator insert_after(const_iterator a_position, const_reference a_value)
		{
			return emplace_after(a_position, a_value);
		}

		iterator insert_after(const_iterator a_position, value_type&& a_value)
		{
			return emplace_after(a_position, std::move(a_value));
		}

		iterator insert_after(const_iterator a_position, size_type a_count, const_reference a_value)
		{
			const auto gen = [&a_value]() noexcept -> const_reference { return a_value; };
			return insert_after(
				a_position,
				counted_function_iterator{ gen, a_count },
				counted_function_iterator<decltype(gen)>());
		}

		template <class InputIt>
		iterator insert_after(const_iterator a_position, InputIt a_first, InputIt a_last)
		{
			const auto [first, last] = allocate_range(std::move(a_first), std::move(a_last));
			return insert_range(a_position, first, last);
		}

		iterator insert_after(const_iterator a_position, std::initializer_list<value_type> a_ilist)
		{
			return insert_after(
				a_position,
				a_ilist.begin(),
				a_ilist.end());
		}

		template <class... Args>
		iterator emplace_after(const_iterator a_position, Args&&... a_args)
		{
			const auto node = new node_type{ { std::forward<Args>(a_args)... }, nullptr };
			return insert_range(a_position, node, node);
		}

		iterator erase_after(const_iterator a_position)
		{
			return erase_after(a_position, ++a_position);
		}

		iterator erase_after(const_iterator a_first, const_iterator a_last)
		{
			REX::Assert(a_first != cend());
			if (a_first != a_last) {
				const auto delRange = [](node_type* a_first, node_type* a_last) {
					while (a_first != a_last) {
						auto prev = a_first;
						a_first = a_first->next;
						delete prev;
					}
				};

				if (a_first == cbefore_begin()) {
					delRange(_root.next, a_last.get());
					if (a_last == cend()) {
						_root = node_type();
					}
					else {
						// invalidates a_last, nonconforming
						_root = std::move(*(a_last.get()));
						delete a_last.get();
						return begin();
					}
				}
				else {
					delRange(a_first.get()->next, a_last.get());
					a_first.get()->next = a_last.get();
				}
			}

			return a_last.make_mutable();
		}

		void push_front(const_reference a_value)
		{
			emplace_front(a_value);
		}

		void push_front(value_type&& a_value)
		{
			emplace_front(std::move(a_value));
		}

		template <class... Args>
		reference emplace_front(Args&&... a_args)
		{
			return *emplace_after(cbefore_begin(), std::forward<Args>(a_args)...);
		}

		void pop_front()
		{
			erase_after(cbefore_begin());
		}

		void push_back(const_reference a_value)
		{
			emplace_back(a_value);
		}

		void push_back(value_type&& a_value)
		{
			emplace_back(std::move(a_value));
		}

		template <class... Args>
		reference emplace_back(Args&&... a_args)
		{
			return *emplace_after(cend(), std::forward<Args>(a_args)...);
		}

		void resize(size_type a_count)
		{
			resize(a_count, value_type());
		}

		void resize(size_type a_count, const value_type& a_value)
		{
			auto n = static_cast<size_type>(-1);
			auto it = cbefore_begin();
			auto prev = const_iterator();

			while (++n != a_count) {
				prev = it;
				if (++it == cend()) {
					break;
				}
			}

			if (it != cend()) {
				REX::Assert(n == a_count);
				erase_after(it, cend());
			}
			else {
				REX::Assert(n != a_count);
				insert_after(prev, a_count - n, a_value);
			}
		}

		void clear()
		{
			erase_after(cbefore_begin(), cend());
		}

		void swap(BSSimpleList& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_root.value, a_other._root.value);
			std::swap(_root.next, a_other._root.next);
		}

	private:
		template <class It>
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It(const_cast<BSSimpleList*>(this), !empty() ? std::addressof(const_cast<node_type&>(_root)) : nullptr);
		}

		template <class It>
		[[nodiscard]] It make_iterator(node_type* a_current) const noexcept
		{
			return It(const_cast<BSSimpleList*>(this), a_current);
		}

		template <class It>
		[[nodiscard]] It make_iterator(std::optional<node_type*> a_current) const noexcept
		{
			return It(const_cast<BSSimpleList*>(this), a_current);
		}

		template <class InputIt>
		[[nodiscard]] static std::pair<node_type*, node_type*> allocate_range(InputIt a_first, InputIt a_last)
		{
			std::pair<node_type*, node_type*> range{ nullptr, nullptr };
			if (a_first != a_last) {
				range.first = new node_type{ *a_first };
				a_first++;

				range.second = range.first;
				for (; a_first != a_last; a_first++) {
					range.second->next = new node_type{ *a_first };
					range.second = range.second->next;
				}
			}

			return range;
		}

		// assumes ownership of given range
		[[nodiscard]] iterator insert_range(const_iterator a_position, node_type* a_first, node_type* a_last)
		{
			REX::Assert(a_position != cend());
			if (a_first == nullptr) {
				REX::Assert(a_last == nullptr);
				return a_position.make_mutable();
			}

			REX::Assert(a_last != nullptr);

			if (a_position == cbefore_begin()) {
				if (_root.value) {
					_root.next = new node_type{ std::move(_root.value), _root.next };
				}

				a_last->next = _root.next;
				_root = std::move(*a_first);
				delete a_first;
			}
			else {
				a_last->next = a_position.get()->next;
				a_position.get()->next = a_first;
			}

			return iterator(this, a_last);
		}

		// members
		node_type _root{}; // 00
	};

	template <class T>
	void swap(BSSimpleList<T>& a_lhs, BSSimpleList<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
