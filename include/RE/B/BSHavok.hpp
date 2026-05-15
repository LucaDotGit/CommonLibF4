#pragma once

#include "RE/H/hkMatrix3.hpp"
#include "RE/H/hkRotation.hpp"
#include "RE/H/hkTransform.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	inline constexpr auto HK_TO_NI_SCALE = 69.99125_f32;
	inline constexpr auto NI_TO_HK_SCALE = 0.0142875_f32;

	[[nodiscard]] constexpr NiPoint3 HkVector4ToNiPoint3(const hkVector4& a_hk) noexcept
	{
		return NiPoint3(a_hk.x, a_hk.y, a_hk.z) * HK_TO_NI_SCALE;
	}

	[[nodiscard]] constexpr hkVector4 NiPoint3ToHkVector4(const NiPoint3& a_ni) noexcept
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, 0.0_f32) * NI_TO_HK_SCALE;
	}

	[[nodiscard]] constexpr NiPoint3A HkVector4ToNiPoint3A(const hkVector4& a_hk) noexcept
	{
		return NiPoint3A(a_hk.x, a_hk.y, a_hk.z) * HK_TO_NI_SCALE;
	}

	[[nodiscard]] constexpr hkVector4 NiPoint3AToHkVector4(const NiPoint3A& a_ni) noexcept
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, 0.0_f32) * NI_TO_HK_SCALE;
	}

	[[nodiscard]] constexpr NiPoint4 HkVector4ToNiPoint4(const hkVector4& a_hk) noexcept
	{
		return NiPoint4(a_hk.x, a_hk.y, a_hk.z, a_hk.w) * HK_TO_NI_SCALE;
	}

	[[nodiscard]] constexpr hkVector4 NiPoint4ToHkVector4(const NiPoint4& a_ni) noexcept
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, a_ni.w) * NI_TO_HK_SCALE;
	}

	[[nodiscard]] constexpr NiMatrix3 HkMatrix3ToNiMatrix3(const hkMatrix3& a_matrix) noexcept
	{
		auto result = NiMatrix3();
		result[0] = { a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], 0.0_f32 };
		result[1] = { a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], 0.0_f32 };
		result[2] = { a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], 0.0_f32 };
		return result;
	}

	[[nodiscard]] constexpr hkMatrix3 NiMatrix3ToHkMatrix3(const NiMatrix3& a_matrix) noexcept
	{
		auto result = hkMatrix3();
		result[0] = { a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], 0.0_f32 };
		result[1] = { a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], 0.0_f32 };
		result[2] = { a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], 0.0_f32 };
		return result;
	}

	[[nodiscard]] constexpr hkRotation NiMatrix3ToHkRotation(const NiMatrix3& a_matrix) noexcept
	{
		auto result = hkRotation();
		result[0] = { a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], 0.0_f32 };
		result[1] = { a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], 0.0_f32 };
		result[2] = { a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], 0.0_f32 };
		return result;
	}

	[[nodiscard]] constexpr NiTransform HkTransformToNiTransform(const hkTransform& a_transform) noexcept
	{
		return { HkMatrix3ToNiMatrix3(a_transform.rotation), HkVector4ToNiPoint3(a_transform.translation) };
	}

	[[nodiscard]] constexpr hkTransform NiTransformToHkTransform(const NiTransform& a_transform) noexcept
	{
		return { NiMatrix3ToHkRotation(a_transform.rotation), NiPoint3ToHkVector4(a_transform.translation) };
	}
}
