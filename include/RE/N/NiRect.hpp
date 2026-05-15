#pragma once

namespace RE
{
	template <class T>
	class NiRect
	{
	public:
		constexpr NiRect() noexcept = default;

		constexpr NiRect(T a_left, T a_top, T a_right, T a_bottom) noexcept
			: left(a_left), right(a_right), top(a_top), bottom(a_bottom)
		{
		}

		constexpr ~NiRect() noexcept = default;

		constexpr NiRect(const NiRect&) noexcept = default;
		constexpr NiRect(NiRect&&) noexcept = default;

		constexpr NiRect& operator=(const NiRect&) noexcept = default;
		constexpr NiRect& operator=(NiRect&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiRect&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiRect&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiRect&) const noexcept = default;

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
		T left{ 0 };   // 00
		T right{ 0 };  // ??
		T top{ 0 };	   // ??
		T bottom{ 0 }; // ??
	};

	extern template class NiRect<std::int32_t>;
	extern template class NiRect<std::uint32_t>;
	extern template class NiRect<REX::Float32>;

	template <class T>
	constexpr void swap(NiRect<T>& a_lhs, NiRect<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap<std::int32_t>(NiRect<std::int32_t>&, NiRect<std::int32_t>&) noexcept;
	extern template void swap<std::uint32_t>(NiRect<std::uint32_t>&, NiRect<std::uint32_t>&) noexcept;
	extern template void swap<REX::Float32>(NiRect<REX::Float32>&, NiRect<REX::Float32>&) noexcept;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<RE::NiRect<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiRect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.left, a_value.top, a_value.right, a_value.bottom);
		}
	};

	extern template struct formatter<RE::NiRect<std::int32_t>>;
	extern template struct formatter<RE::NiRect<std::uint32_t>>;
	extern template struct formatter<RE::NiRect<REX::Float32>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<RE::NiRect<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiRect<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.left, a_value.top, a_value.right, a_value.bottom);
		}
	};

	extern template struct formatter<RE::NiRect<std::int32_t>>;
	extern template struct formatter<RE::NiRect<std::uint32_t>>;
	extern template struct formatter<RE::NiRect<REX::Float32>>;
}
#endif
