#pragma once

#include "RE/N/NiPoint4.hpp"

namespace RE
{
	class NiPoint3;

	class alignas(0x10) NiMatrix3
	{
	public:
		static const NiMatrix3 ZERO;
		static const NiMatrix3 IDENTITY;

		constexpr NiMatrix3() noexcept = default;

		constexpr NiMatrix3(const NiPoint4& a_point0, const NiPoint4& a_point1, const NiPoint4& a_point2) noexcept :
			rows{a_point0, a_point1, a_point2}
		{
		}

		constexpr NiMatrix3(
			REX::Float32 a_x0,
			REX::Float32 a_y0,
			REX::Float32 a_z0,
			REX::Float32 a_w0,
			REX::Float32 a_x1,
			REX::Float32 a_y1,
			REX::Float32 a_z1,
			REX::Float32 a_w1,
			REX::Float32 a_x2,
			REX::Float32 a_y2,
			REX::Float32 a_z2,
			REX::Float32 a_w2) noexcept :
			rows{NiPoint4{a_x0, a_y0, a_z0, a_w0}, NiPoint4{a_x1, a_y1, a_z1, a_w1}, NiPoint4{a_x2, a_y2, a_z2, a_w2}}
		{
		}

		constexpr ~NiMatrix3() noexcept = default;

		constexpr NiMatrix3(const NiMatrix3&) noexcept = default;
		constexpr NiMatrix3(NiMatrix3&&) noexcept = default;

		constexpr auto operator=(const NiMatrix3&) noexcept -> NiMatrix3& = default;
		constexpr auto operator=(NiMatrix3&&) noexcept -> NiMatrix3& = default;

		[[nodiscard]]
		constexpr auto operator==(const NiMatrix3&) const noexcept -> bool = default;
		[[nodiscard]]
		constexpr auto operator<=>(const NiMatrix3&) const noexcept = default;

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) noexcept -> NiPoint4&
		{
			REX::Assert(a_index < rows.size());
			return rows[a_index];
		}

		[[nodiscard]]
		constexpr auto operator[](std::size_t a_index) const noexcept -> const NiPoint4&
		{
			REX::Assert(a_index < rows.size());
			return rows[a_index];
		}

		[[nodiscard]]
		constexpr auto Transpose() const noexcept -> NiMatrix3
		{
			return {
				rows[0].x,
				rows[1].x,
				rows[2].x,
				static_cast<REX::Float32>(0.0),
				rows[0].y,
				rows[1].y,
				rows[2].y,
				static_cast<REX::Float32>(0.0),
				rows[0].z,
				rows[1].z,
				rows[2].z,
				static_cast<REX::Float32>(0.0)
			};
		}

		auto ToEulerAnglesXYZ(NiPoint3& a_point) const noexcept -> bool;
		auto ToEulerAnglesXYZ(REX::Float32& a_x, REX::Float32& a_y, REX::Float32& a_z) const noexcept -> bool;
		auto ToEulerAnglesXZY(REX::Float32& a_x, REX::Float32& a_z, REX::Float32& a_y) const noexcept -> bool;
		auto ToEulerAnglesYXZ(REX::Float32& a_y, REX::Float32& a_x, REX::Float32& a_z) const noexcept -> bool;
		auto ToEulerAnglesYZX(REX::Float32& a_y, REX::Float32& a_z, REX::Float32& a_x) const noexcept -> bool;
		auto ToEulerAnglesZYX(REX::Float32& a_z, REX::Float32& a_y, REX::Float32& a_x) const noexcept -> bool;
		auto ToEulerAnglesZXY(REX::Float32& a_z, REX::Float32& a_x, REX::Float32& a_y) const noexcept -> bool;

		void FromEulerAnglesXYZ(const NiPoint3& a_point) noexcept;
		void FromEulerAnglesXYZ(REX::Float32 a_x, REX::Float32 a_y, REX::Float32 a_z) noexcept;
		void FromEulerAnglesXZY(REX::Float32 a_x, REX::Float32 a_z, REX::Float32 a_y) noexcept;
		void FromEulerAnglesYXZ(REX::Float32 a_y, REX::Float32 a_x, REX::Float32 a_z) noexcept;
		void FromEulerAnglesYZX(REX::Float32 a_y, REX::Float32 a_z, REX::Float32 a_x) noexcept;
		void FromEulerAnglesZYX(REX::Float32 a_z, REX::Float32 a_y, REX::Float32 a_x) noexcept;
		void FromEulerAnglesZXY(REX::Float32 a_z, REX::Float32 a_x, REX::Float32 a_y) noexcept;

		// members
		std::array<NiPoint4, 3> rows; // 0x00
	};

	static_assert(sizeof(NiMatrix3) == 0x30);

	inline constexpr auto NiMatrix3::ZERO = NiMatrix3();
	inline constexpr auto NiMatrix3::IDENTITY =
		NiMatrix3(NiPoint4::IDENTITY0, NiPoint4::IDENTITY1, NiPoint4::IDENTITY2);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::NiMatrix3> : public formatter<std::string>
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
		constexpr auto format(const RE::NiMatrix3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}]"sv, a_value[0], a_value[1], a_value[2]);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::NiMatrix3> : public formatter<std::string>
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
		constexpr auto format(const RE::NiMatrix3& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "[{}, {}, {}]"sv, a_value[0], a_value[1], a_value[2]);
		}
	};
}
#endif
