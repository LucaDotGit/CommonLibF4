#pragma once

namespace RE
{
	class hkQuaternionf
	{
	public:
		constexpr hkQuaternionf() noexcept = default;

		constexpr hkQuaternionf(REX::Float32 a_w, REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept :
			w(a_w),
			x(a_x),
			y(a_y),
			z(a_z)
		{
		}

		constexpr ~hkQuaternionf() noexcept = default;

		constexpr hkQuaternionf(const hkQuaternionf&) noexcept = default;
		constexpr hkQuaternionf(hkQuaternionf&&) noexcept = default;

		constexpr auto operator=(const hkQuaternionf&) noexcept -> hkQuaternionf& = default;
		constexpr auto operator=(hkQuaternionf&&) noexcept -> hkQuaternionf& = default;

		[[nodiscard]]
		constexpr auto operator==(const hkQuaternionf& rhs) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const hkQuaternionf& rhs) const noexcept = default;

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
		constexpr auto operator+(const hkQuaternionf& rhs) const noexcept -> hkQuaternionf
		{
			return {w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator-(const hkQuaternionf& rhs) const noexcept -> hkQuaternionf
		{
			return {w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator*(const hkQuaternionf& rhs) const noexcept -> hkQuaternionf
		{
			return {
				(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
				(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
				(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
				(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w)
			};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 rhs) const noexcept -> hkQuaternionf
		{
			return {w * rhs, x * rhs, y * rhs, z * rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 rhs) const noexcept -> hkQuaternionf
		{
			return {w / rhs, x / rhs, y / rhs, z / rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> hkQuaternionf
		{
			return {-w, -x, -y, -z};
		}

		constexpr auto operator+=(const hkQuaternionf& rhs) noexcept -> hkQuaternionf&
		{
			w += rhs.w;
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		constexpr auto operator-=(const hkQuaternionf& rhs) noexcept -> hkQuaternionf&
		{
			w -= rhs.w;
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		constexpr auto operator*=(const hkQuaternionf& rhs) noexcept -> hkQuaternionf&
		{
			*this = *this * rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 rhs) noexcept -> hkQuaternionf&
		{
			w *= rhs;
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 rhs) noexcept -> hkQuaternionf&
		{
			w /= rhs;
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		[[nodiscard]]
		constexpr auto Dot() const -> REX::Float32
		{
			return (w * w) + (x * x) + (y * y) + (z * z);
		}

		[[nodiscard]]
		constexpr auto Dot(const hkQuaternionf& q) const -> REX::Float32
		{
			return (w * q.w) + (x * q.x) + (y * q.y) + (z * q.z);
		}

		constexpr void swap(hkQuaternionf& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(w, a_other.w);
			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}

		REX::Float32 w{static_cast<REX::Float32>(1.0)}; // 0x00
		REX::Float32 x{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 y{static_cast<REX::Float32>(0.0)}; // 0x08
		REX::Float32 z{static_cast<REX::Float32>(0.0)}; // 0x0C
	};

	static_assert(sizeof(hkQuaternionf) == 0x10);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::hkQuaternionf> : public formatter<std::string>
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
		constexpr auto format(const RE::hkQuaternionf& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.w, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::hkQuaternionf> : public formatter<std::string>
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
		constexpr auto format(const RE::hkQuaternionf& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.w, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif
