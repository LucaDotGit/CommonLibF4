#pragma once

#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSShaderParticleGeometryData;
	class BSGeometry;

	class __declspec(novtable) BSTempEffectSPG
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTempEffectSPG };
		inline static constexpr auto VTABLE{ VTABLE::BSTempEffectSPG };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffectSPG };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kSPG };

		~BSTempEffectSPG() override; // 00

		// members
		BGSShaderParticleGeometryData* SPGData; // 30
		NiPointer<BSGeometry> geometry;			// 38
		REX::Float32 totalFadeTime;				// 40
		REX::Float32 fadeTime;					// 44
		bool fadeIn;							// 48
	};
	static_assert(sizeof(BSTempEffectSPG) == 0x50);
}
