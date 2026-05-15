#pragma once

namespace RE
{
	class alignas(0x10) hkVector4
	{
	public:
		constexpr hkVector4() noexcept = default;

		constexpr hkVector4(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_w) noexcept
			: x(a_x), y(a_y), z(a_z), w(a_w)
		{
		}

		constexpr ~hkVector4() noexcept = default;

		constexpr hkVector4(const hkVector4&) noexcept = default;
		constexpr hkVector4(hkVector4&&) noexcept = default;

		constexpr hkVector4& operator=(const hkVector4&) noexcept = default;
		constexpr hkVector4& operator=(hkVector4&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const hkVector4&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const hkVector4&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const hkVector4&) const noexcept = default;

		[[nodiscard]] constexpr REX::Float32& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < 4);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr const REX::Float32& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < 4);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr hkVector4 operator+(const hkVector4& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w };
		}

		[[nodiscard]] constexpr hkVector4 operator-(const hkVector4& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w };
		}

		[[nodiscard]] constexpr hkVector4 operator*(const hkVector4& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w };
		}

		[[nodiscard]] constexpr hkVector4 operator/(const hkVector4& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w };
		}

		[[nodiscard]] constexpr hkVector4 operator*(REX::Float32 a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs, z * a_rhs, w * a_rhs };
		}

		[[nodiscard]] constexpr hkVector4 operator/(REX::Float32 a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs, z / a_rhs, w / a_rhs };
		}

		[[nodiscard]] constexpr hkVector4 operator-() const noexcept
		{
			return { -x, -y, -z, -w };
		}

		constexpr hkVector4& operator+=(const hkVector4& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			w += a_rhs.w;
			return *this;
		}

		constexpr hkVector4& operator-=(const hkVector4& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			w -= a_rhs.w;
			return *this;
		}

		constexpr hkVector4& operator*=(const hkVector4& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			w *= a_rhs.w;
			return *this;
		}

		constexpr hkVector4& operator/=(const hkVector4& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			w /= a_rhs.w;
			return *this;
		}

		constexpr hkVector4& operator+=(REX::Float32 a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			w += a_rhs;
			return *this;
		}

		constexpr hkVector4& operator-=(REX::Float32 a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			w -= a_rhs;
			return *this;
		}

		constexpr hkVector4& operator*=(REX::Float32 a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			w *= a_rhs;
			return *this;
		}

		constexpr hkVector4& operator/=(REX::Float32 a_rhs) noexcept
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			w /= a_rhs;
			return *this;
		}

		constexpr void swap(hkVector4& a_other) noexcept
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
		REX::Float32 x; // 00
		REX::Float32 y; // 04
		REX::Float32 z; // 08
		REX::Float32 w; // 0C
	};
	static_assert(sizeof(hkVector4) == 0x10);

	constexpr void swap(hkVector4& a_lhs, hkVector4& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::hkVector4>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::hkVector4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::hkVector4>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::hkVector4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif
