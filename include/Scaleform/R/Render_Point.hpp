#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Point
	{
	public:
		constexpr Point() noexcept = default;

		constexpr Point(T a_x, T a_y) noexcept
			: x(a_x), y(a_y)
		{
		}

		constexpr ~Point() noexcept = default;

		constexpr Point(const Point&) noexcept = default;
		constexpr Point(Point&&) noexcept = default;

		constexpr Point& operator=(const Point&) noexcept = default;
		constexpr Point& operator=(Point&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Point&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Point&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Point&) const noexcept = default;

		[[nodiscard]] constexpr T& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr const T& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr Point operator+(const Point& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y };
		}

		[[nodiscard]] constexpr Point operator-(const Point& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y };
		}

		[[nodiscard]] constexpr Point operator*(const Point& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y };
		}

		[[nodiscard]] constexpr Point operator/(const Point& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y };
		}

		[[nodiscard]] constexpr Point operator*(T a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs };
		}

		[[nodiscard]] constexpr Point operator/(T a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs };
		}

		[[nodiscard]] constexpr Point operator-() const noexcept
		{
			return { -x, -y };
		}

		constexpr Point& operator+=(const Point& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			return *this;
		}

		constexpr Point& operator-=(const Point& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			return *this;
		}

		constexpr Point& operator*=(const Point& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			return *this;
		}

		constexpr Point& operator/=(const Point& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			return *this;
		}

		constexpr Point& operator+=(T a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			return *this;
		}

		constexpr Point& operator-=(T a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			return *this;
		}

		constexpr Point& operator*=(T a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			return *this;
		}

		constexpr Point& operator/=(T a_rhs) noexcept
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
		T x; // 00
		T y; // ??
	};

	extern template class Point<REX::Float32>;

	template <class T>
	constexpr void swap(Point<T>& a_lhs, Point<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(Point<REX::Float32>&, Point<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Point<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Point<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	extern template struct formatter<Scaleform::Render::Point<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<Scaleform::Render::Point<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Point<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	extern template struct formatter<Scaleform::Render::Point<REX::Float32>>;
}
#endif
