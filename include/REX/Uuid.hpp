#pragma once

#include "REX/Contract.hpp"
#include "REX/Hash.hpp"

namespace REX
{
	struct Uuid final
	{
	public:
		inline static constexpr auto BYTE_COUNT = 16;
		inline static constexpr auto STRING_LENGTH = 36;

		using value_type = std::uint8_t;
		using container_type = std::array<value_type, BYTE_COUNT>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr Uuid() noexcept = default;
		constexpr ~Uuid() noexcept = default;

		constexpr Uuid(container_type a_data) noexcept
			: _data(a_data)
		{
		}

		constexpr Uuid(const Uuid&) noexcept = default;
		constexpr Uuid(Uuid&&) noexcept = default;

		constexpr Uuid& operator=(Uuid&&) noexcept = default;
		constexpr Uuid& operator=(const Uuid&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Uuid&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Uuid&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Uuid&) const noexcept = default;

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr reference front() noexcept { return _data.front(); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return _data.front(); }

		[[nodiscard]] constexpr reference back() noexcept { return _data.back(); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return _data.back(); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr iterator begin() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr iterator end() noexcept { return _data.data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return _data.data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return _data.data() + size(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _data.max_size(); }

		[[nodiscard]] static Uuid Generate() noexcept;

		[[nodiscard]] static constexpr std::optional<Uuid> FromArray(std::span<const value_type, BYTE_COUNT> a_bytes) noexcept
		{
			auto bytes = container_type();
			std::ranges::copy(a_bytes, bytes.begin());
			return Uuid(bytes);
		}

		[[nodiscard]] static constexpr std::optional<Uuid> FromBytes(std::span<const value_type> a_bytes) noexcept
		{
			if (a_bytes.size() != BYTE_COUNT) {
				return std::nullopt;
			}

			auto bytes = container_type();
			std::ranges::copy(a_bytes, bytes.begin());
			return Uuid(bytes);
		}

		[[nodiscard]] static constexpr std::optional<Uuid> FromString(std::string_view a_value) noexcept
		{
			if (a_value.size() != STRING_LENGTH) {
				return std::nullopt;
			}

			auto bytes = container_type();
			for (auto i = static_cast<std::size_t>(0); i < sizeof(_data); i++) {
				const auto byte = FromHexStringAt(a_value, FROM_STRING_TABLE[i]);
				if (!byte) {
					return std::nullopt;
				}

				bytes[i] = *byte;
			}

			return Uuid(bytes);
		}

		[[nodiscard]] constexpr std::string ToString() const
		{
			auto result = std::string();
			result.resize(STRING_LENGTH, '-');

			for (auto i = static_cast<std::size_t>(0); i < BYTE_COUNT; i++) {
				constexpr auto HIGH_NIBBLE_SHIFT = static_cast<value_type>(4);
				constexpr auto LOW_NIBBLE_MASK = static_cast<value_type>(0x0F);

				const auto byte = _data[i];
				const auto highNibble = (byte >> HIGH_NIBBLE_SHIFT) & LOW_NIBBLE_MASK;
				const auto lowNibble = byte & LOW_NIBBLE_MASK;

				result[FROM_STRING_TABLE[i]] = TO_STRING_TABLE[highNibble];
				result[FROM_STRING_TABLE[i] + 1] = TO_STRING_TABLE[lowNibble];
			}

			return result;
		}

		constexpr void swap(Uuid& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

	private:
		inline static constexpr auto FROM_STRING_TABLE = std::array<const std::size_t, BYTE_COUNT>{
			0, 2, 4, 6, 9, 11, 14, 16, 19, 21, 24, 26, 28, 30, 32, 34
		};

		inline static constexpr auto TO_STRING_TABLE = std::array<const char, BYTE_COUNT>{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
		};

		[[nodiscard]] static constexpr std::optional<value_type> FromHexChar(char a_char) noexcept
		{
			constexpr auto TO_LOWER_MASK = 0x20;

			const auto rawChar = a_char | TO_LOWER_MASK;

			if (rawChar >= '0' && rawChar <= '9') {
				constexpr auto DECIMAL_CHAR_NUMERIC_OFFSET = '0';
				return rawChar - DECIMAL_CHAR_NUMERIC_OFFSET;
			}

			if (rawChar >= 'a' && rawChar <= 'f') {
				constexpr auto HEX_CHAR_NUMERIC_OFFSET = 'a' - 10;
				return rawChar - HEX_CHAR_NUMERIC_OFFSET;
			}

			return std::nullopt;
		}

		[[nodiscard]] static constexpr std::optional<value_type> FromHexStringAt(std::string_view a_value, std::size_t a_index) noexcept
		{
			if (a_index + 1 >= a_value.size()) {
				return std::nullopt;
			}

			const auto high = FromHexChar(a_value[a_index]);
			const auto low = FromHexChar(a_value[a_index + 1]);

			if (!high || !low) {
				return std::nullopt;
			}

			return (*high << 4) | *low;
		}

	public:
		container_type _data;
	};

	static_assert(std::is_standard_layout_v<Uuid>);
	static_assert(std::is_trivially_destructible_v<Uuid>);
	static_assert(std::is_trivially_copyable_v<Uuid>);

	constexpr void swap(Uuid& a_lhs, Uuid& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	template <>
	struct hash<REX::Uuid>
	{
	public:
		[[nodiscard]] std::size_t operator()(const REX::Uuid& a_key) const noexcept
		{
			return REX::Hash(std::string_view{ reinterpret_cast<const char*>(a_key.data()), a_key.size() });
		}
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<REX::Uuid>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Uuid& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<REX::Uuid>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::Uuid& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
