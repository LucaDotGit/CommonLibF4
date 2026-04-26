#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Rect
	{
	public:
		constexpr Rect() noexcept = default;

		constexpr Rect(T a_x1, T a_y1, T a_x2, T a_y2) noexcept
			: x1(a_x1), y1(a_y1), x2(a_x2), y2(a_y2)
		{
		}

		constexpr ~Rect() noexcept = default;

		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;

		constexpr Rect& operator=(const Rect&) noexcept = default;
		constexpr Rect& operator=(Rect&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const Rect&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const Rect&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const Rect&) const noexcept = default;

		constexpr void swap(Rect& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x1, a_other.x1);
			std::swap(y1, a_other.y1);
			std::swap(x2, a_other.x2);
			std::swap(y2, a_other.y2);
		}

		// members
		T x1; // 00
		T y1; // ??
		T x2; // ??
		T y2; // ??
	};

	extern template class Rect<REX::Float32>;

	template <class T>
	constexpr void swap(Rect<T>& a_lhs, Rect<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(Rect<REX::Float32>&, Rect<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Rect<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Rect<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.x1, a_value.y1, a_value.x2, a_value.y2);
		}
	};

	extern template struct formatter<Scaleform::Render::Rect<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<Scaleform::Render::Rect<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const Scaleform::Render::Rect<T>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.x1, a_value.y1, a_value.x2, a_value.y2);
		}
	};

	extern template struct formatter<Scaleform::Render::Rect<REX::Float32>>;
}
#endif
