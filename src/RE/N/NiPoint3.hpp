#pragma once

namespace RE
{
	class NiPoint3
	{
	public:
		static const NiPoint3 ZERO;
		static const NiPoint3 UNIT;
		static const NiPoint3 UNIT_X;
		static const NiPoint3 UNIT_Y;
		static const NiPoint3 UNIT_Z;

		constexpr NiPoint3() noexcept = default;

		constexpr NiPoint3(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept :
			x(a_x),
			y(a_y),
			z(a_z)
		{
		}

		constexpr ~NiPoint3() noexcept = default;

		constexpr NiPoint3(const NiPoint3&) noexcept = default;
		constexpr NiPoint3(NiPoint3&&) noexcept = default;

		constexpr auto operator=(const NiPoint3&) noexcept -> NiPoint3& = default;
		constexpr auto operator=(NiPoint3&&) noexcept -> NiPoint3& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiPoint3&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiPoint3&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> REX::Float32&
		{
			REX::Assert(a_index < 3);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const REX::Float32&
		{
			REX::Assert(a_index < 3);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]]
		constexpr auto operator+(const NiPoint3& a_rhs) const noexcept -> NiPoint3
		{
			return {x + a_rhs.x, y + a_rhs.y, z + a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator-(const NiPoint3& a_rhs) const noexcept -> NiPoint3
		{
			return {x - a_rhs.x, y - a_rhs.y, z - a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator*(const NiPoint3& a_rhs) const noexcept -> NiPoint3
		{
			return {x * a_rhs.x, y * a_rhs.y, z * a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator/(const NiPoint3& a_rhs) const noexcept -> NiPoint3
		{
			return {x / a_rhs.x, y / a_rhs.y, z / a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 a_rhs) const noexcept -> NiPoint3
		{
			return {x * a_rhs, y * a_rhs, z * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 a_rhs) const noexcept -> NiPoint3
		{
			return {x / a_rhs, y / a_rhs, z / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> NiPoint3
		{
			return {-x, -y, -z};
		}

		constexpr auto operator+=(const NiPoint3& a_rhs) noexcept -> NiPoint3&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			return *this;
		}

		constexpr auto operator-=(const NiPoint3& a_rhs) noexcept -> NiPoint3&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			return *this;
		}

		constexpr auto operator*=(const NiPoint3& a_rhs) noexcept -> NiPoint3&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			return *this;
		}

		constexpr auto operator/=(const NiPoint3& a_rhs) noexcept -> NiPoint3&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			return *this;
		}

		constexpr auto operator+=(REX::Float32 a_rhs) noexcept -> NiPoint3&
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			return *this;
		}

		constexpr auto operator-=(REX::Float32 a_rhs) noexcept -> NiPoint3&
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 a_rhs) noexcept -> NiPoint3&
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 a_rhs) noexcept -> NiPoint3&
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			return *this;
		}

		[[nodiscard]]
		constexpr auto Cross(const NiPoint3& a_rhs) const noexcept -> NiPoint3
		{
			return {(y * a_rhs.z) - (z * a_rhs.y), (z * a_rhs.x) - (x * a_rhs.z), (x * a_rhs.y) - (y * a_rhs.x)};
		}

		[[nodiscard]]
		constexpr auto Dot(const NiPoint3& a_rhs) const noexcept -> REX::Float32
		{
			return (x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z);
		}

		[[nodiscard]]
		constexpr auto LengthSquared() const noexcept -> REX::Float32
		{
			return (x * x) + (y * y) + (z * z);
		}

		[[nodiscard]]
		auto Length() const noexcept -> REX::Float32
		{
			return std::sqrt(LengthSquared());
		}

		[[nodiscard]]
		constexpr auto DistanceSquared(const NiPoint3& a_rhs) const noexcept -> REX::Float32
		{
			const auto dx = x - a_rhs.x;
			const auto dy = y - a_rhs.y;
			const auto dz = z - a_rhs.z;
			return (dx * dx) + (dy * dy) + (dz * dz);
		}

		[[nodiscard]]
		auto Distance(const NiPoint3& a_rhs) const noexcept -> REX::Float32
		{
			return std::sqrt(DistanceSquared(a_rhs));
		}

		[[nodiscard]]
		auto Unitize() noexcept -> REX::Float32
		{
			const auto length = Length();
			if (length == static_cast<REX::Float32>(1.0)) {
				return static_cast<REX::Float32>(1.0);
			}

			if (length <= std::numeric_limits<REX::Float32>::epsilon()) {
				operator=(NiPoint3::ZERO);
				return static_cast<REX::Float32>(0.0);
			}

			operator/=(length);
			return length;
		}

		[[nodiscard]]
		auto ZAngle() const noexcept -> REX::Float32
		{
			return std::atan2(y, x);
		}

		constexpr void swap(NiPoint3& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}

		// members
		REX::Float32 x{static_cast<REX::Float32>(0.0)}; // 0x00
		REX::Float32 y{static_cast<REX::Float32>(0.0)}; // 0x04
		REX::Float32 z{static_cast<REX::Float32>(0.0)}; // 0x08
	};

	static_assert(sizeof(NiPoint3) == 0x0C);

	inline constexpr auto NiPoint3::ZERO = NiPoint3();
	inline constexpr auto NiPoint3::UNIT =
		NiPoint3(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0));
	inline constexpr auto NiPoint3::UNIT_X =
		NiPoint3(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint3::UNIT_Y =
		NiPoint3(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint3::UNIT_Z =
		NiPoint3(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0));
}

namespace RE
{
	class alignas(0x10) NiPoint3A : public NiPoint3 // 0x00
	{
	public:
		static const NiPoint3A ZERO;
		static const NiPoint3A UNIT;
		static const NiPoint3A UNIT_X;
		static const NiPoint3A UNIT_Y;
		static const NiPoint3A UNIT_Z;

		constexpr NiPoint3A() noexcept = default;

		constexpr NiPoint3A(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept :
			NiPoint3(a_x, a_y, a_z)
		{
		}

		constexpr ~NiPoint3A() noexcept = default;

		constexpr NiPoint3A(const NiPoint3A&) noexcept = default;
		constexpr NiPoint3A(NiPoint3A&&) noexcept = default;

		constexpr auto operator=(const NiPoint3A&) noexcept -> NiPoint3A& = default;
		constexpr auto operator=(NiPoint3A&&) noexcept -> NiPoint3A& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiPoint3A&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiPoint3A&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator+(const NiPoint3A& a_rhs) const noexcept -> NiPoint3A
		{
			return {x + a_rhs.x, y + a_rhs.y, z + a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator-(const NiPoint3A& a_rhs) const noexcept -> NiPoint3A
		{
			return {x - a_rhs.x, y - a_rhs.y, z - a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator*(const NiPoint3A& a_rhs) const noexcept -> NiPoint3A
		{
			return {x * a_rhs.x, y * a_rhs.y, z * a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator/(const NiPoint3A& a_rhs) const noexcept -> NiPoint3A
		{
			return {x / a_rhs.x, y / a_rhs.y, z / a_rhs.z};
		}

		[[nodiscard]]
		constexpr auto operator*(REX::Float32 a_rhs) const noexcept -> NiPoint3A
		{
			return {x * a_rhs, y * a_rhs, z * a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator/(REX::Float32 a_rhs) const noexcept -> NiPoint3A
		{
			return {x / a_rhs, y / a_rhs, z / a_rhs};
		}

		[[nodiscard]]
		constexpr auto operator-() const noexcept -> NiPoint3A
		{
			return {-x, -y, -z};
		}

		constexpr auto operator+=(const NiPoint3A& a_rhs) noexcept -> NiPoint3A&
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			return *this;
		}

		constexpr auto operator-=(const NiPoint3A& a_rhs) noexcept -> NiPoint3A&
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			return *this;
		}

		constexpr auto operator*=(const NiPoint3A& a_rhs) noexcept -> NiPoint3A&
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			return *this;
		}

		constexpr auto operator/=(const NiPoint3A& a_rhs) noexcept -> NiPoint3A&
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			return *this;
		}

		constexpr auto operator+=(REX::Float32 a_rhs) noexcept -> NiPoint3A&
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			return *this;
		}

		constexpr auto operator-=(REX::Float32 a_rhs) noexcept -> NiPoint3A&
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			return *this;
		}

		constexpr auto operator*=(REX::Float32 a_rhs) noexcept -> NiPoint3A&
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			return *this;
		}

		constexpr auto operator/=(REX::Float32 a_rhs) noexcept -> NiPoint3A&
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			return *this;
		}

		[[nodiscard]]
		constexpr auto Cross(const NiPoint3A& a_rhs) const noexcept -> NiPoint3A
		{
			return {(y * a_rhs.z) - (z * a_rhs.y), (z * a_rhs.x) - (x * a_rhs.z), (x * a_rhs.y) - (y * a_rhs.x)};
		}

		constexpr void swap(NiPoint3A& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
			std::swap(z, a_other.z);
		}
	};

	static_assert(sizeof(NiPoint3A) == 0x10);

	inline constexpr auto NiPoint3A::ZERO = NiPoint3A();
	inline constexpr auto NiPoint3A::UNIT =
		NiPoint3A(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0));
	inline constexpr auto NiPoint3A::UNIT_X =
		NiPoint3A(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint3A::UNIT_Y =
		NiPoint3A(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0));
	inline constexpr auto NiPoint3A::UNIT_Z =
		NiPoint3A(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0));
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiPoint3> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint3& a_value, FormatContext& a_context) const
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
	template <>
	struct formatter<RE::NiPoint3> : public formatter<std::string>
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
		constexpr auto format(const RE::NiPoint3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};
}
#endif
