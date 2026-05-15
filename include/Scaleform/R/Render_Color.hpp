#pragma once

namespace Scaleform::Render
{
	class Color
	{
	public:
		constexpr Color() noexcept = default;

		constexpr Color(std::uint32_t a_raw) noexcept
			: raw(a_raw)
		{
		}

		constexpr Color(std::uint8_t a_r, std::uint8_t a_g, std::uint8_t a_b, std::uint8_t a_a = 255) noexcept
			: channels{ .blue = a_b, .green = a_g, .red = a_r, .alpha = a_a }
		{
		}

		constexpr ~Color() noexcept = default;

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) noexcept = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr void swap(Color& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(raw, a_other.raw);
		}

		class Rgb32
		{
		public:
			// members
			std::uint8_t blue;	// 00
			std::uint8_t green; // 01
			std::uint8_t red;	// 02
			std::uint8_t alpha; // 03
		};
		static_assert(sizeof(Rgb32) == 0x04);

		// members
		union
		{
			Rgb32 channels;
			std::uint32_t raw;
		}; // 00
	};
	static_assert(sizeof(Color) == 0x04);

	constexpr void swap(Color& a_lhs, Color& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<Scaleform::Render::Color>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Color& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.channels.red, a_value.channels.green, a_value.channels.blue);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<Scaleform::Render::Color>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Color& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.channels.red, a_value.channels.green, a_value.channels.blue);
		}
	};
}
#endif
