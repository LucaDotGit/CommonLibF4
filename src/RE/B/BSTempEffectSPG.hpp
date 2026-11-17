#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSShaderParticleGeometryData;
	class BSGeometry;

	class __declspec(novtable) BSTempEffectSPG : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTempEffectSPG;
		inline static constexpr const auto& VTABLE = VTABLE::BSTempEffectSPG;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffectSPG;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::SPG;

		~BSTempEffectSPG() override; // 0x00

		// members
		BGSShaderParticleGeometryData* SPGData; // 0x30
		NiPointer<BSGeometry> geometry;			// 0x38
		REX::Float32 totalFadeTime;				// 0x40
		REX::Float32 fadeTime;					// 0x44
		bool fadeIn;							// 0x48
	};

	static_assert(sizeof(BSTempEffectSPG) == 0x50);
}
