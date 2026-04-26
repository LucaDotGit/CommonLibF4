#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiTransform
	{
	public:
		static const NiTransform IDENTITY;

		constexpr NiTransform() noexcept = default;

		constexpr NiTransform(const NiMatrix3& a_rotation, const NiPoint3& a_translation, REX::Float32 a_scale) noexcept
			: rotate(a_rotation), translate(a_translation), scale(a_scale)
		{
		}

		constexpr ~NiTransform() noexcept = default;

		constexpr NiTransform(const NiTransform&) noexcept = default;
		constexpr NiTransform(NiTransform&&) noexcept = default;

		constexpr NiTransform& operator=(const NiTransform&) noexcept = default;
		constexpr NiTransform& operator=(NiTransform&&) noexcept = default;

		// members
		NiMatrix3 rotate;			   // 00
		NiPoint3 translate;			   // 30
		REX::Float32 scale{ 1.0_f32 }; // 3C
	};
	static_assert(sizeof(NiTransform) == 0x40);

	inline constexpr auto NiTransform::IDENTITY = NiTransform(NiMatrix3::IDENTITY, NiPoint3(), 1.0_f32);
}
