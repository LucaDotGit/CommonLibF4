#pragma once

#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"

namespace REX
{
	inline constexpr auto RGB_SIZE = static_cast<std::size_t>(3);
	inline constexpr auto RGBA_SIZE = static_cast<std::size_t>(4);

	class Color final
	{
	public:
		using value_type = std::uint8_t;
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

		inline static constexpr auto DEFAULT_ALPHA_VALUE = std::numeric_limits<value_type>::max();

		inline static constexpr auto MAX_SIZE = RGBA_SIZE;
		inline static constexpr auto HEXADECIMAL_RGB_STRING_SIZE = (RGB_SIZE * 2) + 1;
		inline static constexpr auto HEXADECIMAL_RGBA_STRING_SIZE = (RGBA_SIZE * 2) + 1;

		inline static constexpr auto MIN_FLOAT_VALUE = static_cast<REX::Float32>(0.0);
		inline static constexpr auto MAX_FLOAT_VALUE = static_cast<REX::Float32>(1.0);
		inline static constexpr auto FLOAT_MULTIPLIER =
			static_cast<REX::Float32>(std::numeric_limits<value_type>::max());

		constexpr Color() noexcept = default;
		constexpr ~Color() noexcept = default;

		constexpr Color(value_type a_red, value_type a_green, value_type a_blue) noexcept :
			_red(a_red),
			_green(a_green),
			_blue(a_blue)
		{
		}

		constexpr Color(value_type a_red, value_type a_green, value_type a_blue, value_type a_alpha) noexcept :
			_red(a_red),
			_green(a_green),
			_blue(a_blue),
			_alpha(a_alpha)
		{
		}

		constexpr explicit Color(std::array<value_type, RGB_SIZE> a_color) noexcept :
			_red(a_color[0]),
			_green(a_color[1]),
			_blue(a_color[2]),
			_alpha(a_color[3])
		{
		}

		constexpr explicit Color(std::span<const value_type, RGB_SIZE> a_color) noexcept :
			_red(a_color[0]),
			_green(a_color[1]),
			_blue(a_color[2]),
			_alpha(a_color[3])
		{
		}

		constexpr explicit Color(std::array<value_type, RGBA_SIZE> a_color) noexcept :
			_red(a_color[0]),
			_green(a_color[1]),
			_blue(a_color[2]),
			_alpha(a_color[3])
		{
		}

		constexpr explicit Color(std::span<const value_type, RGBA_SIZE> a_color) noexcept :
			_red(a_color[0]),
			_green(a_color[1]),
			_blue(a_color[2]),
			_alpha(a_color[3])
		{
		}

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr auto operator=(std::array<value_type, RGB_SIZE> a_color) noexcept -> Color&
		{
			_red = a_color[0];
			_green = a_color[1];
			_blue = a_color[2];
			return *this;
		}

		constexpr auto operator=(std::span<const value_type, RGB_SIZE> a_color) noexcept -> Color&
		{
			_red = a_color[0];
			_green = a_color[1];
			_blue = a_color[2];
			return *this;
		}

		constexpr auto operator=(std::array<value_type, RGBA_SIZE> a_color) noexcept -> Color&
		{
			_red = a_color[0];
			_green = a_color[1];
			_blue = a_color[2];
			_alpha = a_color[3];
			return *this;
		}

		constexpr auto operator=(std::span<const value_type, RGBA_SIZE> a_color) noexcept -> Color&
		{
			_red = a_color[0];
			_green = a_color[1];
			_blue = a_color[2];
			_alpha = a_color[3];
			return *this;
		}

		constexpr auto operator=(const Color&) noexcept -> Color& = default;
		constexpr auto operator=(Color&&) noexcept -> Color& = default;

		[[nodiscard]]
		constexpr auto operator==(const Color&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Color&) const noexcept = default;

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
		constexpr auto view() noexcept -> auto
		{
			return std::span(reinterpret_cast<std::array<value_type, MAX_SIZE>&>(_red));
		}

		[[nodiscard]]
		constexpr auto view() const noexcept -> auto
		{
			return std::span(reinterpret_cast<const std::array<value_type, MAX_SIZE>&>(_red));
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return view()[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return view()[a_index];
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
			return view().data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return view().data();
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
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto max_size() const noexcept -> size_type
		{
			return MAX_SIZE;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
		constexpr auto empty() const noexcept -> bool
		{
			return false;
		}

		[[nodiscard]]
		constexpr auto GetRed() const noexcept
		{
			return _red;
		}

		void SetRed(value_type a_red) noexcept
		{
			_red = a_red;
		}

		[[nodiscard]]
		constexpr auto GetGreen() const noexcept
		{
			return _green;
		}

		void SetGreen(value_type a_green) noexcept
		{
			_green = a_green;
		}

		[[nodiscard]]
		constexpr auto GetBlue() const noexcept
		{
			return _blue;
		}

		void SetBlue(value_type a_blue) noexcept
		{
			_blue = a_blue;
		}

		[[nodiscard]]
		constexpr auto GetAlpha() const noexcept
		{
			return _alpha;
		}

		void SetAlpha(value_type a_alpha) noexcept
		{
			_alpha = a_alpha;
		}

		[[nodiscard]]
		static constexpr auto FromArray(std::span<const value_type> a_color) noexcept -> std::optional<Color>
		{
			if (a_color.size() == RGB_SIZE) {
				return Color(std::span<const value_type, RGB_SIZE>{a_color.begin(), a_color.end()});
			}

			if (a_color.size() == RGBA_SIZE) {
				return Color(std::span<const value_type, RGBA_SIZE>{a_color.begin(), a_color.end()});
			}

			return std::nullopt;
		}

		[[nodiscard]]
		static constexpr auto FromHexRgb(std::uint32_t a_value) noexcept -> Color
		{
			return {
				static_cast<value_type>(
					(a_value >> std::numeric_limits<std::uint8_t>::digits * 2) &
					std::numeric_limits<std::uint8_t>::max()),
				static_cast<value_type>(
					(a_value >> std::numeric_limits<std::uint8_t>::digits * 1) &
					std::numeric_limits<std::uint8_t>::max()),
				static_cast<value_type>(a_value & std::numeric_limits<std::uint8_t>::max()),
				DEFAULT_ALPHA_VALUE
			};
		}

		[[nodiscard]]
		constexpr auto ToHexRgb() const noexcept -> std::uint32_t
		{
			return (static_cast<std::uint32_t>(GetRed()) << std::numeric_limits<std::uint8_t>::digits * 2) |
				   (static_cast<std::uint32_t>(GetGreen()) << std::numeric_limits<std::uint8_t>::digits * 1) |
				   static_cast<std::uint32_t>(GetBlue());
		}

		[[nodiscard]]
		static constexpr auto FromHexRgba(std::uint32_t a_value) noexcept -> Color
		{
			return {
				static_cast<value_type>(
					(a_value >> std::numeric_limits<std::uint8_t>::digits * 3) &
					std::numeric_limits<std::uint8_t>::max()),
				static_cast<value_type>(
					(a_value >> std::numeric_limits<std::uint8_t>::digits * 2) &
					std::numeric_limits<std::uint8_t>::max()),
				static_cast<value_type>(
					(a_value >> std::numeric_limits<std::uint8_t>::digits * 1) &
					std::numeric_limits<std::uint8_t>::max()),
				static_cast<value_type>(a_value & std::numeric_limits<std::uint8_t>::max())
			};
		}

		[[nodiscard]]
		constexpr auto ToHexRgba() const noexcept -> std::uint32_t
		{
			return (static_cast<std::uint32_t>(GetRed()) << std::numeric_limits<std::uint8_t>::digits * 3) |
				   (static_cast<std::uint32_t>(GetGreen()) << std::numeric_limits<std::uint8_t>::digits * 2) |
				   (static_cast<std::uint32_t>(GetBlue()) << std::numeric_limits<std::uint8_t>::digits * 1) |
				   static_cast<std::uint32_t>(GetAlpha());
		}

		[[nodiscard]]
		static constexpr auto FromFloatRgb(std::span<const REX::Float32> a_color) noexcept -> std::optional<Color>
		{
			if (a_color.size() != RGB_SIZE) {
				return std::nullopt;
			}

			return Color{
				static_cast<value_type>(std::clamp(a_color[0], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER),
				static_cast<value_type>(std::clamp(a_color[1], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER),
				static_cast<value_type>(std::clamp(a_color[2], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER)
			};
		}

		[[nodiscard]]
		constexpr auto ToFloatRgb() const noexcept -> std::array<REX::Float32, RGB_SIZE>
		{
			return {
				static_cast<REX::Float32>(GetRed()) / FLOAT_MULTIPLIER,
				static_cast<REX::Float32>(GetGreen()) / FLOAT_MULTIPLIER,
				static_cast<REX::Float32>(GetBlue()) / FLOAT_MULTIPLIER
			};
		}

		[[nodiscard]]
		static constexpr auto FromFloatRgba(std::span<const REX::Float32> a_color) noexcept -> std::optional<Color>
		{
			if (a_color.size() != RGBA_SIZE) {
				return std::nullopt;
			}

			return Color{
				static_cast<value_type>(std::clamp(a_color[0], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER),
				static_cast<value_type>(std::clamp(a_color[1], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER),
				static_cast<value_type>(std::clamp(a_color[2], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER),
				static_cast<value_type>(std::clamp(a_color[3], MIN_FLOAT_VALUE, MAX_FLOAT_VALUE) * FLOAT_MULTIPLIER)
			};
		}

		[[nodiscard]]
		constexpr auto ToFloatRgba() const noexcept -> std::array<REX::Float32, RGBA_SIZE>
		{
			return {
				static_cast<REX::Float32>(GetRed()) / FLOAT_MULTIPLIER,
				static_cast<REX::Float32>(GetGreen()) / FLOAT_MULTIPLIER,
				static_cast<REX::Float32>(GetBlue()) / FLOAT_MULTIPLIER,
				static_cast<REX::Float32>(GetAlpha()) / FLOAT_MULTIPLIER
			};
		}

		[[nodiscard]]
		auto ToHexRgbString(std::span<char> a_buffer) const noexcept -> std::string_view;
		[[nodiscard]]
		auto ToHexRgbaString(std::span<char> a_buffer) const noexcept -> std::string_view;

		[[nodiscard]]
		auto ToHexRgbString() const -> std::string;
		[[nodiscard]]
		auto ToHexRgbaString() const -> std::string;

		[[nodiscard]]
		auto ToString() const -> std::string;

		constexpr void swap(Color& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_red, a_other._red);
			std::swap(_green, a_other._green);
			std::swap(_blue, a_other._blue);
			std::swap(_alpha, a_other._alpha);
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		value_type _red{0};
		value_type _green{0};
		value_type _blue{0};
		value_type _alpha{DEFAULT_ALPHA_VALUE};
		// NOLINTEND(readability-identifier-naming)
	};

	static_assert(std::is_standard_layout_v<Color>);
	static_assert(std::is_trivially_destructible_v<Color>);
	static_assert(std::is_trivially_copyable_v<Color>);
	static_assert(std::is_trivially_move_constructible_v<Color>);
}

namespace std
{
	template <>
	struct hash<REX::Color>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::Color& a_key) const noexcept -> std::size_t
		{
			return REX::HashRange(a_key);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<REX::Color> : public formatter<std::string>
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
		constexpr auto format(const REX::Color& a_value, FormatContext& a_context) const
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
	struct formatter<REX::Color> : public formatter<std::string>
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
		constexpr auto format(const REX::Color& a_value, FormatContext& a_context) const
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
	struct meta<REX::Color>
	{
		inline static constexpr auto value = [](auto&& a_self) -> decltype(auto) {
			return a_self.view();
		};
	};
}
#endif
