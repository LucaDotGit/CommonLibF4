#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSStringPool.hpp"

namespace RE::Impl
{
	template <REX::win32_character CharT, bool CS>
	class BSFixedString
	{
	public:
		inline static constexpr auto IS_CASE_SENSITIVE = CS;

		using value_type = CharT;
		using traits_type = std::char_traits<value_type>;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr BSFixedString() noexcept = default;
		constexpr ~BSFixedString() noexcept { try_release(); }

		constexpr BSFixedString(std::nullptr_t) = delete;

		constexpr BSFixedString(const_pointer a_value)
		{
			assign_impl(a_value);
		}

		constexpr BSFixedString(const_iterator a_first, const_iterator a_last)
		{
			const auto value = REX::basic_zstring_view<value_type>{ a_first, a_last };
			assign_impl(value);
		}

		constexpr explicit BSFixedString(REX::basic_zstring_view<value_type> a_value)
		{
			assign_impl(a_value);
		}

		constexpr BSFixedString(std::initializer_list<value_type> a_ilist)
		{
			const auto value = REX::basic_zstring_view<value_type>{ a_ilist.begin(), a_ilist.size() };
			assign_impl(value);
		}

		template <bool OtherCS>
		constexpr explicit BSFixedString(const BSFixedString<value_type, OtherCS>& a_rhs)
			requires(OtherCS != CS)
		{
			assign_impl(a_rhs.data());
		}

		constexpr BSFixedString(const volatile BSFixedString&) = delete;

		constexpr BSFixedString(const BSFixedString& a_rhs)
			: _data(a_rhs._data)
		{
			try_acquire();
		}

		constexpr BSFixedString(BSFixedString&& a_rhs) noexcept
			: _data(std::exchange(a_rhs._data, nullptr))
		{
		}

		constexpr BSFixedString& operator=(std::nullptr_t) = delete;

		constexpr BSFixedString& operator=(const_pointer a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BSFixedString& operator=(REX::basic_zstring_view<value_type> a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BSFixedString& operator=(std::initializer_list<value_type> a_rhs)
		{
			const auto value = REX::basic_zstring_view<value_type>{ a_rhs.begin(), a_rhs.size() };
			assign_impl(value);
			return *this;
		}

		template <bool OtherCS>
		constexpr BSFixedString& operator=(const BSFixedString<value_type, OtherCS>& a_rhs)
			requires(OtherCS != CS)
		{
			assign_impl(a_rhs.data());
			return *this;
		}

		constexpr BSFixedString& operator=(const volatile BSFixedString&) = delete;

		constexpr BSFixedString& operator=(const BSFixedString& a_rhs)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_release();
			_data = a_rhs._data;
			try_acquire();

			return *this;
		}

		constexpr BSFixedString& operator=(BSFixedString&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			return *this;
		}

		[[nodiscard]] constexpr friend bool operator==(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept { return hash_equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(const BSFixedString& a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend bool operator==(REX::basic_zstring_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept { return equals_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(const BSFixedString& a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }
		[[nodiscard]] constexpr friend auto operator<=>(REX::basic_zstring_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept { return compare_impl(a_lhs, a_rhs); }

		[[nodiscard]] constexpr operator REX::basic_zstring_view<value_type>() const noexcept { return { data(), size() }; }

		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]] constexpr const_reference front() const noexcept { return at(0); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return at(size() - 1); }

		[[nodiscard]] constexpr const_pointer data() const noexcept
		{
			const auto* underlyingData = _data ? _data->data<value_type>() : nullptr;
			return underlyingData ? underlyingData : EMPTY_BUFFER.data();
		}

		[[nodiscard]] constexpr const_pointer c_str() const noexcept { return data(); }

		[[nodiscard]] constexpr const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _data ? _data->size() : 0; }
		[[nodiscard]] constexpr size_type length() const noexcept { return size(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return size(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

		constexpr void clear() noexcept
		{
			try_release();
		}

		[[nodiscard]] constexpr bool contains(REX::basic_zstring_view<value_type> a_substring) const noexcept
		{
			if constexpr (CS) {
				return REX::Contains(static_cast<REX::basic_zstring_view<value_type>>(*this), a_substring);
			}
			else {
				return REX::ContainsIgnoreCase(static_cast<REX::basic_zstring_view<value_type>>(*this), a_substring);
			}
		}

		constexpr void swap(BSFixedString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

	protected:
		template <class>
		friend struct RE::BSCRC32;

		template <class>
		friend struct std::hash;

		[[nodiscard]] constexpr const void* hash_accessor() const noexcept { return _data; }

	private:
		template <REX::win32_character, bool>
		friend class BSFixedString;

		inline static constexpr auto EMPTY_BUFFER = std::array<const value_type, 1>{ 0 };

		[[nodiscard]] static constexpr bool hash_equals_impl(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept
		{
			const auto getLeaf = [](const BSFixedString& a_value) -> const BSStringPool::Entry* {
				return a_value._data ? a_value._data->leaf() : nullptr;
			};

			const auto* leftLeaf = getLeaf(a_lhs);
			const auto* rightLeaf = getLeaf(a_rhs);
			return leftLeaf == rightLeaf;
		}

		[[nodiscard]] static constexpr bool equals_impl(REX::basic_zstring_view<value_type> a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept
		{
			if constexpr (CS) {
				return REX::Equals(a_lhs, a_rhs);
			}
			else {
				return REX::EqualsIgnoreCase(a_lhs, a_rhs);
			}
		}

		[[nodiscard]] static constexpr std::strong_ordering compare_impl(REX::basic_zstring_view<value_type> a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept
		{
			if constexpr (CS) {
				return REX::Compare(a_lhs, a_rhs);
			}
			else {
				return REX::CompareIgnoreCase(a_lhs, a_rhs);
			}
		}

		constexpr void assign_impl(const_pointer a_value)
		{
			try_release();

			if (!a_value) {
				return;
			}

			REX::Assert(REX::IsNullTerminated(std::basic_string_view<value_type>(a_value)));
			GetEntry<value_type>(_data, a_value, CS);
		}

		constexpr void assign_impl(REX::basic_zstring_view<value_type> a_value)
		{
			try_release();

			if (!a_value.data()) {
				return;
			}

			REX::Assert(REX::IsNullTerminated(a_value));
			GetEntry<value_type>(_data, a_value.data(), CS);
		}

		constexpr void try_acquire() noexcept
		{
			if (!_data) {
				return;
			}

			_data->Acquire();
		}

		constexpr void try_release() noexcept
		{
			if (!_data) {
				return;
			}

			BSStringPool::Entry::Release(_data);
			REX::Assert(_data == nullptr);
		}

		// members
		BSStringPool::Entry* _data{ nullptr }; // 00
	};

	extern template class BSFixedString<char, false>;
	extern template class BSFixedString<char, true>;
	extern template class BSFixedString<wchar_t, false>;
	extern template class BSFixedString<wchar_t, true>;
}

namespace RE
{
	using BSFixedString = Impl::BSFixedString<char, false>;
	using BSFixedStringCS = Impl::BSFixedString<char, true>;
	using BSFixedStringW = Impl::BSFixedString<wchar_t, false>;
	using BSFixedStringWCS = Impl::BSFixedString<wchar_t, true>;

	template <REX::win32_character CharT, bool CS>
	constexpr void swap(Impl::BSFixedString<CharT, CS>& a_lhs, Impl::BSFixedString<CharT, CS>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(RE::BSFixedString&, RE::BSFixedString&) noexcept;
	extern template void swap(RE::BSFixedStringCS&, RE::BSFixedStringCS&) noexcept;
	extern template void swap(RE::BSFixedStringW&, RE::BSFixedStringW&) noexcept;
	extern template void swap(RE::BSFixedStringWCS&, RE::BSFixedStringWCS&) noexcept;
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <>
	struct script_traits<RE::BSFixedString>
	{
		using is_string = std::true_type;
	};

	template <>
	struct script_traits<RE::BSFixedStringCS>
	{
		using is_string = std::true_type;
	};

	template <>
	struct script_traits<RE::BSFixedStringW>
	{
		using is_wstring = std::true_type;
	};

	template <>
	struct script_traits<RE::BSFixedStringWCS>
	{
		using is_wstring = std::true_type;
	};
}

namespace RE
{
	template <REX::win32_character CharT, bool CS>
	struct BSCRC32<RE::Impl::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::Impl::BSFixedString<CharT, CS>& a_key) const noexcept
		{
			return RE::HashCRC32(a_key.hash_accessor());
		}
	};

	extern template struct BSCRC32<RE::BSFixedString>;
	extern template struct BSCRC32<RE::BSFixedStringCS>;
	extern template struct BSCRC32<RE::BSFixedStringW>;
	extern template struct BSCRC32<RE::BSFixedStringWCS>;
}

namespace std
{
	template <REX::win32_character CharT, bool CS>
	struct hash<RE::Impl::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::Impl::BSFixedString<CharT, CS>& a_key) const noexcept
		{
			return REX::Hash(a_key.hash_accessor());
		}
	};

	extern template struct hash<RE::BSFixedString>;
	extern template struct hash<RE::BSFixedStringCS>;
	extern template struct hash<RE::BSFixedStringW>;
	extern template struct hash<RE::BSFixedStringWCS>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <REX::win32_character CharT, bool CS>
	struct formatter<RE::Impl::BSFixedString<CharT, CS>, CharT>
		: public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::Impl::BSFixedString<CharT, CS>& a_value, FormatContext& a_context) const
		{
			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
		}
	};

	extern template struct formatter<RE::BSFixedString, RE::BSFixedString::value_type>;
	extern template struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type>;
	extern template struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type>;
	extern template struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	/*
		TODO: Change this to one template specialization when fmt is able to compile it.

		```CPP
		template <REX::win32_character CharT, bool CS>
		struct formatter<RE::Impl::BSFixedString<CharT, CS>, CharT>
			: public formatter<std::basic_string_view<CharT>, CharT>
		{
		public:
			template <class ParseContext>
			[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
			{
				return a_context.begin();
			}

			template <class FormatContext>
			[[nodiscard]] constexpr auto format(const RE::Impl::BSFixedString<CharT, CS>& a_value, FormatContext& a_context) const
			{
				using namespace std::string_view_literals;

				return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
			}
		};

		extern template struct formatter<RE::BSFixedString, RE::BSFixedString::value_type>;
		extern template struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type>;
		extern template struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type>;
		extern template struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type>;
		```
	*/

	template <>
	struct formatter<RE::BSFixedString, RE::BSFixedString::value_type>
		: public formatter<std::basic_string_view<RE::BSFixedString::value_type>, RE::BSFixedString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSFixedString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSFixedString::value_type>>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type>
		: public formatter<std::basic_string_view<RE::BSFixedStringCS::value_type>, RE::BSFixedStringCS::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSFixedStringCS& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSFixedStringCS::value_type>>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type>
		: public formatter<std::basic_string_view<RE::BSFixedStringW::value_type>, RE::BSFixedStringW::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSFixedStringW& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSFixedStringW::value_type>>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type>
		: public formatter<std::basic_string_view<RE::BSFixedStringWCS::value_type>, RE::BSFixedStringWCS::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSFixedStringWCS& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, static_cast<std::basic_string_view<RE::BSFixedStringWCS::value_type>>(a_value));
		}
	};
}
#endif
