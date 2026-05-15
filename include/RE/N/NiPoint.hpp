#pragma once

namespace RE
{
	class NiPoint2
	{
	public:
		static const NiPoint2 ZERO;
		static const NiPoint2 UNIT;
		static const NiPoint2 UNIT_X;
		static const NiPoint2 UNIT_Y;

		constexpr NiPoint2() noexcept = default;

		constexpr NiPoint2(REX::Float32 a_x, REX::Float32 a_y) noexcept
			: x(a_x), y(a_y)
		{
		}

		constexpr ~NiPoint2() noexcept = default;

		constexpr NiPoint2(const NiPoint2&) noexcept = default;
		constexpr NiPoint2(NiPoint2&&) noexcept = default;

		constexpr NiPoint2& operator=(const NiPoint2&) noexcept = default;
		constexpr NiPoint2& operator=(NiPoint2&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiPoint2&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiPoint2&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiPoint2&) const noexcept = default;

		[[nodiscard]] constexpr REX::Float32& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr const REX::Float32& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < 2);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr NiPoint2 operator+(const NiPoint2& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y };
		}

		[[nodiscard]] constexpr NiPoint2 operator-(const NiPoint2& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y };
		}

		[[nodiscard]] constexpr NiPoint2 operator*(const NiPoint2& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y };
		}

		[[nodiscard]] constexpr NiPoint2 operator/(const NiPoint2& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y };
		}

		[[nodiscard]] constexpr NiPoint2 operator*(REX::Float32 a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs };
		}

		[[nodiscard]] constexpr NiPoint2 operator/(REX::Float32 a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs };
		}

		[[nodiscard]] constexpr NiPoint2 operator-() const noexcept
		{
			return { -x, -y };
		}

		constexpr NiPoint2& operator+=(const NiPoint2& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			return *this;
		}

		constexpr NiPoint2& operator-=(const NiPoint2& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			return *this;
		}

		constexpr NiPoint2& operator*=(const NiPoint2& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			return *this;
		}

		constexpr NiPoint2& operator/=(const NiPoint2& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			return *this;
		}

		constexpr NiPoint2& operator+=(REX::Float32 a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			return *this;
		}

		constexpr NiPoint2& operator-=(REX::Float32 a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			return *this;
		}

		constexpr NiPoint2& operator*=(REX::Float32 a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			return *this;
		}

		constexpr NiPoint2& operator/=(REX::Float32 a_rhs) noexcept
		{
			x /= a_rhs;
			y /= a_rhs;
			return *this;
		}

		constexpr void swap(NiPoint2& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(x, a_other.x);
			std::swap(y, a_other.y);
		}

		// members
		REX::Float32 x{ 0.0_f32 }; // 00
		REX::Float32 y{ 0.0_f32 }; // 04
	};
	static_assert(sizeof(NiPoint2) == 0x08);

	inline constexpr auto NiPoint2::ZERO = NiPoint2();
	inline constexpr auto NiPoint2::UNIT = NiPoint2(1.0_f32, 1.0_f32);
	inline constexpr auto NiPoint2::UNIT_X = NiPoint2(1.0_f32, 0.0_f32);
	inline constexpr auto NiPoint2::UNIT_Y = NiPoint2(0.0_f32, 1.0_f32);

	constexpr void swap(NiPoint2& a_lhs, NiPoint2& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

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

		constexpr NiPoint3(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept
			: x(a_x), y(a_y), z(a_z)
		{
		}

		constexpr ~NiPoint3() noexcept = default;

		constexpr NiPoint3(const NiPoint3&) noexcept = default;
		constexpr NiPoint3(NiPoint3&&) noexcept = default;

		constexpr NiPoint3& operator=(const NiPoint3&) noexcept = default;
		constexpr NiPoint3& operator=(NiPoint3&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiPoint3&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiPoint3&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiPoint3&) const noexcept = default;

		[[nodiscard]] constexpr REX::Float32& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < 3);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr const REX::Float32& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < 3);
			return std::addressof(x)[a_index];
		}

		[[nodiscard]] constexpr NiPoint3 operator+(const NiPoint3& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3 operator-(const NiPoint3& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3 operator*(const NiPoint3& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3 operator/(const NiPoint3& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y, z / a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3 operator*(REX::Float32 a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs, z * a_rhs };
		}

		[[nodiscard]] constexpr NiPoint3 operator/(REX::Float32 a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs, z / a_rhs };
		}

		[[nodiscard]] constexpr NiPoint3 operator-() const noexcept
		{
			return { -x, -y, -z };
		}

		constexpr NiPoint3& operator+=(const NiPoint3& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			return *this;
		}

		constexpr NiPoint3& operator-=(const NiPoint3& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3& operator*=(const NiPoint3& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3& operator/=(const NiPoint3& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3& operator+=(REX::Float32 a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			return *this;
		}

		constexpr NiPoint3& operator-=(REX::Float32 a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			return *this;
		}

		constexpr NiPoint3& operator*=(REX::Float32 a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			return *this;
		}

		constexpr NiPoint3& operator/=(REX::Float32 a_rhs) noexcept
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			return *this;
		}

		[[nodiscard]] constexpr NiPoint3 Cross(const NiPoint3& a_rhs) const noexcept
		{
			return {
				(y * a_rhs.z) - (z * a_rhs.y),
				(z * a_rhs.x) - (x * a_rhs.z),
				(x * a_rhs.y) - (y * a_rhs.x)
			};
		}

		[[nodiscard]] constexpr REX::Float32 Dot(const NiPoint3& a_rhs) const noexcept
		{
			return (x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z);
		}

		[[nodiscard]] constexpr REX::Float32 LengthSquared() const noexcept
		{
			return (x * x) + (y * y) + (z * z);
		}

		[[nodiscard]] REX::Float32 Length() const noexcept
		{
			return std::sqrt(LengthSquared());
		}

		[[nodiscard]] constexpr REX::Float32 DistanceSquared(const NiPoint3& a_rhs) const noexcept
		{
			const auto dx = x - a_rhs.x;
			const auto dy = y - a_rhs.y;
			const auto dz = z - a_rhs.z;
			return (dx * dx) + (dy * dy) + (dz * dz);
		}

		[[nodiscard]] REX::Float32 Distance(const NiPoint3& a_rhs) const noexcept
		{
			return std::sqrt(DistanceSquared(a_rhs));
		}

		[[nodiscard]] REX::Float32 Unitize() noexcept
		{
			const auto length = Length();
			if (length == 1.0_f32) {
				return 1.0_f32;
			}

			if (length <= std::numeric_limits<REX::Float32>::epsilon()) {
				operator=(NiPoint3::ZERO);
				return 0.0_f32;
			}

			operator/=(length);
			return length;
		}

		[[nodiscard]] REX::Float32 ZAngle() const noexcept
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
		REX::Float32 x{ 0.0_f32 }; // 00
		REX::Float32 y{ 0.0_f32 }; // 04
		REX::Float32 z{ 0.0_f32 }; // 08
	};
	static_assert(sizeof(NiPoint3) == 0x0C);

	inline constexpr auto NiPoint3::ZERO = NiPoint3();
	inline constexpr auto NiPoint3::UNIT = NiPoint3(1.0_f32, 1.0_f32, 1.0_f32);
	inline constexpr auto NiPoint3::UNIT_X = NiPoint3(1.0_f32, 0.0_f32, 0.0_f32);
	inline constexpr auto NiPoint3::UNIT_Y = NiPoint3(0.0_f32, 1.0_f32, 0.0_f32);
	inline constexpr auto NiPoint3::UNIT_Z = NiPoint3(0.0_f32, 0.0_f32, 1.0_f32);

	constexpr void swap(NiPoint3& a_lhs, NiPoint3& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace RE
{
	class alignas(0x10) NiPoint3A
		: public NiPoint3 // 00
	{
	public:
		static const NiPoint3A ZERO;
		static const NiPoint3A UNIT;
		static const NiPoint3A UNIT_X;
		static const NiPoint3A UNIT_Y;
		static const NiPoint3A UNIT_Z;

		constexpr NiPoint3A() noexcept = default;

		constexpr NiPoint3A(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept
			: NiPoint3(a_x, a_y, a_z)
		{
		}

		constexpr ~NiPoint3A() noexcept = default;

		constexpr NiPoint3A(const NiPoint3A&) noexcept = default;
		constexpr NiPoint3A(NiPoint3A&&) noexcept = default;

		constexpr NiPoint3A& operator=(const NiPoint3A&) noexcept = default;
		constexpr NiPoint3A& operator=(NiPoint3A&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiPoint3A&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiPoint3A&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiPoint3A&) const noexcept = default;

		[[nodiscard]] constexpr NiPoint3A operator+(const NiPoint3A& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3A operator-(const NiPoint3A& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3A operator*(const NiPoint3A& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3A operator/(const NiPoint3A& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y, z / a_rhs.z };
		}

		[[nodiscard]] constexpr NiPoint3A operator*(REX::Float32 a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs, z * a_rhs };
		}

		[[nodiscard]] constexpr NiPoint3A operator/(REX::Float32 a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs, z / a_rhs };
		}

		[[nodiscard]] constexpr NiPoint3A operator-() const noexcept
		{
			return { -x, -y, -z };
		}

		constexpr NiPoint3A& operator+=(const NiPoint3A& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			return *this;
		}

		constexpr NiPoint3A& operator-=(const NiPoint3A& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3A& operator*=(const NiPoint3A& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3A& operator/=(const NiPoint3A& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			return *this;
		}

		constexpr NiPoint3A& operator+=(REX::Float32 a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			return *this;
		}

		constexpr NiPoint3A& operator-=(REX::Float32 a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			return *this;
		}

		constexpr NiPoint3A& operator*=(REX::Float32 a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			return *this;
		}

		constexpr NiPoint3A& operator/=(REX::Float32 a_rhs) noexcept
		{
			x /= a_rhs;
			y /= a_rhs;
			z /= a_rhs;
			return *this;
		}

		[[nodiscard]] constexpr NiPoint3A Cross(const NiPoint3A& a_rhs) const noexcept
		{
			return {
				(y * a_rhs.z) - (z * a_rhs.y),
				(z * a_rhs.x) - (x * a_rhs.z),
				(x * a_rhs.y) - (y * a_rhs.x)
			};
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
	inline constexpr auto NiPoint3A::UNIT = NiPoint3A(1.0_f32, 1.0_f32, 1.0_f32);
	inline constexpr auto NiPoint3A::UNIT_X = NiPoint3A(1.0_f32, 0.0_f32, 0.0_f32);
	inline constexpr auto NiPoint3A::UNIT_Y = NiPoint3A(0.0_f32, 1.0_f32, 0.0_f32);
	inline constexpr auto NiPoint3A::UNIT_Z = NiPoint3A(0.0_f32, 0.0_f32, 1.0_f32);

	constexpr void swap(NiPoint3A& a_lhs, NiPoint3A& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

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

		constexpr NiPoint4(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_w) noexcept
			: x(a_x), y(a_y), z(a_z), w(a_w)
		{
		}

		constexpr ~NiPoint4() noexcept = default;

		constexpr NiPoint4(const NiPoint4&) noexcept = default;
		constexpr NiPoint4(NiPoint4&&) noexcept = default;

		constexpr NiPoint4& operator=(const NiPoint4&) noexcept = default;
		constexpr NiPoint4& operator=(NiPoint4&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const NiPoint4&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const NiPoint4&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const NiPoint4&) const noexcept = default;

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

		[[nodiscard]] constexpr NiPoint4 operator+(const NiPoint4& a_rhs) const noexcept
		{
			return { x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w };
		}

		[[nodiscard]] constexpr NiPoint4 operator-(const NiPoint4& a_rhs) const noexcept
		{
			return { x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w };
		}

		[[nodiscard]] constexpr NiPoint4 operator*(const NiPoint4& a_rhs) const noexcept
		{
			return { x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w };
		}

		[[nodiscard]] constexpr NiPoint4 operator/(const NiPoint4& a_rhs) const noexcept
		{
			return { x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w };
		}

		[[nodiscard]] constexpr NiPoint4 operator*(REX::Float32 a_rhs) const noexcept
		{
			return { x * a_rhs, y * a_rhs, z * a_rhs, w * a_rhs };
		}

		[[nodiscard]] constexpr NiPoint4 operator/(REX::Float32 a_rhs) const noexcept
		{
			return { x / a_rhs, y / a_rhs, z / a_rhs, w / a_rhs };
		}

		[[nodiscard]] constexpr NiPoint4 operator-() const noexcept
		{
			return { -x, -y, -z, -w };
		}

		constexpr NiPoint4& operator+=(const NiPoint4& a_rhs) noexcept
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			w += a_rhs.w;
			return *this;
		}

		constexpr NiPoint4& operator-=(const NiPoint4& a_rhs) noexcept
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			w -= a_rhs.w;
			return *this;
		}

		constexpr NiPoint4& operator*=(const NiPoint4& a_rhs) noexcept
		{
			x *= a_rhs.x;
			y *= a_rhs.y;
			z *= a_rhs.z;
			w *= a_rhs.w;
			return *this;
		}

		constexpr NiPoint4& operator/=(const NiPoint4& a_rhs) noexcept
		{
			x /= a_rhs.x;
			y /= a_rhs.y;
			z /= a_rhs.z;
			w /= a_rhs.w;
			return *this;
		}

		constexpr NiPoint4& operator+=(REX::Float32 a_rhs) noexcept
		{
			x += a_rhs;
			y += a_rhs;
			z += a_rhs;
			w += a_rhs;
			return *this;
		}

		constexpr NiPoint4& operator-=(REX::Float32 a_rhs) noexcept
		{
			x -= a_rhs;
			y -= a_rhs;
			z -= a_rhs;
			w -= a_rhs;
			return *this;
		}

		constexpr NiPoint4& operator*=(REX::Float32 a_rhs) noexcept
		{
			x *= a_rhs;
			y *= a_rhs;
			z *= a_rhs;
			w *= a_rhs;
			return *this;
		}

		constexpr NiPoint4& operator/=(REX::Float32 a_rhs) noexcept
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
		REX::Float32 x{ 0.0_f32 }; // 00
		REX::Float32 y{ 0.0_f32 }; // 04
		REX::Float32 z{ 0.0_f32 }; // 08
		REX::Float32 w{ 0.0_f32 }; // 0C
	};
	static_assert(sizeof(NiPoint4) == 0x10);

	inline constexpr auto NiPoint4::ZERO = NiPoint4();
	inline constexpr auto NiPoint4::IDENTITY0 = NiPoint4(1.0_f32, 0.0_f32, 0.0_f32, 0.0_f32);
	inline constexpr auto NiPoint4::IDENTITY1 = NiPoint4(0.0_f32, 1.0_f32, 0.0_f32, 0.0_f32);
	inline constexpr auto NiPoint4::IDENTITY2 = NiPoint4(0.0_f32, 0.0_f32, 1.0_f32, 0.0_f32);
	inline constexpr auto NiPoint4::IDENTITY3 = NiPoint4(0.0_f32, 0.0_f32, 0.0_f32, 1.0_f32);

	constexpr void swap(NiPoint4& a_lhs, NiPoint4& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::NiPoint2>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint2& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	template <>
	struct formatter<RE::NiPoint3>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};

	template <>
	struct formatter<RE::NiPoint4>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint4& a_value, FormatContext& a_context) const
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
	struct formatter<RE::NiPoint2>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint2& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.x, a_value.y);
		}
	};

	template <>
	struct formatter<RE::NiPoint3>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {})"sv, a_value.x, a_value.y, a_value.z);
		}
	};

	template <>
	struct formatter<RE::NiPoint4>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::NiPoint4& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {}, {}, {})"sv, a_value.x, a_value.y, a_value.z, a_value.w);
		}
	};
}
#endif
