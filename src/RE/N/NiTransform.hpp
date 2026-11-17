#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiTransform
	{
	public:
		static const NiTransform IDENTITY;

		constexpr NiTransform() noexcept = default;

		constexpr NiTransform(const NiMatrix3& a_rotation, const NiPoint3& a_translation) noexcept :
			rotation(a_rotation),
			translation(a_translation)
		{
		}

		constexpr NiTransform(const NiMatrix3& a_rotation, const NiPoint3& a_translation, REX::Float32 a_scale) noexcept
			:
			rotation(a_rotation),
			translation(a_translation),
			scale(a_scale)
		{
		}

		constexpr ~NiTransform() noexcept = default;

		constexpr NiTransform(const NiTransform&) noexcept = default;
		constexpr NiTransform(NiTransform&&) noexcept = default;

		constexpr auto operator=(const NiTransform&) noexcept -> NiTransform& = default;
		constexpr auto operator=(NiTransform&&) noexcept -> NiTransform& = default;

		// members
		NiMatrix3 rotation;									// 0x00
		NiPoint3 translation;								// 0x30
		REX::Float32 scale{static_cast<REX::Float32>(1.0)}; // 0x3C
	};

	static_assert(sizeof(NiTransform) == 0x40);

	inline constexpr auto NiTransform::IDENTITY =
		NiTransform(NiMatrix3::IDENTITY, NiPoint3(), static_cast<REX::Float32>(1.0));
}
