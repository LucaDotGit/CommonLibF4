#pragma once

namespace Scaleform::Render
{
	template <class T>
	class Rect
	{
	public:
		constexpr Rect() noexcept = default;

		constexpr Rect(T a_x1, T a_y1, T a_x2, T a_y2) noexcept :
			x1(a_x1),
			y1(a_y1),
			x2(a_x2),
			y2(a_y2)
		{
		}

		constexpr ~Rect() noexcept = default;

		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;

		constexpr auto operator=(const Rect&) noexcept -> Rect& = default;
		constexpr auto operator=(Rect&&) noexcept -> Rect& = default;

		[[nodiscard]]
		constexpr auto operator==(const Rect&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const Rect&) const noexcept = default;

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
		T x1; // 0x00
		T y1; // 0x??
		T x2; // 0x??
		T y2; // 0x??
	};

	using RectF = Rect<REX::Float32>;
	static_assert(sizeof(RectF) == 0x10);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<Scaleform::Render::Rect<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Rect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x1, a_value.y1, a_value.x2, a_value.y2);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class T>
	struct formatter<Scaleform::Render::Rect<T>> : public formatter<std::string>
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
		constexpr auto format(const Scaleform::Render::Rect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x1, a_value.y1, a_value.x2, a_value.y2);
		}
	};
}
#endif
