#pragma once

#include "RE/H/hkContainerHeapAllocator.hpp"

namespace RE
{
	template <class T, class Allocator = hkContainerHeapAllocator>
	class hkArray
	{
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::int32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		hkArray() = default;

		~hkArray()
		{
			if (capacity() == 0) {
				return;
			}

			clear();

			auto& allocator = Allocator::GetAllocator();
			allocator.free(data(), capacity() * sizeof(value_type));

			_data = nullptr;
			_capacityAndFlags = 0;
		}

		explicit hkArray(size_type a_count)
		{
			resize(a_count);
		}

		hkArray(size_type a_count, const_reference a_value)
		{
			assign(a_count, a_value);
		}

		template <class InputIt>
		hkArray(InputIt a_first, InputIt a_last)
			requires(std::derived_from<typename std::iterator_traits<InputIt>::iterator_category, std::input_iterator_tag>)
		{
			assign(a_first, a_last);
		}

		hkArray(const hkArray& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		hkArray(hkArray&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
			: _data(std::exchange(a_rhs._data, nullptr)),
			  _size(std::exchange(a_rhs._size, 0)),
			  _capacityAndFlags(std::exchange(a_rhs._capacityAndFlags, 0))
		{
		}

		hkArray(std::initializer_list<T> a_ilist)
			: hkArray(a_ilist.begin(), a_ilist.end())
		{
		}

		hkArray& operator=(const hkArray& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		hkArray& operator=(hkArray&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			clear();

			_data = std::exchange(a_rhs._data, nullptr);
			_size = std::exchange(a_rhs._size, 0);
			_capacityAndFlags = std::exchange(a_rhs._capacityAndFlags, 0);

			return *this;
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
		[[nodiscard]] size_type capacity() const noexcept { return _capacityAndFlags & kCapacityMask; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] bool empty() const noexcept { return size() == 0; }

		template <class ForwardIt>
		void assign(ForwardIt a_first, ForwardIt a_last)
		{
			auto out = begin();
			const auto outLast = end();

			for (; out != outLast && a_first != a_last; a_first++, out++) {
				*out = *a_first;
			}

			if (out != outLast) {
				erase(out, outLast);
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

		void swap(hkArray& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
			std::swap(_size, a_other._size);
			std::swap(_capacityAndFlags, a_other._capacityAndFlags);
		}

	private:
		enum Flags : size_type
		{
			kCapacityMask = static_cast<size_type>(0x3FFFFFFF),
			kFlagMask = static_cast<size_type>(0xC0000000),
			kDontDeallocateFlag = static_cast<size_type>(0x80000000),
			kForceSigned = static_cast<size_type>(0xFFFFFFFF)
		};

		template <class, class>
		friend class hkArray;

		[[nodiscard]] iterator decay_iterator(const_iterator a_iter) noexcept
		{
			return const_cast<pointer>(std::addressof(*a_iter));
		}

		void reserve_auto(size_type a_capacity)
		{
			if (a_capacity <= capacity()) {
				return;
			}

			// grow by 1.5x, rounding up
			const auto grow = a_capacity + (a_capacity >> 1) + (a_capacity & 1);
			reserve_exact(grow);
		}

		void reserve_exact(size_type a_capacity)
		{
			REX::Assert(a_capacity <= kCapacityMask);
			if (a_capacity <= capacity()) {
				return;
			}

			auto& allocator = hkContainerHeapAllocator::GetAllocator();

			auto* newData = calloc<T>(a_capacity);
			if (!newData) {
				throw std::bad_alloc();
			}

			const auto oldSize = size() * sizeof(T);
			std::copy_n(_data, oldSize, newData);

			if ((_capacityAndFlags & kDontDeallocateFlag) == 0) {
				allocator.free(_data);
			}

			_data = newData;
			_capacityAndFlags &= ~kCapacityMask;
			_capacityAndFlags |= a_capacity & kCapacityMask;
		}

		void resize_impl(size_type a_count, const value_type* a_value)
		{
			if (a_count == size()) {
				return;
			}

			reserve_auto(a_count);

			if (a_count > size()) {
				std::uninitialized_fill_n(data() + size(), a_count - size(), a_value ? *a_value : value_type{});
			}
			else {
				std::destroy(data() + a_count, data() + size());
			}

			_size = a_count;
		}

		// members
		T* _data{ nullptr };								// 00
		size_type _size{ 0 };								// 08
		size_type _capacityAndFlags{ kDontDeallocateFlag }; // 0C
	};
	static_assert(sizeof(hkArray<std::any>) == 0x10);
}
