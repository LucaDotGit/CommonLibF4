#pragma once

#include "RE/H/hkMatrix3.hpp"
#include "RE/H/hkRotation.hpp"
#include "RE/H/hkTransform.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	inline constexpr auto HK_TO_NI_SCALE = static_cast<REX::Float32>(69.99125);
	inline constexpr auto NI_TO_HK_SCALE = static_cast<REX::Float32>(0.0142875);

	[[nodiscard]]
	constexpr auto HkVector4ToNiPoint3(const hkVector4& a_hk) noexcept -> NiPoint3
	{
		return NiPoint3(a_hk.x, a_hk.y, a_hk.z) * HK_TO_NI_SCALE;
	}

	[[nodiscard]]
	constexpr auto NiPoint3ToHkVector4(const NiPoint3& a_ni) noexcept -> hkVector4
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, static_cast<REX::Float32>(0.0)) * NI_TO_HK_SCALE;
	}

	[[nodiscard]]
	constexpr auto HkVector4ToNiPoint3A(const hkVector4& a_hk) noexcept -> NiPoint3A
	{
		return NiPoint3A(a_hk.x, a_hk.y, a_hk.z) * HK_TO_NI_SCALE;
	}

	[[nodiscard]]
	constexpr auto NiPoint3AToHkVector4(const NiPoint3A& a_ni) noexcept -> hkVector4
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, static_cast<REX::Float32>(0.0)) * NI_TO_HK_SCALE;
	}

	[[nodiscard]]
	constexpr auto HkVector4ToNiPoint4(const hkVector4& a_hk) noexcept -> NiPoint4
	{
		return NiPoint4(a_hk.x, a_hk.y, a_hk.z, a_hk.w) * HK_TO_NI_SCALE;
	}

	[[nodiscard]]
	constexpr auto NiPoint4ToHkVector4(const NiPoint4& a_ni) noexcept -> hkVector4
	{
		return hkVector4(a_ni.x, a_ni.y, a_ni.z, a_ni.w) * NI_TO_HK_SCALE;
	}

	[[nodiscard]]
	constexpr auto HkMatrix3ToNiMatrix3(const hkMatrix3& a_matrix) noexcept -> NiMatrix3
	{
		auto result = NiMatrix3();
		result[0] = {a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], static_cast<REX::Float32>(0.0)};
		result[1] = {a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], static_cast<REX::Float32>(0.0)};
		result[2] = {a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], static_cast<REX::Float32>(0.0)};
		return result;
	}

	[[nodiscard]]
	constexpr auto NiMatrix3ToHkMatrix3(const NiMatrix3& a_matrix) noexcept -> hkMatrix3
	{
		auto result = hkMatrix3();
		result[0] = {a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], static_cast<REX::Float32>(0.0)};
		result[1] = {a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], static_cast<REX::Float32>(0.0)};
		result[2] = {a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], static_cast<REX::Float32>(0.0)};
		return result;
	}

	[[nodiscard]]
	constexpr auto NiMatrix3ToHkRotation(const NiMatrix3& a_matrix) noexcept -> hkRotation
	{
		auto result = hkRotation();
		result[0] = {a_matrix[0][0], a_matrix[1][0], a_matrix[2][0], static_cast<REX::Float32>(0.0)};
		result[1] = {a_matrix[0][1], a_matrix[1][1], a_matrix[2][1], static_cast<REX::Float32>(0.0)};
		result[2] = {a_matrix[0][2], a_matrix[1][2], a_matrix[2][2], static_cast<REX::Float32>(0.0)};
		return result;
	}

	[[nodiscard]]
	constexpr auto HkTransformToNiTransform(const hkTransform& a_transform) noexcept -> NiTransform
	{
		return {HkMatrix3ToNiMatrix3(a_transform.rotation), HkVector4ToNiPoint3(a_transform.translation)};
	}

	[[nodiscard]]
	constexpr auto NiTransformToHkTransform(const NiTransform& a_transform) noexcept -> hkTransform
	{
		return {NiMatrix3ToHkRotation(a_transform.rotation), NiPoint3ToHkVector4(a_transform.translation)};
	}
}
