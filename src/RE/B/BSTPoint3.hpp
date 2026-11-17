#pragma once

#include "RE/B/BSTPointDefaultOps.hpp"

namespace RE
{
	template <class T>
	class BSTPoint3Base
	{
	public:
		using value_type = T;

		constexpr BSTPoint3Base() noexcept = default;
		constexpr ~BSTPoint3Base() noexcept = default;

		constexpr BSTPoint3Base(value_type a_x, value_type a_y, value_type a_z) :
			x(a_x),
			y(a_y),
			z(a_z)
		{
		}

		constexpr BSTPoint3Base(const BSTPoint3Base&) noexcept = default;
		constexpr BSTPoint3Base(BSTPoint3Base&&) noexcept = default;

		constexpr auto operator=(const BSTPoint3Base&) noexcept -> BSTPoint3Base& = default;
		constexpr auto operator=(BSTPoint3Base&&) noexcept -> BSTPoint3Base& = default;

		[[nodiscard]]
		constexpr auto operator==(const BSTPoint3Base&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const BSTPoint3Base&) const noexcept = default;

		constexpr void swap(BSTPoint3Base& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}

		value_type x{static_cast<value_type>(0)}; // 0x00
		value_type y{static_cast<value_type>(0)}; // 0x??
		value_type z{static_cast<value_type>(0)}; // 0x??
	};

	template <class T, class Ops = BSTPointDefaultOps<T>>
	class BSTPoint3 : public BSTPoint3Base<T>, public BSTPointDefaultOps<T>
	{
	public:
	};

	using BSTPoint3I = BSTPoint3<std::int32_t>;
	static_assert(sizeof(BSTPoint3I) == 0x0C);

	using BSTPoint3U = BSTPoint3<std::uint32_t>;
	static_assert(sizeof(BSTPoint3U) == 0x0C);

	using BSTPoint3F = BSTPoint3<REX::Float32>;
	static_assert(sizeof(BSTPoint3F) == 0x0C);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class T>
	struct formatter<RE::BSTPoint3<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::BSTPoint3<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class T>
	struct formatter<RE::BSTPoint3<T>> : public formatter<std::string>
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
		constexpr auto format(const RE::BSTPoint3<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif
