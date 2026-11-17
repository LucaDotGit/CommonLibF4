#pragma once

#include "RE/H/hkRotation.hpp"

namespace RE
{
	class hkTransform
	{
	public:
		constexpr hkTransform() noexcept = default;

		constexpr hkTransform(const hkRotation& a_rotation, const hkVector4& a_translation) noexcept :
			rotation(a_rotation),
			translation(a_translation)
		{
		}

		constexpr ~hkTransform() noexcept = default;

		constexpr hkTransform(const hkTransform&) noexcept = default;
		constexpr hkTransform(hkTransform&&) noexcept = default;

		constexpr auto operator=(const hkTransform&) noexcept -> hkTransform& = default;
		constexpr auto operator=(hkTransform&&) noexcept -> hkTransform& = default;

		// members
		hkRotation rotation;   // 0x00
		hkVector4 translation; // 0x30
	};

	static_assert(sizeof(hkTransform) == 0x40);
}
