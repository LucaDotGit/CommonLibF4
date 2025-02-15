#pragma once

#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	template <class T, std::uint32_t N>
	class DynamicMemoryManagementPol
	{
	public:
		using value_type = T;

		constexpr DynamicMemoryManagementPol() noexcept = default;
		DynamicMemoryManagementPol(const DynamicMemoryManagementPol&) = default;
		DynamicMemoryManagementPol(DynamicMemoryManagementPol&&) = default;
		~DynamicMemoryManagementPol() = default;

		DynamicMemoryManagementPol& operator=(const DynamicMemoryManagementPol&) = default;
		DynamicMemoryManagementPol& operator=(DynamicMemoryManagementPol&&) = default;

		[[nodiscard]] value_type* allocate(std::uint32_t a_num)
		{
			if (a_num > N) {
				return 0;
			}

			auto size = a_num * sizeof(value_type);
			auto mem = malloc<value_type>(size);
			std::memset(mem, 0, size);
			return mem;
		}

		void deallocate(value_type* a_ptr) { free(a_ptr); }
	};

	template <class T, std::uint32_t N>
	class FixedLengthMemoryManagementPol
	{
	public:
		using value_type = T;

		constexpr FixedLengthMemoryManagementPol() noexcept = default;

		FixedLengthMemoryManagementPol(const FixedLengthMemoryManagementPol& a_rhs) { copy_from(a_rhs); }
		FixedLengthMemoryManagementPol(FixedLengthMemoryManagementPol&& a_rhs) { copy_from(a_rhs); }

		~FixedLengthMemoryManagementPol() = default;

		FixedLengthMemoryManagementPol& operator=(const FixedLengthMemoryManagementPol& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				copy_from(a_rhs);
			}
			return *this;
		}

		FixedLengthMemoryManagementPol& operator=(FixedLengthMemoryManagementPol&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				copy_from(a_rhs);
			}
			return *this;
		}

		[[nodiscard]] value_type* allocate(std::uint32_t a_num)
		{
			return a_num > N ? 0 : _buffer;
		}

		void deallocate(value_type*) { return; }

	private:
		void copy_from(const FixedLengthMemoryManagementPol& a_rhs)
		{
			std::memcpy(_buffer, a_rhs._buffer, sizeof(value_type) * N);
		}

		value_type _buffer[N]{ 0 }; // 00
	};

	template <class CharT, std::uint32_t N, template <class, std::uint32_t> class Allocator>
	class BSStringT
		: public Allocator<CharT, N>
	{
	private:
		static constexpr auto MAX = static_cast<std::uint16_t>(N);

	public:
		using value_type = CharT;
		using traits_type = std::char_traits<value_type>;
		using allocator_type = Allocator<value_type, N>;
		using size_type = std::uint16_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		BSStringT()
		{
			clear();
		}

		BSStringT(const BSStringT& a_rhs) :
			allocator_type(a_rhs)
		{
			set_cstr(a_rhs.data());
		}

		BSStringT(BSStringT&& a_rhs) :
			allocator_type(std::move(a_rhs)),
			_data(a_rhs._data),
			_size(a_rhs._size),
			_capacity(a_rhs._capacity)
		{
			a_rhs._data = nullptr;
			a_rhs._size = 0;
			a_rhs._capacity = 0;
		}

		BSStringT(const_pointer a_rhs)
		{
			set_cstr(a_rhs);
		}

		BSStringT(const_pointer a_rhs, size_type a_len)
		{
			set_cstr(a_rhs, a_len);
		}

		explicit BSStringT(std::basic_string_view<value_type> a_rhs)
		{
			set_cstr(a_rhs.data(), a_rhs.size());
		}

		BSStringT(std::basic_string_view<value_type>::const_iterator a_first, std::basic_string_view<value_type>::const_iterator a_last)
		{
			set_cstr(a_first, static_cast<size_type>(std::distance(a_first, a_last)));
		}

		BSStringT(std::initializer_list<value_type> a_ilist)
		{
			set_cstr(a_ilist.begin(), a_ilist.size());
		}

		~BSStringT()
		{
			deallocate(_data);
			_data = nullptr;
		}

		BSStringT& operator=(const BSStringT& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				static_cast<allocator_type&>(*this) = a_rhs;
				set_cstr(a_rhs.data());
			}
			return *this;
		}

		BSStringT& operator=(BSStringT&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				static_cast<allocator_type&>(*this) = std::move(a_rhs);

				_data = a_rhs._data;
				a_rhs._data = nullptr;

				_size = a_rhs._size;
				a_rhs._size = 0;

				_capacity = a_rhs._capacity;
				a_rhs._capacity = 0;
			}
			return *this;
		}

		BSStringT& operator=(const_pointer a_rhs)
		{
			set_cstr(a_rhs);
			return *this;
		}

		BSStringT& operator=(std::basic_string_view<value_type> a_rhs)
		{
			set_cstr(a_rhs.data(), a_rhs.size());
			return *this;
		}

		BSStringT& operator=(std::initializer_list<value_type> a_ilist)
		{
			set_cstr(a_ilist.begin(), a_ilist.size());
			return *this;
		}

		BSStringT operator+(const BSStringT& a_rhs)
		{
			BSStringT result{ *this };
			result.append_cstr(a_rhs.data(), a_rhs.size());
			return result;
		}

		BSStringT operator+(const_pointer a_rhs)
		{
			BSStringT result{ *this };
			result.append_cstr(a_rhs, traits_type::length(a_rhs));
			return result;
		}

		BSStringT operator+(std::basic_string_view<value_type> a_rhs)
		{
			BSStringT result{ *this };
			result.append_cstr(a_rhs.data(), a_rhs.size());
			return result;
		}

		BSStringT& operator+=(const BSStringT& a_rhs)
		{
			append_cstr(a_rhs.data(), a_rhs.size());
			return *this;
		}

		BSStringT& operator+=(const_pointer a_rhs)
		{
			append_cstr(a_rhs, traits_type::length(a_rhs));
			return *this;
		}

		BSStringT& operator+=(std::basic_string_view<value_type> a_rhs)
		{
			append_cstr(a_rhs.data(), a_rhs.size());
			return *this;
		}

		[[nodiscard]] constexpr operator std::basic_string_view<value_type>() const noexcept { return { data(), size() }; }

		[[nodiscard]] constexpr reference operator[](size_type a_pos) noexcept
		{
			return at(a_pos);
		}

		[[nodiscard]] constexpr const_reference operator[](size_type a_pos) const noexcept
		{
			return at(a_pos);
		}

		[[nodiscard]] reference at(size_type a_pos) noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] const_reference at(size_type a_pos) const noexcept
		{
			assert(a_pos < size());
			return data()[a_pos];
		}

		[[nodiscard]] constexpr iterator begin() noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] constexpr iterator end() noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return rend(); }

		[[nodiscard]] constexpr reference front() noexcept { return at(0); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return at(0); }

		[[nodiscard]] constexpr reference back() noexcept { return at(size() - 1); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data ? _data : EMPTY; }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data ? _data : EMPTY; }

		[[nodiscard]] constexpr const_pointer c_str() const noexcept { return data(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		[[nodiscard]] constexpr size_type size() const noexcept
		{
			return _size != MAX ? _size : static_cast<size_type>(traits_type::length(data()));
		}

		[[nodiscard]] constexpr size_type length() const noexcept { return size(); }

		void clear() { set_cstr(EMPTY); }

		[[nodiscard]] friend auto operator==(const BSStringT& a_lhs, const BSStringT& a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs) == std::strong_ordering::equal;
		}

		[[nodiscard]] friend auto operator==(const BSStringT& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs) == std::strong_ordering::equal;
		}

		[[nodiscard]] friend auto operator==(std::basic_string_view<value_type> a_lhs, const BSStringT& a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs) == std::strong_ordering::equal;
		}

		[[nodiscard]] friend auto operator==(const BSStringT& a_lhs, const_pointer a_rhs) noexcept
		{
			return strnicmp(a_lhs.data(), a_rhs, a_lhs.size()) == std::strong_ordering::equal;
		}

		[[nodiscard]] friend auto operator==(const_pointer a_lhs, const BSStringT& a_rhs) noexcept
		{
			return strnicmp(a_lhs, a_rhs.data(), a_rhs.size()) == std::strong_ordering::equal;
		}

		[[nodiscard]] friend auto operator<=>(const BSStringT& a_lhs, const BSStringT& a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs);
		}

		[[nodiscard]] friend auto operator<=>(const BSStringT& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs);
		}

		[[nodiscard]] friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BSStringT& a_rhs) noexcept
		{
			return stricmp(a_lhs, a_rhs);
		}

		[[nodiscard]] friend auto operator<=>(const BSStringT& a_lhs, const_pointer a_rhs) noexcept
		{
			return strnicmp(a_lhs.data(), a_rhs, a_lhs.size());
		}

		[[nodiscard]] friend auto operator<=>(const_pointer a_lhs, const BSStringT& a_rhs) noexcept
		{
			return strnicmp(a_lhs, a_rhs.data(), a_rhs.size());
		}

		F4_HEAP_REDEFINE_NEW();

	private:
		[[nodiscard]] static std::strong_ordering stricmp(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
		{
			const auto lsize = a_lhs.size();
			const auto rsize = a_rhs.size();

			if (lsize != rsize) {
				return lsize <=> rsize;
			}

			return strnicmp(a_lhs.data(), a_rhs.data(), lsize);
		}

		[[nodiscard]] static std::strong_ordering strnicmp(const_pointer a_lhs, const_pointer a_rhs, std::size_t a_length) noexcept
		{
			if (a_length == 0) {
				return std::strong_ordering::equal;
			}

			if constexpr (std::is_same_v<value_type, char>) {
				return _strnicmp(a_lhs, a_rhs, a_length) <=> 0;
			}
			else if constexpr (std::is_same_v<value_type, wchar_t>) {
				return _wcsnicmp(a_lhs, a_rhs, a_length) <=> 0;
			}
			else {
				static_assert(false, "unsupported value_type");
			}
		}

		[[nodiscard]] pointer allocate(std::uint32_t a_num) { return allocator_type::allocate(a_num); }

		void deallocate(pointer a_ptr) { allocator_type::deallocate(a_ptr); }

		bool set_cstr(const_pointer a_str, std::uint32_t a_len = 0)
		{
			auto len = static_cast<std::uint16_t>(a_len);
			if (_data == a_str) {
				return true;
			}

			if (len == 0) {
				len = static_cast<std::uint16_t>(traits_type::length(a_str));
			}

			const size_type newSize = len > MAX ? MAX : len;
			++len;
			const size_type newCap = len > MAX ? MAX : len;

			if (len <= _capacity) {
				traits_type::copy(_data, a_str, len);
				_size = newSize;
				return true;
			}

			const auto newData = allocate(len);
			if (!newData) {
				return false;
			}

			traits_type::copy(newData, a_str, len);
			if (_data) {
				deallocate(_data);
			}

			_data = newData;
			_size = newSize;
			_capacity = newCap;
			return true;
		}

		bool append_cstr(const_pointer a_ptr, size_t a_len)
		{
			if (a_len == 0) {
				return true;
			}

			const auto newSize = size() + a_len;
			const auto newCap = newSize + 1;

			if (newCap <= _capacity) {
				traits_type::copy(_data + size(), a_ptr, a_len);
				_size = static_cast<size_type>(newSize);
				return true;
			}

			const auto newData = allocate(newCap);
			if (!newData) {
				return false;
			}

			traits_type::copy(newData, _data, size());
			traits_type::copy(newData + size(), a_ptr, a_len);

			if (_data) {
				deallocate(_data);
			}

			_data = newData;
			_size = static_cast<size_type>(newSize);
			_capacity = static_cast<size_type>(newCap);
			return true;
		}

		static constexpr value_type EMPTY[]{ 0 };

		// members
		pointer _data{ nullptr };  // ?? (00)
		size_type _size{ 0 };	   // ?? (08)
		size_type _capacity{ 0 };  // ?? (0A)
		std::uint32_t _pad0C{ 0 }; // ?? (0C)
	};

	using BSString = BSStringT<char, static_cast<std::uint32_t>(-1), DynamicMemoryManagementPol>;
	static_assert(sizeof(BSString) == 0x10);

	template <std::uint32_t N>
	class BSStaticStringT
		: public BSStringT<char, N, FixedLengthMemoryManagementPol>
	{
	public:
		using Base = BSStringT<char, N, FixedLengthMemoryManagementPol>;
		using Base::Base;
	};
}

namespace std
{
	template <>
	struct formatter<RE::BSString, RE::BSString::value_type>
		: public formatter<basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>
	{
		constexpr auto parse(basic_format_parse_context<RE::BSString::value_type>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::BSString& a_str, FormatContext& a_ctx) const
		{
			return formatter<basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>::format(a_str, a_ctx);
		}
	};
}

#ifdef FMT_VERSION
namespace fmt
{
	template <>
	struct formatter<RE::BSString, RE::BSString::value_type>
		: public formatter<std::basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>
	{
		constexpr auto parse(basic_format_parse_context<RE::BSString::value_type>& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(const RE::BSString& a_str, FormatContext& a_ctx) const
		{
			return formatter<std::basic_string_view<RE::BSString::value_type>, RE::BSString::value_type>::format(a_str, a_ctx);
		}
	};
}
#endif
