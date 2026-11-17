#pragma once

namespace RE
{
	template <class T>
	class NiRect
	{
	public:
		constexpr NiRect() noexcept = default;

		constexpr NiRect(T a_left, T a_top, T a_right, T a_bottom) noexcept :
			left(a_left),
			right(a_right),
			top(a_top),
			bottom(a_bottom)
		{
		}

		constexpr ~NiRect() noexcept = default;

		constexpr NiRect(const NiRect&) noexcept = default;
		constexpr NiRect(NiRect&&) noexcept = default;

		constexpr auto operator=(const NiRect&) noexcept -> NiRect& = default;
		constexpr auto operator=(NiRect&&) noexcept -> NiRect& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiRect&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiRect&) const noexcept = default;

		constexpr void swap(NiRect& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(left, a_other.left);
			std::swap(right, a_other.right);
			std::swap(top, a_other.top);
			std::swap(bottom, a_other.bottom);
		}

		// members
		T left{0};	 // 0x00
		T right{0};	 // 0x??
		T top{0};	 // 0x??
		T bottom{0}; // 0x??
	};

	using NiRectI = NiRect<std::int32_t>;
	static_assert(sizeof(NiRectI) == 0x10);

	using NiRectU = NiRect<std::uint32_t>;
	static_assert(sizeof(NiRectU) == 0x10);

	using NiRectF = NiRect<REX::Float32>;
	static_assert(sizeof(NiRectF) == 0x10);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<RE::NiRect<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::NiRect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"({}, {}, {}, {})"sv,
				a_value.left,
				a_value.top,
				a_value.right,
				a_value.bottom);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class T>
	struct formatter<RE::NiRect<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::NiRect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(
				a_context.out(),
				"({}, {}, {}, {})"sv,
				a_value.left,
				a_value.top,
				a_value.right,
				a_value.bottom);
		}
	};
}
#endif
