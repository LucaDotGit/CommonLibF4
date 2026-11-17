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

		hkArray() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		~hkArray() noexcept
		{
			if (capacity() == 0) {
				return;
			}

			clear();

			auto& allocator = Allocator::GetAllocator();
			allocator.free(_data, REX::ToUnsigned(capacity()) * sizeof(value_type));

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

		template <std::input_iterator InputIt>
		hkArray(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		hkArray(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		hkArray(std::initializer_list<T> a_initList) :
			hkArray{a_initList.begin(), a_initList.end()}
		{
		}

		hkArray(const hkArray& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		hkArray(hkArray&& a_rhs) noexcept(
			std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>) :
			_data(std::exchange(a_rhs._data, nullptr)),
			_size(std::exchange(a_rhs._size, 0)),
			_capacityAndFlags(std::exchange(a_rhs._capacityAndFlags, 0))
		{
		}

		auto operator=(std::initializer_list<value_type> a_rhs) -> hkArray&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(const hkArray& a_rhs) -> hkArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(hkArray&& a_rhs)
			noexcept(std::is_nothrow_move_assignable_v<allocator_type> && std::is_nothrow_move_assignable_v<value_type>)
				-> hkArray&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_size = std::exchange(a_rhs._size, 0);
			_capacityAndFlags = std::exchange(a_rhs._capacityAndFlags, 0);

			return *this;
		}

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
			return data();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return begin() + size();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return begin() + size();
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
			return _capacityAndFlags & CapacityMask;
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

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void append_range(Range&& a_range)
		{
			insert(end(), std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <std::input_iterator InputIt>
		auto insert(const_iterator a_position, InputIt a_first, InputIt a_last) -> iterator
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

		auto insert(const_iterator a_position, const value_type& a_value) -> iterator
		{
			return emplace(a_position, a_value);
		}

		auto insert(const_iterator a_position, value_type&& a_value) -> iterator
		{
			return emplace(a_position, std::move(a_value));
		}

		auto insert(const_iterator a_position, std::initializer_list<value_type> a_initList) -> iterator
		{
			return insert(a_position, a_initList.begin(), a_initList.end());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		constexpr void insert_range(size_type a_position, Range&& a_range)
		{
			insert(a_position, std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <class... Args>
		auto emplace(const_iterator a_position, Args&&... a_args) -> iterator
			requires(std::is_constructible_v<value_type, Args&&...>)
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

		auto erase(const_iterator a_first, const_iterator a_last) -> iterator
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

		auto erase(const_iterator a_position) -> iterator
		{
			return erase(a_position, std::next(a_position));
		}

		template <class... Args>
		auto emplace_back(Args&&... a_args) -> reference
			requires(std::is_constructible_v<value_type, Args&&...>)
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

		void reserve(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			reserve_exact(a_newCapacity);
		}

		void resize(size_type a_newSize)
		{
			resize_impl(a_newSize, nullptr);
		}

		void resize(size_type a_newSize, const value_type& a_value)
		{
			resize_impl(a_newSize, std::addressof(a_value));
		}

		void shrink_to_fit()
		{
			reserve_exact(size());
		}

		void clear() noexcept
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
		template <class, class>
		friend class hkArray;

		enum Flags : size_type
		{
			CapacityMask = static_cast<size_type>(0x3FFF'FFFF),
			FlagMask = static_cast<size_type>(0xC000'0000),
			DontDeallocateFlag = static_cast<size_type>(0x8000'0000),
			ForceSigned = static_cast<size_type>(0xFFFF'FFFF)
		};

		[[nodiscard]]
		auto decay_iterator(const_iterator a_it) noexcept -> iterator
		{
			return const_cast<pointer>(std::addressof(*a_it));
		}

		void reserve_auto(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			// grow by 1.5x, rounding up
			const auto grow = a_newCapacity + (a_newCapacity >> 1) + (a_newCapacity & 1);
			reserve_exact(grow);
		}

		void reserve_exact(size_type a_newCapacity)
		{
			REX::Assert(a_newCapacity <= CapacityMask);
			if (a_newCapacity <= capacity()) {
				return;
			}

			auto& allocator = hkContainerHeapAllocator::GetAllocator();

			auto* newData = malloc<T>(a_newCapacity);
			if (!newData) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			const auto oldSize = size() * sizeof(T);
			std::copy_n(_data, oldSize, newData);

			if ((_capacityAndFlags & DontDeallocateFlag) == 0) {
				allocator.free(_data);
			}

			_data = newData;
			_capacityAndFlags &= ~CapacityMask;
			_capacityAndFlags |= a_newCapacity & CapacityMask;
		}

		void resize_impl(size_type a_newSize, const value_type* a_value)
		{
			if (a_newSize == size()) {
				return;
			}

			if (a_newSize < size()) {
				erase(begin() + a_newSize, end());
				return;
			}

			reserve_auto(a_newSize);

			auto range = std::span<value_type>{data() + size(), a_newSize - size()};

			if (a_value) {
				std::uninitialized_fill_n(range.begin(), range.size(), *a_value);
			}
			else {
				std::uninitialized_default_construct_n(range.begin(), range.size());
			}

			_size = a_newSize;
		}

		// members
		T* _data{nullptr};								 // 0x00
		size_type _size{0};								 // 0x08
		size_type _capacityAndFlags{DontDeallocateFlag}; // 0x0C
	};

	static_assert(sizeof(hkArray<std::any>) == 0x10);
}
