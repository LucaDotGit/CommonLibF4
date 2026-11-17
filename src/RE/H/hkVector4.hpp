#pragma once

namespace RE
{
	class alignas(0x10) hkVector4
	{
	public:
		constexpr hkVector4() noexcept = default;

		constexpr hkVector4(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_w) noexcept :
			x(a_x),
			y(a_y),
			z(a_z),
			w(a_w)
		{
		}

		constexpr ~hkVector4() noexcept = default;

		constexpr hkVector4(const hkVector4&) noexcept = default;
		constexpr hkVector4(hkVector4&&) noexcept = default;

		constexpr auto operator=(const hkVector4&) noexcept -> hkVector4& = default;
		constexpr auto operator=(hkVector4&&) noexcept -> hkVector4& = default;

		[[nodiscard]]
		constexpr auto operator==(const hkVector4&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const hkVector4&) const noexcept = default;

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
		constexpr auto operator+(const hkVector4& a_rhs) const noexcept -> hkVector4
		{
			return {x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator-(const hkVector4& a_rhs) const noexcept -> hkVector4
		{
			return {x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator*(const hkVector4& a_rhs) const noexcept -> hkVector4
		{
			return {x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator/(const hkVector4& a_rhs) const noexcept -> hkVector4
		{
			return {x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 a_rhs) const noexcept -> hkVector4
		{
			return {x * a_rhs, y * a_rhs, z * a_rhs, w * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 a_rhs) const noexcept -> hkVector4
		{
			return {x / a_rhs, y / a_rhs, z / a_rhs, w / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> hkVector4
		{
			return {-x, -y, -z, -w};
		}

		constexpr auto operator+=(const hkVector4& a_rhs) noexcept -> hkVector4&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			w += a_rhs.w;
			return *this;
		}

		constexpr auto operator-=(const hkVector4& a_rhs) noexcept -> hkVector4&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			w -= a_rhs.w;
			return *this;
		}

		constexpr auto operator*=(const hkVector4& a_rhs) noexcept -> hkVector4&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			w *= a_rhs.w;
			return *this;
		}

		constexpr auto operator/=(const hkVector4& a_rhs) noexcept -> hkVector4&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			w /= a_rhs.w;
			return *this;
		}

		constexpr auto operator+=(REX::Float32 a_rhs) noexcept -> hkVector4&
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			w += a_rhs;
			return *this;
		}

		constexpr auto operator-=(REX::Float32 a_rhs) noexcept -> hkVector4&
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			w -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 a_rhs) noexcept -> hkVector4&
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			w *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 a_rhs) noexcept -> hkVector4&
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
		REX::Float32 x; // 0x00
		REX::Float32 y; // 0x04
		REX::Float32 z; // 0x08
		REX::Float32 w; // 0x0C
	};

	static_assert(sizeof(hkVector4) == 0x10);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::hkVector4> : public formatter<std::string>
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
		constexpr auto format(const RE::hkVector4& a_value, FormatContext& a_context) const
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
	struct formatter<RE::hkVector4> : public formatter<std::string>
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
		constexpr auto format(const RE::hkVector4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif
