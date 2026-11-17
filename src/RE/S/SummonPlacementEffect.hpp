#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/ReferenceEffect.hpp"
#include "RE/S/SimpleAnimationGraphManagerHolder.hpp"

namespace RE
{
	class BGSArtObjectCloneTask;
	class NiAVObject;
	class BSAnimationGraphEvent;

	class __declspec(novtable) SummonPlacementEffect :
		public ReferenceEffect,					   // 0x00
		public SimpleAnimationGraphManagerHolder,  // 0x48
		public BSTEventSink<BSAnimationGraphEvent> // 0x60
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SummonPlacementEffect;
		inline static constexpr const auto& VTABLE = VTABLE::SummonPlacementEffect;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::SummonPlacementEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::MagicSummon;

		~SummonPlacementEffect() override; // 0x00

		// members
		BGSArtObject* artObject;					// 0x70
		NiPoint3 fixedLocation;						// 0x78
		NiPointer<NiAVObject> artObject3D;			// 0x88
		std::byte* loadedDataSubBuffer;				// 0x90
		NiPointer<BGSArtObjectCloneTask> cloneTask; // 0x98
		bool animationComplete;						// 0x99
	};

	static_assert(sizeof(SummonPlacementEffect) == 0xA0);
}
