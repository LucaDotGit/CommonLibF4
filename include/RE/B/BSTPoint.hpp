#pragma once

namespace RE
{
	template <class T>
	class BSTPointDefaultOps
	{
	public:
	};

	extern template class BSTPointDefaultOps<std::int8_t>;
	extern template class BSTPointDefaultOps<std::uint8_t>;
	extern template class BSTPointDefaultOps<std::int16_t>;
	extern template class BSTPointDefaultOps<std::uint16_t>;
	extern template class BSTPointDefaultOps<std::int32_t>;
	extern template class BSTPointDefaultOps<std::uint32_t>;
	extern template class BSTPointDefaultOps<REX::Float32>;
	extern template class BSTPointDefaultOps<REX::Float64>;

	template <class T>
	class BSTPoint2Base
	{
	public:
		constexpr BSTPoint2Base() noexcept = default;
		constexpr ~BSTPoint2Base() noexcept = default;

		constexpr BSTPoint2Base(T a_x, T a_y)
			: x(a_x), y(a_y)
		{
		}

		constexpr BSTPoint2Base(const BSTPoint2Base&) noexcept = default;
		constexpr BSTPoint2Base(BSTPoint2Base&&) noexcept = default;

		constexpr BSTPoint2Base& operator=(const BSTPoint2Base&) noexcept = default;
		constexpr BSTPoint2Base& operator=(BSTPoint2Base&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const BSTPoint2Base&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const BSTPoint2Base&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const BSTPoint2Base&) const noexcept = default;

		constexpr void swap(BSTPoint2Base& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
		}

		T x{}; // 00
		T y{}; // ??
	};

	extern template class BSTPoint2Base<std::int8_t>;
	extern template class BSTPoint2Base<std::uint8_t>;
	extern template class BSTPoint2Base<std::int16_t>;
	extern template class BSTPoint2Base<std::uint16_t>;
	extern template class BSTPoint2Base<std::int32_t>;
	extern template class BSTPoint2Base<std::uint32_t>;
	extern template class BSTPoint2Base<REX::Float32>;
	extern template class BSTPoint2Base<REX::Float64>;

	template <class T>
	constexpr void swap(BSTPoint2Base<T>& a_lhs, BSTPoint2Base<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(BSTPoint2Base<std::int8_t>&, BSTPoint2Base<std::int8_t>&) noexcept;
	extern template void swap(BSTPoint2Base<std::uint8_t>&, BSTPoint2Base<std::uint8_t>&) noexcept;
	extern template void swap(BSTPoint2Base<std::int16_t>&, BSTPoint2Base<std::int16_t>&) noexcept;
	extern template void swap(BSTPoint2Base<std::uint16_t>&, BSTPoint2Base<std::uint16_t>&) noexcept;
	extern template void swap(BSTPoint2Base<std::int32_t>&, BSTPoint2Base<std::int32_t>&) noexcept;
	extern template void swap(BSTPoint2Base<std::uint32_t>&, BSTPoint2Base<std::uint32_t>&) noexcept;
	extern template void swap(BSTPoint2Base<REX::Float32>&, BSTPoint2Base<REX::Float32>&) noexcept;
	extern template void swap(BSTPoint2Base<REX::Float64>&, BSTPoint2Base<REX::Float64>&) noexcept;

	template <class T, class Ops = BSTPointDefaultOps<T>>
	class BSTPoint2
		: public BSTPoint2Base<T>,
		  public BSTPointDefaultOps<T>
	{
	public:
	};

	extern template class BSTPoint2<std::int8_t>;
	extern template class BSTPoint2<std::uint8_t>;
	extern template class BSTPoint2<std::int16_t>;
	extern template class BSTPoint2<std::uint16_t>;
	extern template class BSTPoint2<std::int32_t>;
	extern template class BSTPoint2<std::uint32_t>;
	extern template class BSTPoint2<REX::Float32>;
	extern template class BSTPoint2<REX::Float64>;

	template <class T>
	class BSTPoint3Base
	{
	public:
		constexpr BSTPoint3Base() noexcept = default;
		constexpr ~BSTPoint3Base() noexcept = default;

		constexpr BSTPoint3Base(T a_x, T a_y, T a_z)
			: x(a_x), y(a_y), z(a_z)
		{
		}

		constexpr BSTPoint3Base(const BSTPoint3Base&) noexcept = default;
		constexpr BSTPoint3Base(BSTPoint3Base&&) noexcept = default;

		constexpr BSTPoint3Base& operator=(const BSTPoint3Base&) noexcept = default;
		constexpr BSTPoint3Base& operator=(BSTPoint3Base&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const BSTPoint3Base&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const BSTPoint3Base&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const BSTPoint3Base&) const noexcept = default;

		constexpr void swap(BSTPoint3Base& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}

		T x{}; // 00
		T y{}; // ??
		T z{}; // ??
	};

	extern template class BSTPoint3Base<std::int8_t>;
	extern template class BSTPoint3Base<std::uint8_t>;
	extern template class BSTPoint3Base<std::int16_t>;
	extern template class BSTPoint3Base<std::uint16_t>;
	extern template class BSTPoint3Base<std::int32_t>;
	extern template class BSTPoint3Base<std::uint32_t>;
	extern template class BSTPoint3Base<REX::Float32>;
	extern template class BSTPoint3Base<REX::Float64>;

	template <class T>
	constexpr void swap(BSTPoint3Base<T>& a_lhs, BSTPoint3Base<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	extern template void swap(BSTPoint3Base<std::int8_t>&, BSTPoint3Base<std::int8_t>&) noexcept;
	extern template void swap(BSTPoint3Base<std::uint8_t>&, BSTPoint3Base<std::uint8_t>&) noexcept;
	extern template void swap(BSTPoint3Base<std::int16_t>&, BSTPoint3Base<std::int16_t>&) noexcept;
	extern template void swap(BSTPoint3Base<std::uint16_t>&, BSTPoint3Base<std::uint16_t>&) noexcept;
	extern template void swap(BSTPoint3Base<std::int32_t>&, BSTPoint3Base<std::int32_t>&) noexcept;
	extern template void swap(BSTPoint3Base<std::uint32_t>&, BSTPoint3Base<std::uint32_t>&) noexcept;
	extern template void swap(BSTPoint3Base<REX::Float32>&, BSTPoint3Base<REX::Float32>&) noexcept;
	extern template void swap(BSTPoint3Base<REX::Float64>&, BSTPoint3Base<REX::Float64>&) noexcept;

	template <class T, class Ops = BSTPointDefaultOps<T>>
	class BSTPoint3
		: public BSTPoint3Base<T>,
		  public BSTPointDefaultOps<T>
	{
	public:
	};

	extern template class BSTPoint3<std::int8_t>;
	extern template class BSTPoint3<std::uint8_t>;
	extern template class BSTPoint3<std::int16_t>;
	extern template class BSTPoint3<std::uint16_t>;
	extern template class BSTPoint3<std::int32_t>;
	extern template class BSTPoint3<std::uint32_t>;
	extern template class BSTPoint3<REX::Float32>;
	extern template class BSTPoint3<REX::Float64>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T>
	struct formatter<RE::BSTPoint2<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTPoint2<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	template <class T>
	struct formatter<RE::BSTPoint3<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTPoint3<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};

	extern template struct formatter<RE::BSTPoint2<std::int8_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint8_t>>;
	extern template struct formatter<RE::BSTPoint2<std::int16_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint16_t>>;
	extern template struct formatter<RE::BSTPoint2<std::int32_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint32_t>>;
	extern template struct formatter<RE::BSTPoint2<REX::Float32>>;
	extern template struct formatter<RE::BSTPoint2<REX::Float64>>;

	extern template struct formatter<RE::BSTPoint3<std::int8_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint8_t>>;
	extern template struct formatter<RE::BSTPoint3<std::int16_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint16_t>>;
	extern template struct formatter<RE::BSTPoint3<std::int32_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint32_t>>;
	extern template struct formatter<RE::BSTPoint3<REX::Float32>>;
	extern template struct formatter<RE::BSTPoint3<REX::Float64>>;
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T>
	struct formatter<RE::BSTPoint2<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTPoint2<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	template <class T>
	struct formatter<RE::BSTPoint3<T>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTPoint3<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};

	extern template struct formatter<RE::BSTPoint2<std::int8_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint8_t>>;
	extern template struct formatter<RE::BSTPoint2<std::int16_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint16_t>>;
	extern template struct formatter<RE::BSTPoint2<std::int32_t>>;
	extern template struct formatter<RE::BSTPoint2<std::uint32_t>>;
	extern template struct formatter<RE::BSTPoint2<REX::Float32>>;
	extern template struct formatter<RE::BSTPoint2<REX::Float64>>;

	extern template struct formatter<RE::BSTPoint3<std::int8_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint8_t>>;
	extern template struct formatter<RE::BSTPoint3<std::int16_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint16_t>>;
	extern template struct formatter<RE::BSTPoint3<std::int32_t>>;
	extern template struct formatter<RE::BSTPoint3<std::uint32_t>>;
	extern template struct formatter<RE::BSTPoint3<REX::Float32>>;
	extern template struct formatter<RE::BSTPoint3<REX::Float64>>;
}
#endif
