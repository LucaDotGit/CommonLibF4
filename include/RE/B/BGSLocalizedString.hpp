#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/B/BSFixedString.hpp"

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

		constexpr BGSLocalizedString(const_pointer a_value)
		{
			assign_impl(a_value);
		}

		constexpr BGSLocalizedString(const_iterator a_first, const_iterator a_last)
		{
			const auto view = REX::basic_zstring_view<value_type>{ a_first, a_last };
			assign_impl(view);
		}

		constexpr explicit BGSLocalizedString(REX::basic_zstring_view<value_type> a_value)
		{
			assign_impl(a_value);
		}

		constexpr BGSLocalizedString(std::initializer_list<value_type> a_ilist)
		{
			const auto view = REX::basic_zstring_view<value_type>{ a_ilist.begin(), a_ilist.end() };
			assign_impl(view);
		}

		constexpr BGSLocalizedString(const volatile BGSLocalizedString&) = delete;

		constexpr BGSLocalizedString(const BGSLocalizedString&) = default;
		constexpr BGSLocalizedString(BGSLocalizedString&&) noexcept = default;

		constexpr BGSLocalizedString& operator=(std::nullptr_t) = delete;

		constexpr BGSLocalizedString& operator=(const_pointer a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BGSLocalizedString& operator=(REX::basic_zstring_view<value_type> a_rhs)
		{
			assign_impl(a_rhs);
			return *this;
		}

		constexpr BGSLocalizedString& operator=(std::initializer_list<value_type> a_rhs)
		{
			const auto view = REX::basic_zstring_view<value_type>{ a_rhs.begin(), a_rhs.end() };
			assign_impl(view);
			return *this;
		}

		constexpr BGSLocalizedString& operator=(const volatile BGSLocalizedString&) = delete;

		constexpr BGSLocalizedString& operator=(const BGSLocalizedString&) = default;
		constexpr BGSLocalizedString& operator=(BGSLocalizedString&&) noexcept = default;

		[[nodiscard]] constexpr friend bool operator==(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs._data == a_rhs._data; }
		[[nodiscard]] constexpr friend bool operator==(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept { return a_lhs._data == a_rhs; }
		[[nodiscard]] constexpr friend bool operator==(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs == a_rhs._data; }
		[[nodiscard]] constexpr friend bool operator==(const BGSLocalizedString& a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept { return a_lhs._data == a_rhs; }
		[[nodiscard]] constexpr friend bool operator==(REX::basic_zstring_view<value_type> a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs == a_rhs._data; }
		[[nodiscard]] constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs._data <=> a_rhs._data; }
		[[nodiscard]] constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, const_pointer a_rhs) noexcept { return a_lhs._data <=> a_rhs; }
		[[nodiscard]] constexpr friend auto operator<=>(const_pointer a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs <=> a_rhs._data; }
		[[nodiscard]] constexpr friend auto operator<=>(const BGSLocalizedString& a_lhs, REX::basic_zstring_view<value_type> a_rhs) noexcept { return a_lhs._data <=> a_rhs; }
		[[nodiscard]] constexpr friend auto operator<=>(REX::basic_zstring_view<value_type> a_lhs, const BGSLocalizedString& a_rhs) noexcept { return a_lhs <=> a_rhs._data; }

		[[nodiscard]] constexpr operator REX::basic_zstring_view<value_type>() const noexcept { return _data; }
		[[nodiscard]] constexpr explicit operator BSFixedStringCS() const noexcept { return _data; }

		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return _data[a_index]; }

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept { return _data.at(a_index); }

		[[nodiscard]] constexpr const_reference front() const noexcept { return _data.front(); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return _data.back(); }

		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_pointer c_str() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr const_iterator begin() const noexcept { return _data.begin(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return _data.end(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return _data.cend(); }

		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return _data.rbegin(); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return _data.rend(); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return _data.crend(); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] constexpr size_type length() const noexcept { return _data.length(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _data.max_size(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return _data.empty(); }

		constexpr void clear() noexcept
		{
			_data.clear();
		}

		[[nodiscard]] constexpr bool contains(REX::basic_zstring_view<value_type> a_rhs) const noexcept
		{
			return _data.contains(a_rhs);
		}

		constexpr void swap(BGSLocalizedString& a_other) noexcept
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

		[[nodiscard]] constexpr const BSFixedStringCS& hash_accessor() const noexcept { return _data; }

	private:
		inline static constexpr auto PREFIX_LENGTH = static_cast<std::size_t>(13);

		constexpr void assign_impl(REX::basic_zstring_view<value_type> a_rhs)
		{
			if (!std::ranges::starts_with(_data, "<ID="sv)) {
				_data = a_rhs;
				return;
			}

			if (_data.size() < PREFIX_LENGTH) [[unlikely]] {
				REX::Assert(false);
				_data = a_rhs;
				return;
			}

			auto buffer = std::string();
			buffer.resize(PREFIX_LENGTH + a_rhs.size());

			std::copy_n(_data.data(), PREFIX_LENGTH, buffer.data());
			std::copy_n(a_rhs.data() ? a_rhs.data() : "", buffer.size() - PREFIX_LENGTH, buffer.data() + PREFIX_LENGTH);

			_data = std::move(buffer);
		}

		// members
		BSFixedStringCS _data; // 00
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
	constexpr void swap(BGSLocalizedString& a_lhs, BGSLocalizedString& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <>
	struct BSCRC32<RE::BGSLocalizedString>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::BGSLocalizedString& a_key) const noexcept
		{
			return RE::HashCRC32(a_key.hash_accessor());
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::BGSLocalizedString>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BGSLocalizedString& a_key) const noexcept
		{
			return REX::Hash(a_key.hash_accessor());
		}
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type>
		: public formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto assign_impl(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BGSLocalizedString& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, static_cast<std::basic_string_view<RE::BGSLocalizedString::value_type>>(a_value));
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::BGSLocalizedString, RE::BGSLocalizedString::value_type>
		: public formatter<std::basic_string_view<RE::BGSLocalizedString::value_type>, RE::BGSLocalizedString::value_type>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto assign_impl(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BGSLocalizedString& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, static_cast<std::basic_string_view<RE::BGSLocalizedString::value_type>>(a_value));
		}
	};
}
#endif
