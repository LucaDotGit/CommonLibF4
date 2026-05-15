#pragma once

#include "RE/H/hkRotation.hpp"

namespace RE
{
	class hkTransform
	{
	public:
		constexpr hkTransform() noexcept = default;

		constexpr hkTransform(const hkRotation& a_rotation, const hkVector4& a_translation) noexcept
			: rotation(a_rotation), translation(a_translation)
		{
		}

		constexpr ~hkTransform() noexcept = default;

		constexpr hkTransform(const hkTransform&) noexcept = default;
		constexpr hkTransform(hkTransform&&) noexcept = default;

		constexpr hkTransform& operator=(const hkTransform&) noexcept = default;
		constexpr hkTransform& operator=(hkTransform&&) noexcept = default;

		// members
		hkRotation rotation;   // 00
		hkVector4 translation; // 30
	};
	static_assert(sizeof(hkTransform) == 0x40);
}
