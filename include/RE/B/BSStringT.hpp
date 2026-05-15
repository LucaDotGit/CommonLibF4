#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <REX::win32_character CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	class BSStringT
		: private Allocator<CharT, N>
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = CharT;
		using allocator_type = Allocator<value_type, N>;
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

		constexpr BSStringT() noexcept = default;

		constexpr ~BSStringT() noexcept
		{
			deallocate(_data);
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}

		constexpr BSStringT(std::nullptr_t) = delete;

		constexpr BSStringT(value_type a_fillChar, size_type a_count)
		{
			resize_impl(a_count, a_fillChar);
		}

		constexpr BSStringT(const_pointer a_value)
		{
			assign_impl(a_value);
		}

		constexpr BSStringT(const_iterator a_first, const_iterator a_last)
		{
			const auto value = std::basic_string_view<value_type>{ a_first, a_last };
			assign_impl(value);
		}

		constexpr explicit BSStringT(std::basic_string_view<value_type> a_value)
		{
			assign_impl(a_value);
		}

		constexpr BSStringT(std::initializer_list<value_type> a_ilist)
		{
			const auto value = std::basic_string_view<value_type>{ a_ilist.begin(), a_ilist.size() };
			assign_impl(value);
		}

		constexpr BSStringT(const BSStringT& a_rhs)
		{
			assign_impl(a_rhs);
		}

		constexpr BSStringT(BSStringT&& a_rhs) noexcept
			: _data(std::exchange(a_rhs._data, nullptr)),
			  _size(std::exchange(a_rhs._size, static_cast<size_type>(0))),
			  _capacity(std::exchange(a_rhs._capacity, static_cast<size_type>(0)))
		{
		}

		constexpr BSStringT& operator=(std::nullptr_t) = delete;

		constexpr BSStringT& operator=(const_pointer a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator=(std::basic_string_view<value_type> a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator=(std::initializer_list<value_type> a_rhs)
		{
			const auto value = std::basic_string_view<value_type>{ a_rhs.begin(), a_rhs.size() };
			assign_impl(value);
			return *this;
		}

		constexpr BSStringT& operator=(const BSStringT& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			assign_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator=(BSStringT&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			_size = std::exchange(a_rhs._size, static_cast<size_type>(0));
			_capacity = std::exchange(a_rhs._capacity, static_cast<size_type>(0));

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSStringT);

		constexpr BSStringT operator+(const BSStringT& a_rhs) const
		{
			auto result = BSStringT(*this);
			result.append_impl(a_rhs);
			return result;
		}

		constexpr BSStringT operator+(const_pointer a_rhs) const
		{
			auto result = BSStringT(*this);
			result.append_impl(a_rhs);
			return result;
		}

		constexpr BSStringT operator+(std::basic_string_view<value_type> a_rhs) const
		{
			auto result = BSStringT(*this);
			result.append_impl(a_rhs);
			return result;
		}

		constexpr BSStringT operator+(std::initializer_list<value_type> a_rhs) const
		{
			auto result = BSStringT(*this);
			result.append_impl({ a_rhs.begin(), a_rhs.size() });
			return result;
		}

		constexpr BSStringT& operator+=(const BSStringT& a_rhs)
		{
			append_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator+=(const_pointer a_rhs)
		{
			append_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator+=(std::basic_string_view<value_type> a_rhs)
		{
			append_impl(a_rhs);
			return *this;
		}

		constexpr BSStringT& operator+=(std::initializer_list<value_type> a_rhs)
		{
			append_impl({ a_rhs.begin(), a_rhs.size() });
			return *this;
		}

		[[nodiscard]] constexpr friend bool operator==(const BSStringT& a_lhs, const BSStringT& a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const BSStringT& a_lhs, const_pointer a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const_pointer a_lhs, const BSStringT& a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const BSStringT& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(std::basic_string_view<value_type> a_lhs, const BSStringT& a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSStringT& a_lhs, const BSStringT& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSStringT& a_lhs, const_pointer a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const_pointer a_lhs, const BSStringT& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSStringT& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BSStringT& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }

		[[nodiscard]] constexpr operator std::basic_string_view<value_type>() const noexcept { return { data(), size() }; }

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] constexpr reference front() noexcept { return at(0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return at(0); }

		[[nodiscard]] constexpr reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data ? _data : const_cast<pointer>(EMPTY_BUFFER.data()); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data ? _data : EMPTY_BUFFER.data(); }

		[[nodiscard]] constexpr const_pointer c_str() const noexcept { return data(); }

		[[nodiscard]] constexpr iterator begin() noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _size != MAX_SIZE ? _size : static_cast<size_type>(traits_type::length(data())); }
		[[nodiscard]] constexpr size_type length() const noexcept { return size(); }
		[[nodiscard]] constexpr size_type capacity() const noexcept { return _capacity; }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return MAX_SIZE; }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		constexpr void reserve(size_type a_newCapacity)
		{
			if (a_newCapacity > capacity()) {
				reserve_exact(a_newCapacity);
			}
		}

		constexpr void resize(size_type a_newSize)
		{
			resize_impl(a_newSize);
		}

		constexpr void resize(size_type a_newSize, value_type a_value)
		{
			resize_impl(a_newSize, a_value);
		}

		constexpr void shrink_to_fit()
		{
			reserve_exact(size());
		}

		constexpr void clear()
		{
			assign_impl(EMPTY_BUFFER.data());
		}

		[[nodiscard]] constexpr bool contains(std::basic_string_view<value_type> a_substring) const noexcept
		{
			return REX::ContainsIgnoreCase(static_cast<std::basic_string_view<value_type>>(*this), a_substring);
		}

		constexpr void swap(BSStringT& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
			std::swap(_size, a_other._size);
			std::swap(_capacity, a_other._capacity);
		}

	private:
		template <REX::win32_character, std::uint16_t, template <class, std::uint16_t> class>
		friend class BSStringT;

		inline static constexpr auto EMPTY_BUFFER = std::array<const value_type, 1>{ 0 };

		[[nodiscard]] static constexpr bool equals_impl(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return REX::EqualsIgnoreCase(a_lhs, a_rhs);
		}

		[[nodiscard]] static constexpr std::strong_ordering compare_impl(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return REX::CompareIgnoreCase(a_lhs, a_rhs);
		}

		[[nodiscard]] constexpr pointer allocate(size_type a_count)
		{
			return allocator_type::allocate(a_count);
		}

		constexpr void deallocate(pointer a_ptr) noexcept
		{
			if (!a_ptr || a_ptr == EMPTY_BUFFER.data()) {
				return;
			}

			allocator_type::deallocate(a_ptr);
		}

		constexpr void assign_impl(std::basic_string_view<value_type> a_str)
		{
			const auto newSize = static_cast<size_type>(std::min(a_str.size(), static_cast<std::size_t>(MAX_SIZE)));
			if (newSize > capacity()) {
				reserve_exact(newSize);
			}

			traits_type::copy(data(), a_str.data(), newSize);
			_size = newSize;
		}

		constexpr void append_impl(std::basic_string_view<value_type> a_str)
		{
			const auto newSize = static_cast<size_type>(std::min(size() + a_str.size(), static_cast<std::size_t>(MAX_SIZE)));
			if (newSize > capacity()) {
				reserve_exact(newSize);
			}

			traits_type::copy(data() + size(), a_str.data(), a_str.size());
			_size = newSize;
		}

		constexpr void reserve_auto(size_type a_newCapacity)
		{
			if (a_newCapacity > capacity()) {
				const auto grow = std::max(a_newCapacity, static_cast<size_type>(capacity() * 2));
				reserve_exact(grow);
			}
		}

		constexpr void reserve_exact(size_type a_newCapacity)
		{
			REX::Assert(a_newCapacity >= capacity());
			if (a_newCapacity == capacity()) {
				return;
			}

			auto* newData = allocate(a_newCapacity);
			if (!newData) {
				throw std::bad_alloc();
			}

			auto* oldData = data();
			if (newData == oldData) {
				return;
			}

			traits_type::copy(newData, oldData, size());
			deallocate(oldData);

			_data = newData;
			_capacity = a_newCapacity;
		}

		constexpr void resize_impl(size_type a_newSize)
		{
			if (a_newSize == size()) {
				return;
			}

			reserve_auto(a_newSize);

			if (a_newSize > size()) {
				traits_type::assign(data() + size(), a_newSize - size(), static_cast<value_type>(0));
			}

			_size = a_newSize;
		}

		constexpr void resize_impl(size_type a_newSize, value_type a_value)
		{
			if (a_newSize == size()) {
				return;
			}

			reserve_auto(a_newSize);

			if (a_newSize > size()) {
				traits_type::assign(data() + size(), a_newSize - size(), a_value);
			}

			_size = a_newSize;
		}

		// members
		pointer _data{ nullptr }; // 00
		size_type _size{ 0 };	  // 08
		size_type _capacity{ 0 }; // 0A
	};

	template <class T, std::uint16_t N>
	class DynamicMemoryManagementPol
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = T;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;

		DynamicMemoryManagementPol() = default;
		~DynamicMemoryManagementPol() noexcept = default;

		DynamicMemoryManagementPol(const DynamicMemoryManagementPol&) = default;
		DynamicMemoryManagementPol(DynamicMemoryManagementPol&&) noexcept = default;

		DynamicMemoryManagementPol& operator=(const DynamicMemoryManagementPol&) = default;
		DynamicMemoryManagementPol& operator=(DynamicMemoryManagementPol&&) noexcept = default;

		[[nodiscard]] constexpr value_type* allocate(size_type a_count) noexcept
		{
			if (a_count > N) {
				return nullptr;
			}

			return calloc<value_type>(a_count);
		}

		constexpr void deallocate(value_type* a_ptr) noexcept
		{
			free(a_ptr);
		}
	};

	template <class T, std::uint16_t N>
	class FixedLengthMemoryManagementPol
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = T;
		using size_type = std::uint16_t;
		using difference_type = std::int16_t;

		constexpr FixedLengthMemoryManagementPol() = default;
		constexpr ~FixedLengthMemoryManagementPol() noexcept = default;

		constexpr FixedLengthMemoryManagementPol(const FixedLengthMemoryManagementPol&) = default;

		constexpr FixedLengthMemoryManagementPol(FixedLengthMemoryManagementPol&& a_rhs) noexcept
			: _buffer(std::move(a_rhs._buffer))
		{
		}

		constexpr FixedLengthMemoryManagementPol& operator=(const FixedLengthMemoryManagementPol&) = default;

		constexpr FixedLengthMemoryManagementPol& operator=(FixedLengthMemoryManagementPol&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_buffer = std::move(a_rhs._buffer);
			return *this;
		}

		[[nodiscard]] constexpr value_type* allocate(size_type a_count) noexcept
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
		std::array<value_type, N> _buffer{ 0 }; // 00
	};

	extern template class BSStringT<char, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;
	extern template class BSStringT<wchar_t, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;

	using BSString = BSStringT<char, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;
	using BSStringW = BSStringT<wchar_t, std::numeric_limits<std::uint16_t>::max(), DynamicMemoryManagementPol>;

	template <std::uint16_t N>
	using BSStaticStringT = BSStringT<char, N, FixedLengthMemoryManagementPol>;

	template <REX::win32_character CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	constexpr void swap(BSStringT<CharT, N, Allocator>& a_lhs, BSStringT<CharT, N, Allocator>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(BSString&, BSString&) noexcept;
	extern template void swap(BSStringW&, BSStringW&) noexcept;
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
	template <REX::win32_character CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	struct hash<RE::BSStringT<CharT, N, Allocator>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSStringT<CharT, N, Allocator>& a_key) const noexcept
		{
			return REX::HashIgnoreCase(static_cast<std::basic_string_view<CharT>>(a_key));
		}
	};

	extern template struct hash<RE::BSString>;
	extern template struct hash<RE::BSStringW>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <REX::win32_character CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
	struct formatter<RE::BSStringT<CharT, N, Allocator>, CharT>
		: public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSStringT<CharT, N, Allocator>& a_value, FormatContext& a_context) const
		{
			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
		}
	};

	extern template struct formatter<RE::BSString, RE::BSString::value_type>;
	extern template struct formatter<RE::BSStringW, RE::BSStringW::value_type>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	/*
		TODO: Change this to one template specialization when fmt is able to compile it.

		```CPP
		template <REX::win32_character CharT, std::uint16_t N, template <class, std::uint16_t> class Allocator>
		struct formatter<RE::BSStringT<CharT, N, Allocator>, CharT>
			: public formatter<std::basic_string_view<CharT>, CharT>
		{
		public:
			template <class ParseContext>
			[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
			{
				return a_context.begin();
			}

			template <class FormatContext>
			[[nodiscard]] constexpr auto format(const RE::BSStringT<CharT, N, Allocator>& a_value, FormatContext& a_context) const
			{
				using namespace std::string_view_literals;

				return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
			}
		};

		extern template struct formatter<RE::BSString, RE::BSString::value_type>;
		extern template struct formatter<RE::BSStringW, RE::BSStringW::value_type>;
		```
	*/

	template <>
	struct formatter<RE::BSString, RE::BSString::value_type>
		: public formatter<std::basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSString::value_type>>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSStringW, RE::BSStringW::value_type>
		: public formatter<std::basic_string_view<RE::BSStringW::value_type>, RE::BSStringW::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSStringW& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSStringW::value_type>>(a_value));
		}
	};
}
#endif
