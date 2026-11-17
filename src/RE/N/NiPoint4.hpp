#pragma once

namespace RE
{
	class NiPoint4
	{
	public:
		static const NiPoint4 ZERO;
		static const NiPoint4 IDENTITY0;
		static const NiPoint4 IDENTITY1;
		static const NiPoint4 IDENTITY2;
		static const NiPoint4 IDENTITY3;

		constexpr NiPoint4() noexcept = default;

		constexpr NiPoint4(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_w) noexcept :
			x(a_x),
			y(a_y),
			z(a_z),
			w(a_w)
		{
		}

		constexpr ~NiPoint4() noexcept = default;

		constexpr NiPoint4(const NiPoint4&) noexcept = default;
		constexpr NiPoint4(NiPoint4&&) noexcept = default;

		constexpr auto operator=(const NiPoint4&) noexcept -> NiPoint4& = default;
		constexpr auto operator=(NiPoint4&&) noexcept -> NiPoint4& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiPoint4&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiPoint4&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> REX::Float32&
		{
			REX::Assert(a_index < 4);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const REX::Float32&
		{
			REX::Assert(a_index < 4);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator+(const NiPoint4& a_rhs) const noexcept -> NiPoint4
		{
			return {x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator-(const NiPoint4& a_rhs) const noexcept -> NiPoint4
		{
			return {x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator*(const NiPoint4& a_rhs) const noexcept -> NiPoint4
		{
			return {x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator/(const NiPoint4& a_rhs) const noexcept -> NiPoint4
		{
			return {x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 a_rhs) const noexcept -> NiPoint4
		{
			return {x * a_rhs, y * a_rhs, z * a_rhs, w * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 a_rhs) const noexcept -> NiPoint4
		{
			return {x / a_rhs, y / a_rhs, z / a_rhs, w / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> NiPoint4
		{
			return {-x, -y, -z, -w};
		}

		constexpr auto operator+=(const NiPoint4& a_rhs) noexcept -> NiPoint4&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			w += a_rhs.w;
			return *this;
		}

		constexpr auto operator-=(const NiPoint4& a_rhs) noexcept -> NiPoint4&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			w -= a_rhs.w;
			return *this;
		}

		constexpr auto operator*=(const NiPoint4& a_rhs) noexcept -> NiPoint4&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			w *= a_rhs.w;
			return *this;
		}

		constexpr auto operator/=(const NiPoint4& a_rhs) noexcept -> NiPoint4&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			w /= a_rhs.w;
			return *this;
		}

		constexpr auto operator+=(REX::Float32 a_rhs) noexcept -> NiPoint4&
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			w += a_rhs;
			return *this;
		}

		constexpr auto operator-=(REX::Float32 a_rhs) noexcept -> NiPoint4&
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			w -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 a_rhs) noexcept -> NiPoint4&
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			w *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 a_rhs) noexcept -> NiPoint4&
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			w /= a_rhs;
			return *this;
		}

		constexpr void swap(NiPoint4& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
			std::swap(w, a_other.w);
		}

		// members
		REX::Float32 x{static_cast<REX::Float32>(0.0)}; // 0x00
		REX::Float32 y{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 z{static_cast<REX::Float32>(0.0)}; // 0x08
		REX::Float32 w{static_cast<REX::Float32>(0.0)}; // 0x0C
	};

	static_assert(sizeof(NiPoint4) == 0x10);

	inline constexpr auto NiPoint4::ZERO = NiPoint4();
	inline constexpr auto NiPoint4::IDENTITY0 = NiPoint4(
		static_cast<REX::Float32>(1.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint4::IDENTITY1 = NiPoint4(
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(1.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint4::IDENTITY2 = NiPoint4(
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(1.0),
		static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint4::IDENTITY3 = NiPoint4(
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(0.0),
		static_cast<REX::Float32>(1.0));
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiPoint4> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::NiPoint4> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif
