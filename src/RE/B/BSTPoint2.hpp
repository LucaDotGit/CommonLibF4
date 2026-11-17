#pragma once

#include "RE/B/BSTPointDefaultOps.hpp"

namespace RE
{
	template <class T>
	class BSTPoint2Base
	{
	public:
		using value_type = T;

		constexpr BSTPoint2Base() noexcept = default;
		constexpr ~BSTPoint2Base() noexcept = default;

		constexpr BSTPoint2Base(value_type a_x, value_type a_y) :
			x(a_x),
			y(a_y)
		{
		}

		constexpr BSTPoint2Base(const BSTPoint2Base&) noexcept = default;
		constexpr BSTPoint2Base(BSTPoint2Base&&) noexcept = default;

		constexpr auto operator=(const BSTPoint2Base&) noexcept -> BSTPoint2Base& = default;
		constexpr auto operator=(BSTPoint2Base&&) noexcept -> BSTPoint2Base& = default;

		[[nodiscard]]
		constexpr auto operator==(const BSTPoint2Base&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const BSTPoint2Base&) const noexcept = default;

		constexpr void swap(BSTPoint2Base& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
		}

		value_type x{static_cast<value_type>(0)}; // 0x00
		value_type y{static_cast<value_type>(0)}; // 0x??
	};

	template <class T, class Ops = BSTPointDefaultOps<T>>
	class BSTPoint2 : public BSTPoint2Base<T>, public BSTPointDefaultOps<T>
	{
	public:
	};

	using BSTPoint2I = BSTPoint2<std::int32_t>;
	static_assert(sizeof(BSTPoint2I) == 0x08);

	using BSTPoint2U = BSTPoint2<std::uint32_t>;
	static_assert(sizeof(BSTPoint2U) == 0x08);

	using BSTPoint2F = BSTPoint2<REX::Float32>;
	static_assert(sizeof(BSTPoint2F) == 0x08);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<RE::BSTPoint2<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::BSTPoint2<T>& a_value, FormatContext& a_context) const
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
	struct formatter<RE::BSTPoint2<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::BSTPoint2<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};
}
#endif
