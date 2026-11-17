#pragma once

namespace RE
{
	class NiColor
	{
	public:
		constexpr NiColor() noexcept = default;

		constexpr NiColor(REX::Float32 a_r, REX::Float32 a_g, REX::Float32 a_b) noexcept :
			r(a_r),
			g(a_g),
			b(a_b)
		{
		}

		constexpr ~NiColor() = default;

		constexpr NiColor(const NiColor&) = default;
		constexpr NiColor(NiColor&&) noexcept = default;

		constexpr auto operator=(const NiColor&) -> NiColor& = default;
		constexpr auto operator=(NiColor&&) noexcept -> NiColor& = default;

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
		REX::Float32 r{static_cast<REX::Float32>(0.0)}; // 0x00
		REX::Float32 g{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 b{static_cast<REX::Float32>(0.0)}; // 0x08
	};

	static_assert(sizeof(NiColor) == 0x0C);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiColor> : public formatter<std::string>
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
		constexpr auto format(const RE::NiColor& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.r, a_value.g, a_value.b);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::NiColor> : public formatter<std::string>
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
		constexpr auto format(const RE::NiColor& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.r, a_value.g, a_value.b);
		}
	};
}
#endif
