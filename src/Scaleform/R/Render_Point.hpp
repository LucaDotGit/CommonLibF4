#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Point
	{
	public:
		constexpr Point() noexcept = default;

		constexpr Point(T a_x, T a_y) noexcept :
			x(a_x),
			y(a_y)
		{
		}

		constexpr ~Point() noexcept = default;

		constexpr Point(const Point&) noexcept = default;
		constexpr Point(Point&&) noexcept = default;

		constexpr auto operator=(const Point&) noexcept -> Point& = default;
		constexpr auto operator=(Point&&) noexcept -> Point& = default;

		[[nodiscard]]
		constexpr auto operator==(const Point&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Point&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> T&
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const T&
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator+(const Point& a_rhs) const noexcept -> Point
		{
			return {x + a_rhs.x, y + a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator-(const Point& a_rhs) const noexcept -> Point
		{
			return {x - a_rhs.x, y - a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator*(const Point& a_rhs) const noexcept -> Point
		{
			return {x * a_rhs.x, y * a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator/(const Point& a_rhs) const noexcept -> Point
		{
			return {x / a_rhs.x, y / a_rhs.y};
		}

		[[nodiscard]]
		constexpr auto operator*(T a_rhs) const noexcept -> Point
		{
			return {x * a_rhs, y * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(T a_rhs) const noexcept -> Point
		{
			return {x / a_rhs, y / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> Point
		{
			return {-x, -y};
		}

		constexpr auto operator+=(const Point& a_rhs) noexcept -> Point&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			return *this;
		}

		constexpr auto operator-=(const Point& a_rhs) noexcept -> Point&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			return *this;
		}

		constexpr auto operator*=(const Point& a_rhs) noexcept -> Point&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			return *this;
		}

		constexpr auto operator/=(const Point& a_rhs) noexcept -> Point&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			return *this;
		}

		constexpr auto operator+=(T a_rhs) noexcept -> Point&
		{
			x += a_rhs;
			y += a_rhs;
			return *this;
		}

		constexpr auto operator-=(T a_rhs) noexcept -> Point&
		{
			x -= a_rhs;
			y -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(T a_rhs) noexcept -> Point&
		{
			x *= a_rhs;
			y *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(T a_rhs) noexcept -> Point&
		{
			x /= a_rhs;
			y /= a_rhs;
			return *this;
		}

		constexpr void swap(Point& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
		}

		// members
		T x; // 0x00
		T y; // 0x??
	};

	using PointF = Point<REX::Float32>;
	static_assert(sizeof(PointF) == 0x08);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Point<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Point<T>& a_value, FormatContext& a_context) const
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
	template <class T>
	struct formatter<Scaleform::Render::Point<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Point<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};
}
#endif
