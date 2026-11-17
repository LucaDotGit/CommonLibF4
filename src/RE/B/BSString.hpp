#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	class BSTString
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = CharT;
		using allocator_type = Allocator<value_type, MAX_SIZE>;
		using traits_type = std::char_traits<value_type>;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		static_assert(REX::win32_character<value_type>);

		constexpr BSTString() noexcept(std::is_nothrow_default_constructible_v<allocator_type>) = default;

		constexpr ~BSTString() noexcept
		{
			if (capacity() == 0) {
				return;
			}

			clear();

			deallocate(data());
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}

		constexpr BSTString(std::nullptr_t) = delete;

		constexpr explicit BSTString(size_type a_size)
		{
			resize(a_size);
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSTString(const_pointer a_value)
		{
			assign(a_value);
		}

		constexpr BSTString(value_type a_value, size_type a_count)
		{
			resize(a_count, a_value);
		}

		template <std::input_iterator InputIt>
		constexpr BSTString(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSTString(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		constexpr explicit BSTString(std::basic_string_view<value_type> a_value)
		{
			assign(a_value);
		}

		constexpr BSTString(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		constexpr BSTString(const BSTString& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		constexpr BSTString(BSTString&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr)),
			_size(std::exchange(a_rhs._size, static_cast<size_type>(0))),
			_capacity(std::exchange(a_rhs._capacity, static_cast<size_type>(0)))
		{
		}

		constexpr auto operator=(std::nullptr_t) -> BSTString& = delete;

		constexpr auto operator=(const_pointer a_rhs) -> BSTString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(std::basic_string_view<value_type> a_rhs) -> BSTString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(std::initializer_list<value_type> a_rhs) -> BSTString&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		constexpr auto operator=(const BSTString& a_rhs) -> BSTString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		constexpr auto operator=(BSTString&& a_rhs) noexcept -> BSTString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			deallocate(_data);

			_data = std::exchange(a_rhs._data, nullptr);
			_size = std::exchange(a_rhs._size, static_cast<size_type>(0));
			_capacity = std::exchange(a_rhs._capacity, static_cast<size_type>(0));

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTString);

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr operator std::basic_string_view<value_type>() const noexcept
		{
			return {data(), size()};
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data ? _data : const_cast<pointer>(EMPTY_BUFFER.data());
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data ? _data : EMPTY_BUFFER.data();
		}

		[[nodiscard]]
		constexpr auto c_str() const noexcept -> const_pointer
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return begin();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		constexpr auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return _size;
		}

		[[nodiscard]]
		constexpr auto length() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto capacity() const noexcept -> size_type
		{
			return _capacity;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		constexpr void assign(const_pointer a_value)
		{
			assign(std::basic_string_view<value_type>(a_value));
		}

		template <std::input_iterator InputIt>
		constexpr void assign(InputIt a_first, InputIt a_last)
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

		constexpr void assign(std::basic_string_view<value_type> a_value)
		{
			assign(a_value.data(), a_value.data() + a_value.size());
		}

		constexpr void assign(std::initializer_list<value_type> a_value)
		{
			assign(a_value.begin(), a_value.end());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		constexpr void assign_range(Range&& a_range)
		{
			assign(std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		constexpr void append(const_pointer a_value)
		{
			insert(end(), std::basic_string_view<value_type>(a_value));
		}

		template <std::input_iterator InputIt>
		constexpr void append(InputIt a_first, InputIt a_last)
		{
			insert(end(), a_first, a_last);
		}

		constexpr void append(std::basic_string_view<value_type> a_value)
		{
			insert(end(), a_value);
		}

		constexpr void append(std::initializer_list<value_type> a_value)
		{
			insert(end(), a_value);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		constexpr void append_range(Range&& a_range)
		{
			insert_range(end(), std::forward<Range>(a_range));
		}

		constexpr auto insert(const_iterator a_position, const_pointer a_value) -> iterator
		{
			return insert(a_position, std::basic_string_view<value_type>(a_value));
		}

		template <std::input_iterator InputIt>
		constexpr auto insert(const_iterator a_position, InputIt a_first, InputIt a_last) -> iterator
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

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		constexpr auto insert_range(const_iterator a_position, Range&& a_range) -> iterator
		{
			return insert(a_position, std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		constexpr auto insert(const_iterator a_position, std::basic_string_view<value_type> a_value) -> iterator
		{
			return insert(a_position, a_value.data(), a_value.data() + a_value.size());
		}

		constexpr auto insert(const_iterator a_position, std::initializer_list<value_type> a_value) -> iterator
		{
			return insert(a_position, a_value.begin(), a_value.end());
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

		constexpr auto erase(const_iterator a_first, const_iterator a_last) -> iterator
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

		constexpr void push_back(const_pointer a_value)
		{
			append(a_value);
		}

		constexpr void push_back(std::basic_string_view<value_type> a_value)
		{
			append(a_value);
		}

		constexpr void push_back(std::initializer_list<value_type> a_value)
		{
			append(a_value.begin(), a_value.end());
		}

		constexpr void pop_back()
		{
			erase(std::prev(end()));
		}

		constexpr void reserve(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			reserve_exact(a_newCapacity);
		}

		constexpr void resize(size_type a_newSize)
		{
			resize_impl(a_newSize, static_cast<value_type>(0));
		}

		constexpr void resize(size_type a_newSize, value_type a_value)
		{
			resize_impl(a_newSize, a_value);
		}

		constexpr void shrink_to_fit()
		{
			reserve_exact(size());
		}

		constexpr void clear() noexcept
		{
			erase(begin(), end());
		}

		[[nodiscard]]
		constexpr auto compare(std::basic_string_view<value_type> a_rhs) const noexcept -> std::int32_t
		{
			return std::basic_string_view<value_type>(*this).compare(a_rhs);
		}

		[[nodiscard]]
		constexpr auto contains(std::basic_string_view<value_type> a_substring) const noexcept -> bool
		{
			return REX::ContainsIgnoreCase(std::basic_string_view<value_type>(*this), a_substring);
		}

		[[nodiscard]]
		constexpr auto starts_with(std::basic_string_view<value_type> a_prefix) const noexcept -> bool
		{
			return REX::StartsWithIgnoreCase(std::basic_string_view<value_type>(*this), a_prefix);
		}

		[[nodiscard]]
		constexpr auto ends_with(std::basic_string_view<value_type> a_suffix) const noexcept -> bool
		{
			return REX::EndsWithIgnoreCase(std::basic_string_view<value_type>(*this), a_suffix);
		}

		[[nodiscard]]
		constexpr auto find(std::basic_string_view<value_type> a_substring, size_type a_offset = 0) const noexcept
			-> size_type
		{
			return static_cast<size_type>(
				REX::FindIgnoreCase(std::basic_string_view<value_type>(*this), a_substring, a_offset));
		}

		[[nodiscard]]
		constexpr auto rfind(std::basic_string_view<value_type> a_substring, size_type a_offset = MAX_SIZE)
			const noexcept -> size_type
		{
			return static_cast<size_type>(
				REX::FindLastIgnoreCase(std::basic_string_view<value_type>(*this), a_substring, a_offset));
		}

		constexpr void swap(BSTString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_allocator, a_other._allocator);
			std::swap(_data, a_other._data);
			std::swap(_size, a_other._size);
			std::swap(_capacity, a_other._capacity);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTString& a_lhs, const BSTString& a_rhs) noexcept -> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTString& a_lhs, const_pointer a_rhs) noexcept -> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const_pointer a_lhs, const BSTString& a_rhs) noexcept -> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			-> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::basic_string_view<value_type> a_lhs, const BSTString& a_rhs) noexcept
			-> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTString& a_lhs, const BSTString& a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTString& a_lhs, const_pointer a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const_pointer a_lhs, const BSTString& a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			-> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BSTString& a_rhs) noexcept
			-> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr auto operator+(const_pointer a_rhs) const -> BSTString
		{
			auto result = BSTString(*this);
			result.append(a_rhs);
			return result;
		}

		[[nodiscard]]
		constexpr auto operator+(std::basic_string_view<value_type> a_rhs) const -> BSTString
		{
			auto result = BSTString(*this);
			result.append(a_rhs);
			return result;
		}

		[[nodiscard]]
		constexpr auto operator+(std::initializer_list<value_type> a_rhs) const -> BSTString
		{
			auto result = BSTString(*this);
			result.append(a_rhs.begin(), a_rhs.end());
			return result;
		}

		[[nodiscard]]
		constexpr auto operator+(const BSTString& a_rhs) const -> BSTString
		{
			auto result = BSTString(*this);
			result.append(a_rhs.begin(), a_rhs.end());
			return result;
		}

		constexpr auto operator+=(const_pointer a_rhs) -> BSTString&
		{
			append(a_rhs);
			return *this;
		}

		constexpr auto operator+=(std::basic_string_view<value_type> a_rhs) -> BSTString&
		{
			append(a_rhs);
			return *this;
		}

		constexpr auto operator+=(std::initializer_list<value_type> a_rhs) -> BSTString&
		{
			append(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		constexpr auto operator+=(const BSTString& a_rhs) -> BSTString&
		{
			append(a_rhs.begin(), a_rhs.end());
			return *this;
		}

	private:
		template <class, std::uint16_t, template <class, std::uint16_t> class>
		friend class BSTString;

		inline static constexpr auto EMPTY_BUFFER = std::array{static_cast<value_type>(0)};

		[[nodiscard]]
		static constexpr auto equals(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs)
			noexcept -> bool
		{
			return REX::EqualsIgnoreCase(a_lhs, a_rhs);
		}

		[[nodiscard]]
		static constexpr auto compare(
			std::basic_string_view<value_type> a_lhs,
			std::basic_string_view<value_type> a_rhs) noexcept -> auto
		{
			return REX::CompareIgnoreCase(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr auto decay_iterator(const_iterator a_it) -> iterator
		{
			return const_cast<pointer>(std::addressof(*a_it));
		}

		[[nodiscard]]
		constexpr auto allocate(size_type a_count) -> pointer
		{
			return _allocator.allocate(a_count);
		}

		constexpr void deallocate(pointer a_ptr) noexcept
		{
			if (!a_ptr || a_ptr == EMPTY_BUFFER.data()) {
				return;
			}

			_allocator.deallocate(a_ptr);
		}

		constexpr void reserve_auto(size_type a_newCapacity)
		{
			if (a_newCapacity <= capacity()) {
				return;
			}

			const auto grow = std::max(a_newCapacity, static_cast<size_type>(capacity() * 2));
			reserve_exact(grow);
		}

		constexpr void reserve_exact(size_type a_newCapacity)
		{
			REX::Assert(a_newCapacity >= size());
			if (a_newCapacity <= capacity()) {
				return;
			}

			auto* newData = allocate(a_newCapacity);
			if (!newData) [[unlikely]] {
				REX::Throw<std::bad_alloc>();
			}

			auto* oldData = _data;
			if (newData == oldData) {
				return;
			}

			std::uninitialized_move_n(oldData, size(), newData);

			deallocate(oldData);
			_data = newData;
			_capacity = a_newCapacity;
		}

		constexpr void resize_impl(size_type a_newSize, value_type a_value)
		{
			if (a_newSize == size()) {
				return;
			}

			if (a_newSize < size()) {
				erase(begin() + a_newSize, end());
				return;
			}

			reserve_auto(a_newSize + 1);

			auto range = std::span<value_type>{data() + size(), static_cast<size_type>(a_newSize - size())};
			std::uninitialized_fill(range.begin(), range.end(), a_value);

			_size = a_newSize;
			_data[_size] = static_cast<value_type>(0);
		}

		// members
		[[REX_NO_UNIQUE_ADDRESS]]
		allocator_type _allocator{}; // 0x00
		pointer _data{nullptr};		 // 0x??
		size_type _size{0};			 // 0x??
		size_type _capacity{0};		 // 0x??
	};

	template <class T, std::uint16_t N>
	class BSStringHeapAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = T;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;

		BSStringHeapAllocator() noexcept = default;
		~BSStringHeapAllocator() noexcept = default;

		BSStringHeapAllocator(const BSStringHeapAllocator&) = default;
		BSStringHeapAllocator(BSStringHeapAllocator&&) noexcept = default;

		auto operator=(const BSStringHeapAllocator&) -> BSStringHeapAllocator& = default;
		auto operator=(BSStringHeapAllocator&&) noexcept -> BSStringHeapAllocator& = default;

		[[nodiscard]]
		constexpr auto allocate(size_type a_count) noexcept -> value_type*
		{
			if (a_count > N) {
				return nullptr;
			}

			return malloc<value_type>(a_count);
		}

		constexpr void deallocate(value_type* a_ptr) noexcept
		{
			free(a_ptr);
		}
	};

	template <class T, std::uint16_t N>
	class BSStringFixedAllocator
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = T;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;

		constexpr BSStringFixedAllocator() noexcept = default;
		constexpr ~BSStringFixedAllocator() noexcept = default;

		constexpr BSStringFixedAllocator(const BSStringFixedAllocator&) = default;

		constexpr BSStringFixedAllocator(BSStringFixedAllocator&& a_rhs) noexcept :
			_buffer(std::move(a_rhs._buffer))
		{
		}

		constexpr auto operator=(const BSStringFixedAllocator&) -> BSStringFixedAllocator& = default;

		constexpr auto operator=(BSStringFixedAllocator&& a_rhs) noexcept -> BSStringFixedAllocator&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_buffer = std::move(a_rhs._buffer);
			return *this;
		}

		[[nodiscard]]
		constexpr auto allocate(size_type a_count) noexcept -> value_type*
		{
			if (a_count > N) {
				return nullptr;
			}

			return _buffer.data();
		}

		constexpr void deallocate([[maybe_unused]] value_type* a_ptr) noexcept
		{
			return;
		}

	private:
		// members
		std::array<value_type, N> _buffer{0}; // 0x00
	};

	using BSString = BSTString<char, std::numeric_limits<std::uint16_t>::max(), BSStringHeapAllocator>;
	static_assert(sizeof(BSString) == 0x10);

	using BSStringW = BSTString<wchar_t, std::numeric_limits<std::uint16_t>::max(), BSStringHeapAllocator>;
	static_assert(sizeof(BSStringW) == 0x10);

	template <std::uint16_t N>
	using BSStaticString = BSTString<char, N, BSStringFixedAllocator>;

	template <std::uint16_t N>
	using BSStaticStringW = BSTString<wchar_t, N, BSStringFixedAllocator>;
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <>
	struct script_traits<RE::BSString>
	{
		using is_string = std::true_type;
	};

	template <>
	struct script_traits<RE::BSStringW>
	{
		using is_wstring = std::true_type;
	};
}

namespace std
{
	template <class CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	struct hash<RE::BSTString<CharT, N, Allocator>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BSTString<CharT, N, Allocator>& a_key) const noexcept -> std::size_t
		{
			return REX::HashIgnoreCase(std::basic_string_view<CharT>(a_key));
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	struct formatter<RE::BSTString<CharT, N, Allocator>, CharT> : public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSTString<CharT, N, Allocator>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<CharT>(a_value));
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	/*
	template <class CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	struct formatter<RE::BSTString<CharT, N, Allocator>, CharT> : public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSTString<CharT, N, Allocator>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<CharT>(a_value));
		}
	};
	*/

	template <>
	struct formatter<RE::BSString, RE::BSString::value_type> :
		public formatter<std::basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<RE::BSString::value_type>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSStringW, RE::BSStringW::value_type> :
		public formatter<std::basic_string_view<RE::BSStringW::value_type>, RE::BSStringW::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSStringW& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<RE::BSStringW::value_type>(a_value));
		}
	};
}
#endif
