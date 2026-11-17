#pragma once

namespace RE
{
	class NiColorA
	{
	public:
		constexpr NiColorA() noexcept = default;

		constexpr NiColorA(REX::Float32 a_r, REX::Float32 a_g, REX::Float32 a_b, REX::Float32 a_a) noexcept :
			r(a_r),
			g(a_g),
			b(a_b),
			a(a_a)
		{
		}

		constexpr ~NiColorA() = default;

		constexpr NiColorA(const NiColorA&) = default;
		constexpr NiColorA(NiColorA&&) noexcept = default;

		constexpr auto operator=(const NiColorA&) -> NiColorA& = default;
		constexpr auto operator=(NiColorA&&) noexcept -> NiColorA& = default;

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
		REX::Float32 r{static_cast<REX::Float32>(0.0)}; // 0x00
		REX::Float32 g{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 b{static_cast<REX::Float32>(0.0)}; // 0x08
		REX::Float32 a{static_cast<REX::Float32>(0.0)}; // 0x0C
	};

	static_assert(sizeof(NiColorA) == 0x10);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiColorA> : public formatter<std::string>
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
		constexpr auto format(const RE::NiColorA& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.r, a_value.g, a_value.b, a_value.a);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::NiColorA> : public formatter<std::string>
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
		constexpr auto format(const RE::NiColorA& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.r, a_value.g, a_value.b, a_value.a);
		}
	};
}
#endif
