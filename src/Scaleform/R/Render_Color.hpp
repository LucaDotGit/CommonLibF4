#pragma once

namespace Scaleform::Render
{
	class Color
	{
	public:
		constexpr Color() noexcept = default;

		constexpr explicit Color(std::uint32_t a_raw) noexcept :
			raw(a_raw)
		{
		}

		constexpr Color(std::uint8_t a_red, std::uint8_t a_green, std::uint8_t a_blue, std::uint8_t a_alpha = 255)
			noexcept :
			channels{.blue = a_blue, .green = a_green, .red = a_red, .alpha = a_alpha}
		{
		}

		constexpr ~Color() noexcept = default;

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr auto operator=(const Color&) noexcept -> Color& = default;
		constexpr auto operator=(Color&&) noexcept -> Color& = default;

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
			std::uint8_t blue;	// 0x00
			std::uint8_t green; // 0x01
			std::uint8_t red;	// 0x02
			std::uint8_t alpha; // 0x03
		};

		static_assert(sizeof(Rgb32) == 0x04);

		// members
		union
		{
		public:
			Rgb32 channels;
			std::uint32_t raw;
		}; // 0x00
	};

	static_assert(sizeof(Color) == 0x04);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<Scaleform::Render::Color> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Color& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"({}, {}, {})"sv,
				a_value.channels.red,
				a_value.channels.green,
				a_value.channels.blue);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<Scaleform::Render::Color> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Color& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"({}, {}, {})"sv,
				a_value.channels.red,
				a_value.channels.green,
				a_value.channels.blue);
		}
	};
}
#endif
