#pragma once

#include "RE/N/NiMemManager.hpp"

namespace RE
{
	template <class T, class Allocator>
	class NiTLargeArray
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

	private:
		template <class U>
		class iterator_base
		{
		public:
			using value_type = std::remove_const_t<U>;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::bidirectional_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(const iterator_base<V>& a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_pos(a_rhs._pos),
				_head(a_rhs._head),
				_tail(a_rhs._tail)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(const iterator_base<V>& a_rhs) noexcept -> iterator_base&
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_pos = a_rhs._pos;
				_head = a_rhs._head;
				_tail = a_rhs._tail;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() const noexcept -> reference
			{
				REX::Assert(validate());
				return *_pos;
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
				REX::Assert(_head == a_rhs._head);
				REX::Assert(_tail == a_rhs._tail);
				return _pos == a_rhs._pos;
			}

			auto operator++() noexcept -> iterator_base&
			{
				REX::Assert(validate());
				do {
					_pos++;
				}
				while (_pos < _tail && !slot_filled());
				return *this;
			}

			auto operator++(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

			auto operator--() noexcept -> iterator_base&
			{
				REX::Assert(validate());
				do {
					_pos--;
				}
				while (_head <= _pos && !slot_filled());
				return *this;
			}

			auto operator--(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator--();
				return temp;
			}

		protected:
			template <class, class>
			friend class NiTLargeArray;

			iterator_base(pointer a_position, pointer a_head, pointer a_tail) noexcept :
				_pos(a_position),
				_head(a_head),
				_tail(a_tail)
			{
			}

			[[nodiscard]]
			auto validate() const noexcept -> bool
			{
				return _pos != nullptr && _head != nullptr && _tail != nullptr && _head <= _pos && _pos < _tail;
			}

			[[nodiscard]]
			auto slot_filled() const noexcept -> bool
			{
				REX::Assert(validate());
				return static_cast<bool>(*_pos);
			}

		private:
			// members
			pointer _pos{nullptr};	// 0x00
			pointer _head{nullptr}; // 0x08
			pointer _tail{nullptr}; // 0x10
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		NiTLargeArray() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		explicit NiTLargeArray(size_type a_maxSize, size_type a_growBy = 1) :
			_capacity(a_maxSize),
			_growthSize(a_growBy)
		{
			if (capacity() == 0) {
				return;
			}

			auto* newData = _allocator.allocate(capacity());
			if (!newData) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			_data = newData;
		}

		virtual ~NiTLargeArray() // 0x00
		{
			_allocator.deallocate(_data);
		}

		NiTLargeArray(const NiTLargeArray&) = delete;
		NiTLargeArray(NiTLargeArray&&) noexcept = default;

		auto operator=(const NiTLargeArray&) -> NiTLargeArray& = delete;
		auto operator=(NiTLargeArray&&) noexcept -> NiTLargeArray& = default;

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
			return _data;
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return _data;
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>(0);
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(0);
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(0);
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return make_iterator<iterator>(_capacity);
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(_capacity);
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(_capacity);
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _size;
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

		void swap(NiTLargeArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_data, a_other._data);
			std::swap(_capacity, a_other._capacity);
			std::swap(_freeIndex, a_other._freeIndex);
			std::swap(_size, a_other._size);
			std::swap(_growthSize, a_other._growthSize);
		}

	private:
		template <class It>
		[[nodiscard]]
		auto make_iterator(size_type a_position) const noexcept -> It
		{
			return It(_data + a_position, _data, _data + _capacity);
		}

		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		allocator_type _allocator{}; // 0x08
		pointer _data{nullptr};		 // 0x08
		size_type _capacity{0};		 // 0x10
		size_type _freeIndex{0};	 // 0x12
		size_type _size{0};			 // 0x14
		size_type _growthSize{0};	 // 0x16
	};

	template <class T>
	using NiTLargeObjectArray = NiTLargeArray<T, NiTNewInterface<T>>;

	template <class T>
	using NiTLargePrimitiveArray = NiTLargeArray<T, NiTMallocInterface<T>>;
}
