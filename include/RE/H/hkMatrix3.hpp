#pragma once

#include "RE/H/hkVector4.hpp"

namespace RE
{
	class hkMatrix3
	{
	public:
		constexpr hkMatrix3() noexcept = default;

		constexpr hkMatrix3(const hkVector4& a_point0, const hkVector4& a_point1, const hkVector4& a_point2) noexcept
			: rows{ a_point0, a_point1, a_point2 }
		{
		}

		constexpr hkMatrix3(
			REX::Float32 a_x0, REX::Float32 a_y0, REX::Float32 a_z0, REX::Float32 a_w0,
			REX::Float32 a_x1, REX::Float32 a_y1, REX::Float32 a_z1, REX::Float32 a_w1,
			REX::Float32 a_x2, REX::Float32 a_y2, REX::Float32 a_z2, REX::Float32 a_w2) noexcept
			: rows{
				  hkVector4{ a_x0, a_y0, a_z0, a_w0 },
				  hkVector4{ a_x1, a_y1, a_z1, a_w1 },
				  hkVector4{ a_x2, a_y2, a_z2, a_w2 }
			  }
		{
		}

		constexpr ~hkMatrix3() noexcept = default;

		constexpr hkMatrix3(const hkMatrix3&) noexcept = default;
		constexpr hkMatrix3(hkMatrix3&&) noexcept = default;

		constexpr hkMatrix3& operator=(const hkMatrix3&) noexcept = default;
		constexpr hkMatrix3& operator=(hkMatrix3&&) noexcept = default;

		[[nodiscard]] constexpr bool operator==(const hkMatrix3&) const noexcept = default;
		[[nodiscard]] constexpr bool operator!=(const hkMatrix3&) const noexcept = default;
		[[nodiscard]] constexpr auto operator<=>(const hkMatrix3&) const noexcept = default;

		[[nodiscard]] constexpr hkVector4& operator[](std::size_t a_index) noexcept
		{
			REX::Assert(a_index < rows.size());
			return rows[a_index];
		}

		[[nodiscard]] constexpr const hkVector4& operator[](std::size_t a_index) const noexcept
		{
			REX::Assert(a_index < rows.size());
			return rows[a_index];
		}

		[[nodiscard]] constexpr hkMatrix3 Transpose() const noexcept
		{
			return {
				rows[0].x, rows[1].x, rows[2].x, 0.0_f32,
				rows[0].y, rows[1].y, rows[2].y, 0.0_f32,
				rows[0].z, rows[1].z, rows[2].z, 0.0_f32
			};
		}

		// members
		std::array<hkVector4, 3> rows; // 00
	};
	static_assert(sizeof(hkMatrix3) == 0x30);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::hkMatrix3>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::hkMatrix3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}]"sv, a_value[0], a_value[1], a_value[2]);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::hkMatrix3>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::hkMatrix3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}]"sv, a_value[0], a_value[1], a_value[2]);
		}
	};
}
#endif
