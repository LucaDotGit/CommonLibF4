#pragma once

#include "RE/N/NiMemManager.hpp"

namespace RE
{
	template <class T, class Allocator>
	class NiTArray
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		template <class U>
		class iterator_base
		{
		public:
			using value_type = std::remove_const_t<U>;
			using size_type = std::uint16_t;
			using difference_type = std::int16_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::bidirectional_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _pos(a_rhs._pos),
				  _head(a_rhs._head),
				  _tail(a_rhs._tail)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_pos = a_rhs._pos;
				_head = a_rhs._head;
				_tail = a_rhs._tail;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				REX::Assert(validate());
				return *_pos;
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				REX::Assert(_head == a_rhs._head);
				REX::Assert(_tail == a_rhs._tail);
				return _pos == a_rhs._pos;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				REX::Assert(validate());
				do {
					_pos++;
				}
				while (_pos < _tail && !slot_filled());
				return *this;
			}

			iterator_base operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

			iterator_base& operator--() noexcept
			{
				REX::Assert(validate());
				do {
					_pos--;
				}
				while (_head <= _pos && !slot_filled());
				return *this;
			}

			iterator_base operator--(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator--();
				return temp;
			}

		protected:
			template <class, class>
			friend class NiTArray;

			iterator_base(pointer a_position, pointer a_head, pointer a_tail) noexcept
				: _pos(a_position),
				  _head(a_head),
				  _tail(a_tail)
			{
			}

			[[nodiscard]] bool validate() const noexcept
			{
				return _pos != nullptr &&
					   _head != nullptr &&
					   _tail != nullptr &&
					   _head <= _pos &&
					   _pos < _tail;
			}

			[[nodiscard]] bool slot_filled() const noexcept
			{
				REX::Assert(validate());
				return static_cast<bool>(*_pos);
			}

		private:
			// members
			pointer _pos{ nullptr };  // 00
			pointer _head{ nullptr }; // 08
			pointer _tail{ nullptr }; // 10
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		explicit NiTArray(size_type a_maxSize = 0, size_type a_growBy = 1)
			: _capacity(a_maxSize),
			  _growthSize(a_growBy)
		{
			if (capacity() > 0) {
				_data = allocator_type::allocate(capacity());
			}
		}

		virtual ~NiTArray() // 00
		{
			allocator_type::deallocate(_data);
		}

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

		[[nodiscard]] pointer data() noexcept { return _data; }
		[[nodiscard]] const_pointer data() const noexcept { return _data; }

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(0); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(0); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return make_iterator<const_iterator>(0); }

		[[nodiscard]] iterator end() noexcept { return make_iterator<iterator>(_capacity); }
		[[nodiscard]] const_iterator end() const noexcept { return make_iterator<const_iterator>(_capacity); }
		[[nodiscard]] const_iterator cend() const noexcept { return make_iterator<const_iterator>(_capacity); }

		[[nodiscard]] size_type size() const noexcept { return _size; }
		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		void swap(NiTArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
			std::swap(_capacity, a_other._capacity);
			std::swap(_freeIndex, a_other._freeIndex);
			std::swap(_size, a_other._size);
			std::swap(_growthSize, a_other._growthSize);
		}

	private:
		template <class It>
		[[nodiscard]] It make_iterator(size_type a_position) const noexcept
		{
			return It(_data + a_position, _data, _data + _capacity);
		}

		// members
		pointer _data{ nullptr };	// 08
		size_type _capacity{ 0 };	// 10
		size_type _freeIndex{ 0 };	// 12
		size_type _size{ 0 };		// 14
		size_type _growthSize{ 0 }; // 16
	};

	template <class T>
	using NiTObjectArray = NiTArray<T, NiTNewInterface<T>>;

	template <class T>
	using NiTPrimitiveArray = NiTArray<T, NiTMallocInterface<T>>;

	template <class T, class Allocator>
	void swap(NiTArray<T, Allocator>& a_lhs, NiTArray<T, Allocator>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}
