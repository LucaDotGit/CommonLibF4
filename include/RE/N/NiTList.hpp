#pragma once

#include "RE/N/NiTDefaultAllocator.hpp"

namespace RE
{
	template <class T>
	class NiTListItem
	{
	public:
		using value_type = T;

		// members
		NiTListItem* next{ nullptr }; // 00
		NiTListItem* prev{ nullptr }; // 08
		T element{};				  // 10
	};

	template <class Allocator, class T>
	class NiTListBase
	{
	private:
		using Node = NiTListItem<T>;

	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

	protected:
		template <class U>
		class iterator_base
		{
		public:
			using value_type = U;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using pointer = U*;
			using reference = U&;
			using iterator_category = std::bidirectional_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _current(a_rhs._current)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_current = a_rhs._current;
				return *this;
			}

			[[nodiscard]] constexpr reference operator*() const noexcept
			{
				return _current->element;
			}

			[[nodiscard]] constexpr pointer operator->() const noexcept
			{
				return std::addressof(_current->element);
			}

			[[nodiscard]] constexpr bool operator==(const iterator_base& a_rhs) const noexcept
			{
				return _current == a_rhs._current;
			}

			[[nodiscard]] constexpr bool operator!=(const iterator_base& a_rhs) const noexcept
			{
				return !(*this == a_rhs);
			}

		protected:
			template <class, class>
			friend class NiTListBase;

			iterator_base(Node* a_node) noexcept
				: _current(a_node)
			{
			}

		private:
			// members
			Node* _current{ nullptr }; // 00
		};

		template <class U>
		class forward_iterator
			: public iterator_base<U>
		{
		public:
			constexpr forward_iterator& operator++() noexcept
			{
				REX::Assert(this->_current);
				this->_current = this->_current->next;
				return *this;
			}

			[[nodiscard]] constexpr forward_iterator operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}
		};

		template <class U>
		class backward_iterator
			: public iterator_base<U>
		{
		public:
			backward_iterator& operator++() noexcept
			{
				REX::Assert(this->_current);
				this->_current = this->_current->prev;
				return *this;
			}

			[[nodiscard]] backward_iterator operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}
		};

		class AntiBloatAllocator
			: public Allocator // 00
		{
		public:
			// members
			std::uint32_t size{ 0 }; // ??
		};

	public:
		using iterator = forward_iterator<value_type>;
		using const_iterator = forward_iterator<const value_type>;
		using reverse_iterator = backward_iterator<value_type>;
		using const_reverse_iterator = backward_iterator<const value_type>;

		NiTListBase() = default;

		~NiTListBase() noexcept
		{
			clear();
		}

		NiTListBase(const NiTListBase&) = delete;

		NiTListBase(NiTListBase&& a_rhs) noexcept
			: _head(std::exchange(a_rhs._head, nullptr)),
			  _tail(std::exchange(a_rhs._tail, nullptr)),
			  _allocator(std::move(a_rhs._allocator))
		{
		}

		NiTListBase& operator=(const NiTListBase&) = delete;

		NiTListBase& operator=(NiTListBase&&) = delete;

		[[nodiscard]] reference front() noexcept
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]] const_reference front() const noexcept
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]] reference back() noexcept
		{
			REX::Assert(!empty());
			return *rbegin();
		}

		[[nodiscard]] const_reference back() const noexcept
		{
			REX::Assert(!empty());
			return *rbegin();
		}

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(_head); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(_head); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return make_iterator<reverse_iterator>(_tail); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return make_iterator<const_reverse_iterator>(_tail); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return rbegin(); }

		[[nodiscard]] reverse_iterator rend() noexcept { return make_iterator<reverse_iterator>(); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return make_iterator<const_reverse_iterator>(); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return rend(); }

		[[nodiscard]] size_type size() const noexcept { return _allocator.size; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return _allocator.size == 0; }

	protected:
		template <class It>
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It();
		}

		template <class It>
		[[nodiscard]] It make_iterator(Node* a_node) const noexcept
		{
			return empty() ? It(nullptr) : It(a_node);
		}

		void clear()
		{
			auto* current = _head;
			while (current) {
				auto* next = current->next;

				current->~Node();
				_allocator.Deallocate(current);

				current = next;
			}

			_head = nullptr;
			_tail = nullptr;

			_allocator.size = 0;
		}

		// members
		NiTListItem<T>* _head{ nullptr }; // 00
		NiTListItem<T>* _tail{ nullptr }; // 08
		AntiBloatAllocator _allocator{};  // 10
	};

	template <class Allocator, class T>
	class NiTPointerListBase
		: public NiTListBase<Allocator, T> // 00
	{
	public:
	};

	template <class T>
	class NiTList
		: public NiTPointerListBase<NiTDefaultAllocator<T>, T> // 00
	{
	public:
	};
}
