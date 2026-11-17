#pragma once

namespace RE
{
	class NiPoint2
	{
	public:
		static const NiPoint2 ZERO;
		static const NiPoint2 UNIT;
		static const NiPoint2 UNIT_X;
		static const NiPoint2 UNIT_Y;

		constexpr NiPoint2() noexcept = default;

		constexpr NiPoint2(REX::Float32 a_x, REX::Float32 a_y) noexcept :
			x(a_x),
			y(a_y)
		{
		}

		constexpr ~NiPoint2() noexcept = default;

		constexpr NiPoint2(const NiPoint2&) noexcept = default;
		constexpr NiPoint2(NiPoint2&&) noexcept = default;

		constexpr auto operator=(const NiPoint2&) noexcept -> NiPoint2& = default;
		constexpr auto operator=(NiPoint2&&) noexcept -> NiPoint2& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiPoint2&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiPoint2&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> REX::Float32&
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const REX::Float32&
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator+(const NiPoint2& a_rhs) const noexcept -> NiPoint2
		{
			return {x + a_rhs.x, y + a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator-(const NiPoint2& a_rhs) const noexcept -> NiPoint2
		{
			return {x - a_rhs.x, y - a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator*(const NiPoint2& a_rhs) const noexcept -> NiPoint2
		{
			return {x * a_rhs.x, y * a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator/(const NiPoint2& a_rhs) const noexcept -> NiPoint2
		{
			return {x / a_rhs.x, y / a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 a_rhs) const noexcept -> NiPoint2
		{
			return {x * a_rhs, y * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 a_rhs) const noexcept -> NiPoint2
		{
			return {x / a_rhs, y / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> NiPoint2
		{
			return {-x, -y};
		}

		constexpr auto operator+=(const NiPoint2& a_rhs) noexcept -> NiPoint2&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			return *this;
		}

		constexpr auto operator-=(const NiPoint2& a_rhs) noexcept -> NiPoint2&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			return *this;
		}

		constexpr auto operator*=(const NiPoint2& a_rhs) noexcept -> NiPoint2&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			return *this;
		}

		constexpr auto operator/=(const NiPoint2& a_rhs) noexcept -> NiPoint2&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			return *this;
		}

		constexpr auto operator+=(REX::Float32 a_rhs) noexcept -> NiPoint2&
		{
			x += a_rhs;
			y += a_rhs;
			return *this;
		}

		constexpr auto operator-=(REX::Float32 a_rhs) noexcept -> NiPoint2&
		{
			x -= a_rhs;
			y -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 a_rhs) noexcept -> NiPoint2&
		{
			x *= a_rhs;
			y *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 a_rhs) noexcept -> NiPoint2&
		{
			x /= a_rhs;
			y /= a_rhs;
			return *this;
		}

		constexpr void swap(NiPoint2& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
		}

		// members
		REX::Float32 x{static_cast<REX::Float32>(0.0)}; // 0x00
		REX::Float32 y{static_cast<REX::Float32>(0.0)}; // 0x04
	};

	static_assert(sizeof(NiPoint2) == 0x08);

	inline constexpr auto NiPoint2::ZERO = NiPoint2();
	inline constexpr auto NiPoint2::UNIT = NiPoint2(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0));
	inline constexpr auto NiPoint2::UNIT_X = NiPoint2(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint2::UNIT_Y = NiPoint2(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0));
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiPoint2> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint2& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::NiPoint2> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint2& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};
}
#endif
