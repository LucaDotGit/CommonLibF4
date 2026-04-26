#pragma once

namespace RE
{
	class NiQuaternion
	{
	public:
		constexpr NiQuaternion() noexcept = default;

		constexpr NiQuaternion(REX::Float32 a_w, REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept
			: w(a_w), x(a_x), y(a_y), z(a_z)
		{
		}

		constexpr ~NiQuaternion() noexcept = default;

		constexpr NiQuaternion(const NiQuaternion&) noexcept = default;
		constexpr NiQuaternion(NiQuaternion&&) noexcept = default;

		constexpr NiQuaternion& operator=(const NiQuaternion&) noexcept = default;
		constexpr NiQuaternion& operator=(NiQuaternion&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiQuaternion& rhs) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiQuaternion& rhs) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiQuaternion& rhs) const noexcept = default;

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

		[[nodiscard]] constexpr NiQuaternion operator+(const NiQuaternion& rhs) const noexcept
		{
			return { w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z };
		}

		[[nodiscard]] constexpr NiQuaternion operator-(const NiQuaternion& rhs) const noexcept
		{
			return { w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z };
		}

		[[nodiscard]] constexpr NiQuaternion operator*(const NiQuaternion& rhs) const noexcept
		{
			return {
				(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
				(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
				(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
				(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w)
			};
		}

		[[nodiscard]] constexpr NiQuaternion operator*(REX::Float32 rhs) const noexcept
		{
			return { w * rhs, x * rhs, y * rhs, z * rhs };
		}

		[[nodiscard]] constexpr NiQuaternion operator/(REX::Float32 rhs) const noexcept
		{
			return { w / rhs, x / rhs, y / rhs, z / rhs };
		}

		[[nodiscard]] constexpr NiQuaternion operator-() const noexcept
		{
			return { -w, -x, -y, -z };
		}

		constexpr NiQuaternion& operator+=(const NiQuaternion& rhs) noexcept
		{
			w += rhs.w;
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		constexpr NiQuaternion& operator-=(const NiQuaternion& rhs) noexcept
		{
			w -= rhs.w;
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		constexpr NiQuaternion& operator*=(const NiQuaternion& rhs) noexcept
		{
			*this = *this * rhs;
			return *this;
		}

		constexpr NiQuaternion& operator*=(REX::Float32 rhs) noexcept
		{
			w *= rhs;
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		constexpr NiQuaternion& operator/=(REX::Float32 rhs) noexcept
		{
			w /= rhs;
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		[[nodiscard]] constexpr REX::Float32 Dot() const
		{
			return (w * w) + (x * x) + (y * y) + (z * z);
		}

		[[nodiscard]] constexpr REX::Float32 Dot(const NiQuaternion& q) const
		{
			return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
		}

		constexpr void swap(NiQuaternion& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(w, a_other.w);
			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}

		REX::Float32 w{ 1.0_f32 }; // 00
		REX::Float32 x{ 0.0_f32 }; // 04
		REX::Float32 y{ 0.0_f32 }; // 08
		REX::Float32 z{ 0.0_f32 }; // 0C
	};
	static_assert(sizeof(NiQuaternion) == 0x10);

	constexpr void swap(NiQuaternion& a_lhs, NiQuaternion& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::NiQuaternion>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiQuaternion& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.w, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::NiQuaternion>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiQuaternion& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "({}, {}, {}, {})"sv, a_value.w, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif
