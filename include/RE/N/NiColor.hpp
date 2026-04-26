#pragma once

namespace RE
{
	class NiColor
	{
	public:
		constexpr NiColor() noexcept = default;

		constexpr NiColor(REX::Float32 a_r, REX::Float32 a_g, REX::Float32 a_b) noexcept
			: r(a_r), g(a_g), b(a_b)
		{
		}

		constexpr ~NiColor() = default;

		constexpr NiColor(const NiColor&) = default;
		constexpr NiColor(NiColor&&) noexcept = default;

		constexpr NiColor& operator=(const NiColor&) = default;
		constexpr NiColor& operator=(NiColor&&) noexcept = default;

		constexpr void swap(NiColor& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(r, a_other.r);
			std::swap(g, a_other.g);
			std::swap(b, a_other.b);
		}

		// members
		REX::Float32 r{ 0.0_f32 }; // 00
		REX::Float32 g{ 0.0_f32 }; // 04
		REX::Float32 b{ 0.0_f32 }; // 08
	};
	static_assert(sizeof(NiColor) == 0xC);

	constexpr void swap(NiColor& a_lhs, NiColor& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	class NiColorA
	{
	public:
		constexpr NiColorA() noexcept = default;

		constexpr NiColorA(REX::Float32 a_r, REX::Float32 a_g, REX::Float32 a_b, REX::Float32 a_a) noexcept
			: r(a_r), g(a_g), b(a_b), a(a_a)
		{
		}

		constexpr ~NiColorA() = default;

		constexpr NiColorA(const NiColorA&) = default;
		constexpr NiColorA(NiColorA&&) noexcept = default;

		constexpr NiColorA& operator=(const NiColorA&) = default;
		constexpr NiColorA& operator=(NiColorA&&) noexcept = default;

		constexpr void swap(NiColorA& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(r, a_other.r);
			std::swap(g, a_other.g);
			std::swap(b, a_other.b);
			std::swap(a, a_other.a);
		}

		// members
		REX::Float32 r{ 0.0_f32 }; // 00
		REX::Float32 g{ 0.0_f32 }; // 04
		REX::Float32 b{ 0.0_f32 }; // 08
		REX::Float32 a{ 0.0_f32 }; // 0C
	};
	static_assert(sizeof(NiColorA) == 0x10);

	constexpr void swap(NiColorA& a_lhs, NiColorA& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::NiColor>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiColor& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {})"sv, a_value.r, a_value.g, a_value.b);
		}
	};

	template <>
	struct formatter<RE::NiColorA>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiColorA& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.r, a_value.g, a_value.b, a_value.a);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::NiColor>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiColor& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {})"sv, a_value.r, a_value.g, a_value.b);
		}
	};

	template <>
	struct formatter<RE::NiColorA>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiColorA& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.r, a_value.g, a_value.b, a_value.a);
		}
	};
}
#endif
