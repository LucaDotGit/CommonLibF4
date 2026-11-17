#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSStringPool.hpp"

namespace RE::Impl
{
	template <class CharT, bool CS>
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

		static_assert(REX::win32_character<value_type>);

		constexpr BSFixedString() noexcept = default;

		constexpr ~BSFixedString() noexcept
		{
			try_release();
		}

		constexpr BSFixedString(std::nullptr_t) = delete;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSFixedString(const_pointer a_value)
		{
			assign(a_value);
		}

		template <std::input_iterator InputIt>
		constexpr BSFixedString(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSFixedString(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		constexpr explicit BSFixedString(REX::BasicZStringView<value_type> a_value)
		{
			assign(a_value);
		}

		constexpr BSFixedString(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		template <bool OtherCS>
		constexpr explicit BSFixedString(const BSFixedString<value_type, OtherCS>& a_rhs)
			requires(OtherCS != CS)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		constexpr BSFixedString(const BSFixedString& a_rhs) :
			_data(a_rhs._data)
		{
			try_acquire();
		}

		constexpr BSFixedString(BSFixedString&& a_rhs) noexcept :
			_data(std::exchange(a_rhs._data, nullptr))
		{
		}

		constexpr auto operator=(std::nullptr_t) -> BSFixedString& = delete;

		constexpr auto operator=(const_pointer a_rhs) -> BSFixedString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(REX::BasicZStringView<value_type> a_rhs) -> BSFixedString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(std::initializer_list<value_type> a_rhs) -> BSFixedString&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		template <bool OtherCS>
		constexpr auto operator=(const BSFixedString<value_type, OtherCS>& a_rhs) -> BSFixedString&
			requires(OtherCS != CS)
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		constexpr auto operator=(const BSFixedString& a_rhs) -> BSFixedString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_release();
			_data = a_rhs._data;
			try_acquire();

			return *this;
		}

		constexpr auto operator=(BSFixedString&& a_rhs) noexcept -> BSFixedString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			_data = std::exchange(a_rhs._data, nullptr);
			return *this;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr operator std::basic_string_view<value_type>() const noexcept
		{
			return {data(), size()};
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return data()[a_index];
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return at(0);
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return at(size() - 1);
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			const auto* underlyingData = _data ? _data->data<value_type>() : nullptr;
			return underlyingData ? underlyingData : EMPTY_BUFFER.data();
		}

		[[nodiscard]]
		constexpr auto c_str() const noexcept -> const_pointer
		{
			return data();
		}

		[[nodiscard]]
		constexpr auto native_handle() const noexcept -> const void*
		{
			return _data;
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
			return _data ? _data->size() : 0;
		}

		[[nodiscard]]
		constexpr auto length() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		constexpr void assign(const_pointer a_value)
		{
			try_release();

			if (!a_value) {
				return;
			}

			REX::Assert(REX::IsNullTerminated(std::basic_string_view<value_type>(a_value)));
			GetEntry<value_type>(_data, a_value, CS);
		}

		template <std::input_iterator InputIt>
		constexpr void assign(InputIt a_first, InputIt a_last)
		{
			try_release();

			if (a_first == a_last) {
				return;
			}

			REX::Assert(REX::IsNullTerminated(std::basic_string_view<value_type>(a_first, a_last)));
			GetEntry<value_type>(_data, a_first, CS);
		}

		constexpr void assign(REX::BasicZStringView<value_type> a_value)
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

		constexpr void clear() noexcept
		{
			try_release();
		}

		[[nodiscard]]
		constexpr auto compare(std::basic_string_view<value_type> a_rhs) const noexcept -> std::int32_t
		{
			return REX::GetNumericStrongOrdering(compare(*this, a_rhs));
		}

		[[nodiscard]]
		constexpr auto contains(std::basic_string_view<value_type> a_substring) const noexcept -> bool
		{
			if constexpr (CS) {
				return REX::Contains(std::basic_string_view<value_type>(*this), a_substring);
			}
			else {
				return REX::ContainsIgnoreCase(std::basic_string_view<value_type>(*this), a_substring);
			}
		}

		[[nodiscard]]
		constexpr auto starts_with(std::basic_string_view<value_type> a_prefix) const noexcept -> bool
		{
			if constexpr (CS) {
				return REX::StartsWith(std::basic_string_view<value_type>(*this), a_prefix);
			}
			else {
				return REX::StartsWithIgnoreCase(std::basic_string_view<value_type>(*this), a_prefix);
			}
		}

		[[nodiscard]]
		constexpr auto ends_with(std::basic_string_view<value_type> a_suffix) const noexcept -> bool
		{
			if constexpr (CS) {
				return REX::EndsWith(std::basic_string_view<value_type>(*this), a_suffix);
			}
			else {
				return REX::EndsWithIgnoreCase(std::basic_string_view<value_type>(*this), a_suffix);
			}
		}

		[[nodiscard]]
		constexpr auto find(std::basic_string_view<value_type> a_substring, size_type a_offset = 0) const noexcept
			-> size_type
		{
			if constexpr (CS) {
				return static_cast<size_type>(
					REX::Find(std::basic_string_view<value_type>(*this), a_substring, a_offset));
			}
			else {
				return static_cast<size_type>(
					REX::FindIgnoreCase(std::basic_string_view<value_type>(*this), a_substring, a_offset));
			}
		}

		[[nodiscard]]
		constexpr auto rfind(
			std::basic_string_view<value_type> a_substring,
			size_type a_offset = std::numeric_limits<size_type>::max()) const noexcept -> size_type
		{
			if constexpr (CS) {
				return static_cast<size_type>(
					REX::FindLast(std::basic_string_view<value_type>(*this), a_substring, a_offset));
			}
			else {
				return static_cast<size_type>(
					REX::FindLastIgnoreCase(std::basic_string_view<value_type>(*this), a_substring, a_offset));
			}
		}

		constexpr void swap(BSFixedString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept -> bool
		{
			return hash_equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept -> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept -> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSFixedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			-> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::basic_string_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept
			-> bool
		{
			return equals(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSFixedString& a_lhs, const_pointer a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const_pointer a_lhs, const BSFixedString& a_rhs) noexcept -> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSFixedString& a_lhs, std::basic_string_view<value_type> a_rhs) noexcept
			-> auto
		{
			return compare(a_lhs, a_rhs);
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BSFixedString& a_rhs) noexcept
			-> auto
		{
			return compare(a_lhs, a_rhs);
		}

	private:
		template <class, bool>
		friend class BSFixedString;

		inline static constexpr auto EMPTY_BUFFER = std::array{static_cast<value_type>(0)};

		[[nodiscard]]
		static constexpr auto hash_equals(const BSFixedString& a_lhs, const BSFixedString& a_rhs) noexcept -> bool
		{
			const auto getLeaf = [](const BSFixedString& a_value) noexcept -> const BSStringPool::Entry* {
				return a_value._data ? a_value._data->leaf() : nullptr;
			};

			const auto* leftLeaf = getLeaf(a_lhs);
			const auto* rightLeaf = getLeaf(a_rhs);
			return leftLeaf == rightLeaf;
		}

		[[nodiscard]]
		static constexpr auto equals(std::basic_string_view<value_type> a_lhs, std::basic_string_view<value_type> a_rhs)
			noexcept -> bool
		{
			if constexpr (CS) {
				return REX::Equals(a_lhs, a_rhs);
			}
			else {
				return REX::EqualsIgnoreCase(a_lhs, a_rhs);
			}
		}

		[[nodiscard]]
		static constexpr auto compare(
			std::basic_string_view<value_type> a_lhs,
			std::basic_string_view<value_type> a_rhs) noexcept -> auto
		{
			if constexpr (CS) {
				return REX::Compare(a_lhs, a_rhs);
			}
			else {
				return REX::CompareIgnoreCase(a_lhs, a_rhs);
			}
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
		BSStringPool::Entry* _data{nullptr}; // 0x00
	};
}

namespace RE
{
	using BSFixedString = Impl::BSFixedString<char, false>;
	static_assert(sizeof(BSFixedString) == 0x08);

	using BSFixedStringCS = Impl::BSFixedString<char, true>;
	static_assert(sizeof(BSFixedStringCS) == 0x08);

	using BSFixedStringW = Impl::BSFixedString<wchar_t, false>;
	static_assert(sizeof(BSFixedStringW) == 0x08);

	using BSFixedStringWCS = Impl::BSFixedString<wchar_t, true>;
	static_assert(sizeof(BSFixedStringWCS) == 0x08);
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
	template <class CharT, bool CS>
	struct BSCRC32<RE::Impl::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::Impl::BSFixedString<CharT, CS>& a_key) const noexcept -> std::uint32_t
		{
			return RE::HashCRC32(a_key.native_handle());
		}
	};
}

namespace std
{
	template <class CharT, bool CS>
	struct hash<RE::Impl::BSFixedString<CharT, CS>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::Impl::BSFixedString<CharT, CS>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.native_handle());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class CharT, bool CS>
	struct formatter<RE::Impl::BSFixedString<CharT, CS>, CharT> : public formatter<std::basic_string_view<CharT>, CharT>
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
		constexpr auto format(const RE::Impl::BSFixedString<CharT, CS>& a_value, FormatContext& a_context) const
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
	template <class CharT, bool CS>
	struct formatter<RE::Impl::BSFixedString<CharT, CS>, CharT> : public formatter<std::basic_string_view<CharT>, CharT>
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
		constexpr auto format(const RE::Impl::BSFixedString<CharT, CS>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<CharT>(a_value));
		}
	};
	*/

	template <>
	struct formatter<RE::BSFixedString, RE::BSFixedString::value_type> :
		public formatter<std::basic_string_view<RE::BSFixedString::value_type>, RE::BSFixedString::value_type>
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
		constexpr auto format(const RE::BSFixedString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<RE::BSFixedString::value_type>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringCS, RE::BSFixedStringCS::value_type> :
		public formatter<std::basic_string_view<RE::BSFixedStringCS::value_type>, RE::BSFixedStringCS::value_type>
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
		constexpr auto format(const RE::BSFixedStringCS& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<RE::BSFixedStringCS::value_type>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringW, RE::BSFixedStringW::value_type> :
		public formatter<std::basic_string_view<RE::BSFixedStringW::value_type>, RE::BSFixedStringW::value_type>
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
		constexpr auto format(const RE::BSFixedStringW& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<RE::BSFixedStringW::value_type>(a_value));
		}
	};

	template <>
	struct formatter<RE::BSFixedStringWCS, RE::BSFixedStringWCS::value_type> :
		public formatter<std::basic_string_view<RE::BSFixedStringWCS::value_type>, RE::BSFixedStringWCS::value_type>
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
		constexpr auto format(const RE::BSFixedStringWCS& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"{}"sv,
				std::basic_string_view<RE::BSFixedStringWCS::value_type>(a_value));
		}
	};
}
#endif
