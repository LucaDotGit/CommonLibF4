#pragma once

#include "REX/Casting.hpp"
#include "REX/Comparison.hpp"
#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"
#include "REX/Localization.hpp"

namespace REX
{
	class Uuid final
	{
	public:
		inline static constexpr auto MAX_SIZE = static_cast<std::size_t>(16);
		inline static constexpr auto MAX_STRING_SIZE = static_cast<std::size_t>(36);

		using value_type = std::uint8_t;
		using container_type = std::array<value_type, MAX_SIZE>;
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

		constexpr explicit Uuid(container_type a_data) noexcept :
			_data(a_data)
		{
		}

		constexpr Uuid(const Uuid&) noexcept = default;
		constexpr Uuid(Uuid&&) noexcept = default;

		constexpr auto operator=(Uuid&&) noexcept -> Uuid& = default;
		constexpr auto operator=(const Uuid&) noexcept -> Uuid& = default;

		[[nodiscard]]
		constexpr auto operator==(const Uuid&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Uuid&) const noexcept = default;

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
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return _data.data() + size();
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
			return _data.size();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return _data.max_size();
		}

		[[nodiscard]]
		static auto Generate() noexcept -> Uuid;

		[[nodiscard]]
		static constexpr auto FromArray(std::span<const value_type, MAX_SIZE> a_bytes) noexcept -> std::optional<Uuid>
		{
			auto bytes = container_type();
			std::ranges::copy(a_bytes, bytes.begin());
			return Uuid(bytes);
		}

		[[nodiscard]]
		static constexpr auto FromBytes(std::span<const value_type> a_bytes) noexcept -> std::optional<Uuid>
		{
			if (a_bytes.size() != MAX_SIZE) {
				return std::nullopt;
			}

			auto bytes = container_type();
			std::ranges::copy(a_bytes, bytes.begin());
			return Uuid(bytes);
		}

		[[nodiscard]]
		static constexpr auto FromString(std::string_view a_value) noexcept -> std::optional<Uuid>
		{
			if (a_value.size() != MAX_STRING_SIZE) {
				return std::nullopt;
			}

			for (const auto separatorPosition : SEPARATOR_POSITIONS) {
				if (a_value[separatorPosition] != SEPARATOR_CHAR) {
					return std::nullopt;
				}
			}

			auto bytes = container_type();

			for (auto i = static_cast<std::size_t>(0); i < bytes.size(); i++) {
				const auto byte = FromHexStringAt(a_value, FROM_STRING_TABLE[i]);
				if (!byte.has_value()) {
					return std::nullopt;
				}

				bytes[i] = byte.value();
			}

			return Uuid(bytes);
		}

		[[nodiscard]]
		constexpr auto ToString(std::span<char> a_buffer) const noexcept -> std::string_view
		{
			if (a_buffer.size() < MAX_STRING_SIZE) {
				return {};
			}

			for (const auto separatorPosition : SEPARATOR_POSITIONS) {
				a_buffer[separatorPosition] = SEPARATOR_CHAR;
			}

			for (auto i = static_cast<std::size_t>(0); i < MAX_SIZE; i++) {
				constexpr auto HIGH_NIBBLE_SHIFT = static_cast<value_type>(4);
				constexpr auto LOW_NIBBLE_MASK = static_cast<value_type>(0x0F);

				const auto byte = _data[i];
				const auto highNibble = (byte >> HIGH_NIBBLE_SHIFT) & LOW_NIBBLE_MASK;
				const auto lowNibble = byte & LOW_NIBBLE_MASK;

				a_buffer[FROM_STRING_TABLE[i]] = TO_STRING_TABLE[REX::ToUnsigned(highNibble)];
				a_buffer[FROM_STRING_TABLE[i] + 1] = TO_STRING_TABLE[REX::ToUnsigned(lowNibble)];
			}

			return {a_buffer.begin(), a_buffer.end()};
		}

		[[nodiscard]]
		constexpr auto ToString() const -> std::string
		{
			auto buffer = std::array<char, MAX_STRING_SIZE>();
			const auto bufferView = ToString(buffer);
			return std::string(bufferView);
		}

		constexpr void swap(Uuid& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

	private:
		inline static constexpr auto SEPARATOR_CHAR = '-';

		inline static constexpr auto SEPARATOR_POSITIONS = std::array{
			static_cast<std::size_t>(8),
			static_cast<std::size_t>(13),
			static_cast<std::size_t>(18),
			static_cast<std::size_t>(23)
		};

		inline static constexpr auto FROM_STRING_TABLE =
			std::array<const std::size_t, MAX_SIZE>{0, 2, 4, 6, 9, 11, 14, 16, 19, 21, 24, 26, 28, 30, 32, 34};

		inline static constexpr auto TO_STRING_TABLE = std::array<
			const char,
			MAX_SIZE>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

		[[nodiscard]]
		static constexpr auto FromHexChar(char a_char) noexcept -> std::optional<value_type>
		{
			const auto lowerChar = REX::ToLower(a_char);

			if (lowerChar >= REX::MIN_DIGIT_CHAR<char> && lowerChar <= REX::MAX_DIGIT_CHAR<char>) {
				constexpr auto DECIMAL_CHAR_NUMERIC_OFFSET = static_cast<value_type>(REX::MIN_DIGIT_CHAR<char>);
				return static_cast<value_type>(lowerChar - DECIMAL_CHAR_NUMERIC_OFFSET);
			}

			if (lowerChar >= REX::MIN_LOWER_HEXADECIMAL_LETTER_CHAR<char> &&
				lowerChar <= REX::MAX_LOWER_HEXADECIMAL_LETTER_CHAR<char>) {
				constexpr auto DIGIT_CHAR_COUNT =
					static_cast<value_type>(REX::MAX_DIGIT_CHAR<char> - REX::MIN_DIGIT_CHAR<char> + 1);
				constexpr auto HEXADECIMAL_CHAR_NUMERIC_OFFSET =
					static_cast<value_type>(REX::MIN_LOWER_HEXADECIMAL_LETTER_CHAR<char> - DIGIT_CHAR_COUNT);
				return static_cast<value_type>(lowerChar - HEXADECIMAL_CHAR_NUMERIC_OFFSET);
			}

			return std::nullopt;
		}

		[[nodiscard]]
		static constexpr auto FromHexStringAt(std::string_view a_value, std::size_t a_index) noexcept
			-> std::optional<value_type>
		{
			if (a_index + 1 >= a_value.size()) {
				return std::nullopt;
			}

			const auto highPart = FromHexChar(a_value[a_index]);
			const auto lowPart = FromHexChar(a_value[a_index + 1]);

			if (!highPart.has_value() || !lowPart.has_value()) {
				return std::nullopt;
			}

			return static_cast<value_type>((highPart.value() << 4) | lowPart.value());
		}

	public:
		// NOLINTBEGIN(readability-identifier-naming)
		container_type _data;
		// NOLINTEND(readability-identifier-naming)
	};

	static_assert(std::is_standard_layout_v<Uuid>);
	static_assert(std::is_trivially_destructible_v<Uuid>);
	static_assert(std::is_trivially_copyable_v<Uuid>);

	static_assert([]() consteval noexcept -> bool {
		constexpr auto UUID_01 = "62470F2D-F92B-4189-8AF6-157310DADC8B"sv;
		constexpr auto UUID_02 = std::array<const Uuid::value_type, Uuid::MAX_SIZE>{
			0x62,
			0x47,
			0x0F,
			0x2D,
			0xF9,
			0x2B,
			0x41,
			0x89,
			0x8A,
			0xF6,
			0x15,
			0x73,
			0x10,
			0xDA,
			0xDC,
			0x8B
		};

		return Uuid::FromString(UUID_01) == Uuid::FromArray(UUID_02);
	}());

	static_assert([]() consteval noexcept -> bool {
		constexpr auto UUID_01 = "62470F2D-F92B-4189-8AF6-157310DADC8B"sv;
		constexpr auto UUID_02 = Uuid::FromString(UUID_01);

		return UUID_02 && REX::EqualsIgnoreCase(std::string_view(UUID_02->ToString()), UUID_01);
	}());

	static_assert([]() consteval noexcept -> bool {
		constexpr auto INVALID_UUID = "62470F2D/F92B-4189-8AF6-157310DADC8B"sv;
		return !Uuid::FromString(INVALID_UUID);
	}());
}

namespace std
{
	template <>
	struct hash<REX::Uuid>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Uuid& a_key) const noexcept -> std::size_t
		{
			return REX::HashRange(a_key);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REX::Uuid> : public formatter<std::string>
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
		constexpr auto format(const REX::Uuid& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<REX::Uuid> : public formatter<std::string>
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
		constexpr auto format(const REX::Uuid& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <>
	struct meta<REX::Uuid>
	{
	public:
		using self_type = REX::Uuid;
		using other_type = std::string;

		inline static constexpr auto read_fn =
			[](self_type& a_self, const other_type& a_other, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = self_type::FromString(a_other);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid UUID"sv;
				return;
			}

			a_self = std::move(result).value();
		};

		inline static constexpr auto write_fn = [](const self_type& a_self, other_type& a_other) -> void {
			a_other = a_self.ToString();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};
}
#endif
