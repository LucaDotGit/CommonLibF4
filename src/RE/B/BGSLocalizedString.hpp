#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSLocalizedString
	{
	public:
		inline static constexpr auto IS_CASE_SENSITIVE = BSFixedStringCS::IS_CASE_SENSITIVE;

		using value_type = BSFixedStringCS::value_type;
		using traits_type = BSFixedStringCS::traits_type;
		using size_type = BSFixedStringCS::size_type;
		using difference_type = BSFixedStringCS::difference_type;
		using pointer = BSFixedStringCS::pointer;
		using const_pointer = BSFixedStringCS::const_pointer;
		using reference = BSFixedStringCS::reference;
		using const_reference = BSFixedStringCS::const_reference;
		using iterator = BSFixedStringCS::iterator;
		using const_iterator = BSFixedStringCS::const_iterator;
		using reverse_iterator = BSFixedStringCS::reverse_iterator;
		using const_reverse_iterator = BSFixedStringCS::const_reverse_iterator;

		constexpr BGSLocalizedString() noexcept = default;
		constexpr ~BGSLocalizedString() noexcept = default;

		constexpr BGSLocalizedString(std::nullptr_t) = delete;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BGSLocalizedString(const_pointer a_value)
		{
			assign(a_value);
		}

		template <std::input_iterator InputIt>
		constexpr BGSLocalizedString(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BGSLocalizedString(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		constexpr explicit BGSLocalizedString(REX::BasicZStringView<value_type> a_value)
		{
			assign(a_value);
		}

		constexpr BGSLocalizedString(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		constexpr BGSLocalizedString(const BGSLocalizedString&) = default;
		constexpr BGSLocalizedString(BGSLocalizedString&&) noexcept = default;

		constexpr auto operator=(std::nullptr_t) -> BGSLocalizedString& = delete;

		constexpr auto operator=(const_pointer a_rhs) -> BGSLocalizedString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(REX::BasicZStringView<value_type> a_rhs) -> BGSLocalizedString&
		{
			assign(a_rhs);
			return *this;
		}

		constexpr auto operator=(std::initializer_list<value_type> a_rhs) -> BGSLocalizedString&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		constexpr auto operator=(const BGSLocalizedString&) -> BGSLocalizedString& = default;
		constexpr auto operator=(BGSLocalizedString&&) noexcept -> BGSLocalizedString& = default;

		[[nodiscard]]
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr operator std::basic_string_view<value_type>() const noexcept
		{
			return _data;
		}

		[[nodiscard]]
		constexpr explicit operator BSFixedStringCS() const noexcept
		{
			return _data;
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			return _data.at(a_index);
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto c_str() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto native_handle() const noexcept -> const void*
		{
			return _data.native_handle();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return _data.begin();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return _data.cbegin();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return _data.end();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return _data.cend();
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return _data.rbegin();
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return _data.crbegin();
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return _data.rend();
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return _data.crend();
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return _data.size();
		}

		[[nodiscard]]
		constexpr auto length() const noexcept -> size_type
		{
			return _data.length();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return _data.max_size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return _data.empty();
		}

		constexpr void assign(const_pointer a_value)
		{
			assign(REX::BasicZStringView<value_type>(a_value));
		}

		template <std::input_iterator InputIt>
		constexpr void assign(InputIt a_first, InputIt a_last)
		{
			if (!std::ranges::starts_with(_data, "<ID="sv)) {
				_data = REX::BasicZStringView<value_type>{a_first, a_last};
				return;
			}

			if (_data.size() < PREFIX_LENGTH) [[unlikely]] {
				REX::Assert(false);
				_data = REX::BasicZStringView<value_type>{a_first, a_last};
				return;
			}

			auto buffer = std::basic_string<value_type, std::char_traits<value_type>, StlAllocator<value_type>>();
			REX::ResizeForOverwrite(buffer, PREFIX_LENGTH + static_cast<size_type>(std::distance(a_first, a_last)));

			std::copy_n(_data.data(), PREFIX_LENGTH, buffer.data());
			std::copy_n(a_first ? a_first : "", buffer.size() - PREFIX_LENGTH, buffer.data() + PREFIX_LENGTH);

			_data = std::move(buffer);
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
			_data.clear();
		}

		[[nodiscard]]
		constexpr auto compare(std::basic_string_view<value_type> a_rhs) const noexcept -> std::int32_t
		{
			return _data.compare(a_rhs);
		}

		[[nodiscard]]
		constexpr auto contains(std::basic_string_view<value_type> a_rhs) const noexcept -> bool
		{
			return _data.contains(a_rhs);
		}

		[[nodiscard]]
		constexpr auto starts_with(std::basic_string_view<value_type> a_rhs) const noexcept -> bool
		{
			return _data.starts_with(a_rhs);
		}

		[[nodiscard]]
		constexpr auto ends_with(std::basic_string_view<value_type> a_rhs) const noexcept -> bool
		{
			return _data.ends_with(a_rhs);
		}

		[[nodiscard]]
		constexpr auto find(std::basic_string_view<value_type> a_substring, size_type a_offset = 0) const noexcept
			-> size_type
		{
			return _data.find(a_substring, a_offset);
		}

		[[nodiscard]]
		constexpr auto rfind(
			std::basic_string_view<value_type> a_substring,
			size_type a_offset = std::numeric_limits<size_type>::max()) const noexcept -> size_type
		{
			return _data.rfind(a_substring, a_offset);
		}

		constexpr void swap(BGSLocalizedString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept
			-> bool
		{
			return a_lhs._data == a_rhs._data;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept -> bool
		{
			return a_lhs._data == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept -> bool
		{
			return a_lhs == a_rhs._data;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BGSLocalizedString& a_lhs, std::basic_string_view<value_type> a_rhs)
			noexcept -> bool
		{
			return a_lhs._data == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::basic_string_view<value_type> a_lhs, const BGSLocalizedString& a_rhs)
			noexcept -> bool
		{
			return a_lhs == a_rhs._data;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept
			-> auto
		{
			return a_lhs._data <=> a_rhs._data;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept -> auto
		{
			return a_lhs._data <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept -> auto
		{
			return a_lhs <=> a_rhs._data;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, std::basic_string_view<value_type> a_rhs)
			noexcept
		{
			return a_lhs._data <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::basic_string_view<value_type> a_lhs, const BGSLocalizedString& a_rhs)
			noexcept
		{
			return a_lhs <=> a_rhs._data;
		}

	private:
		inline static constexpr auto PREFIX_LENGTH = static_cast<size_type>(13);

		// members
		BSFixedStringCS _data; // 0x00
	};

	static_assert(sizeof(BGSLocalizedString) == 0x08);
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <>
	struct script_traits<RE::BGSLocalizedString>
	{
		using is_string = std::true_type;
	};
}

namespace RE
{
	template <>
	struct BSCRC32<RE::BGSLocalizedString>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::BGSLocalizedString& a_key) const noexcept -> std::uint32_t
		{
			return RE::HashCRC32(a_key.native_handle());
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::BGSLocalizedString>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BGSLocalizedString& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.native_handle());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type> :
		public formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto assign(ParseContext& a_context) const
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BGSLocalizedString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"{}"sv,
				std::basic_string_view<RE::BGSLocalizedString::value_type>(a_value));
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type> :
		public formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto assign(ParseContext& a_context) const
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BGSLocalizedString& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"{}"sv,
				std::basic_string_view<RE::BGSLocalizedString::value_type>(a_value));
		}
	};
}
#endif
