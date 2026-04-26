#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSDeferredDecal
{
	class BSDFDecal;
}

namespace RE
{
	class __declspec(novtable) BSTempEffectScreenSpaceDecal
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::__BSTempEffectScreenSpaceDecal };
		inline static constexpr auto VTABLE{ VTABLE::__BSTempEffectScreenSpaceDecal };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffectScreenSpaceDecal };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kDecal };

		~BSTempEffectScreenSpaceDecal() override; // 00

		// members
		bool permanent;								 // 30
		NiPointer<BSDeferredDecal::BSDFDecal> decal; // 38
	};
	static_assert(sizeof(BSTempEffectScreenSpaceDecal) == 0x40);
}
