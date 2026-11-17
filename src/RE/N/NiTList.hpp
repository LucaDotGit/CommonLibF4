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
		NiTListItem* next{nullptr}; // 0x00
		NiTListItem* prev{nullptr}; // 0x08
		T element{};				// 0x10
	};

	template <class T, class Allocator>
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
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_current(a_rhs._current)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(const iterator_base<V>& a_rhs) noexcept -> iterator_base&
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_current = a_rhs._current;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			constexpr auto operator*() const noexcept -> reference
			{
				return _current->element;
			}

			[[nodiscard]]
			constexpr auto operator->() const noexcept -> pointer
			{
				return std::addressof(_current->element);
			}

			[[nodiscard]]
			constexpr auto operator==(const iterator_base& a_rhs) const noexcept -> bool
			{
				return _current == a_rhs._current;
			}

		protected:
			template <class, class>
			friend class NiTListBase;

			explicit iterator_base(Node* a_node) noexcept :
				_current(a_node)
			{
			}

		private:
			// members
			Node* _current{nullptr}; // 0x00
		};

		template <class U>
		class forward_iterator : public iterator_base<U> // 0x00
		{
		public:
			constexpr auto operator++() noexcept -> forward_iterator&
			{
				REX::Assert(this->_current);
				this->_current = this->_current->next;
				return *this;
			}

			[[nodiscard]]
			constexpr auto operator++(std::int32_t) noexcept -> forward_iterator
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}
		};

		template <class U>
		class backward_iterator : public iterator_base<U> // 0x00
		{
		public:
			auto operator++() noexcept -> backward_iterator&
			{
				REX::Assert(this->_current);
				this->_current = this->_current->prev;
				return *this;
			}

			[[nodiscard]]
			auto operator++(std::int32_t) noexcept -> backward_iterator
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}
		};

		class AntiBloatAllocator : public Allocator // 0x00
		{
		public:
			// members
			std::uint32_t size{0}; // 0x??
		};

	public:
		using allocator_type = AntiBloatAllocator;
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

		NiTListBase(NiTListBase&& a_rhs) noexcept :
			_head(std::exchange(a_rhs._head, nullptr)),
			_tail(std::exchange(a_rhs._tail, nullptr)),
			_allocator(std::move(a_rhs._allocator))
		{
		}

		auto operator=(const NiTListBase&) -> NiTListBase& = delete;

		auto operator=(NiTListBase&&) -> NiTListBase& = delete;

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			REX::Assert(!empty());
			return *rbegin();
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			REX::Assert(!empty());
			return *rbegin();
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>(_head);
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(_head);
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
			return make_iterator<reverse_iterator>(_tail);
		}

		[[nodiscard]]
		auto rbegin() const noexcept -> const_reverse_iterator
		{
			return make_iterator<const_reverse_iterator>(_tail);
		}

		[[nodiscard]]
		auto crbegin() const noexcept -> const_reverse_iterator
		{
			return rbegin();
		}

		[[nodiscard]]
		auto rend() noexcept -> reverse_iterator
		{
			return make_iterator<reverse_iterator>();
		}

		[[nodiscard]]
		auto rend() const noexcept -> const_reverse_iterator
		{
			return make_iterator<const_reverse_iterator>();
		}

		[[nodiscard]]
		auto crend() const noexcept -> const_reverse_iterator
		{
			return rend();
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _allocator.size;
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
			return _allocator.size == 0;
		}

		void swap(NiTListBase& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_head, a_other._head);
			std::swap(_tail, a_other._tail);
			std::swap(_allocator, a_other._allocator);
		}

	protected:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It();
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(Node* a_node) const noexcept -> It
		{
			return empty() ? It(nullptr) : It(a_node);
		}

		void clear() noexcept
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
		NiTListItem<T>* _head{nullptr}; // 0x00
		NiTListItem<T>* _tail{nullptr}; // 0x08
		allocator_type _allocator{};	// 0x10
	};

	template <class T, class Allocator>
	class NiTPointerListBase : public NiTListBase<T, Allocator> // 0x00
	{
	public:
	};

	template <class T>
	class NiTList : public NiTPointerListBase<T, NiTDefaultAllocator<T>> // 0x00
	{
	};
}
