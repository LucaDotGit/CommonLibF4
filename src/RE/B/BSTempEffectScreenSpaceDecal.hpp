#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSDeferredDecal
{
	class BSDFDecal;
}

namespace RE
{
	class __declspec(novtable) BSTempEffectScreenSpaceDecal : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::__BSTempEffectScreenSpaceDecal;
		inline static constexpr const auto& VTABLE = VTABLE::__BSTempEffectScreenSpaceDecal;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffectScreenSpaceDecal;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::Decal;

		~BSTempEffectScreenSpaceDecal() override; // 0x00

		// members
		bool permanent;								 // 0x30
		NiPointer<BSDeferredDecal::BSDFDecal> decal; // 0x38
	};

	static_assert(sizeof(BSTempEffectScreenSpaceDecal) == 0x40);
}
