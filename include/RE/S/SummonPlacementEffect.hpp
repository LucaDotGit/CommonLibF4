#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/ReferenceEffect.hpp"
#include "RE/S/SimpleAnimationGraphManagerHolder.hpp"

namespace RE
{
	class BGSArtObjectCloneTask;
	class NiAVObject;
	class BSAnimationGraphEvent;

	class __declspec(novtable) SummonPlacementEffect
		: public ReferenceEffect,					 // 00
		  public SimpleAnimationGraphManagerHolder,	 // 48
		  public BSTEventSink<BSAnimationGraphEvent> // 60
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SummonPlacementEffect };
		inline static constexpr auto VTABLE{ VTABLE::SummonPlacementEffect };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::SummonPlacementEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kMagicSummon };

		~SummonPlacementEffect() override;

		// members
		BGSArtObject* artObject;					// 70
		NiPoint3 fixedLocation;						// 78
		NiPointer<NiAVObject> artObject3D;			// 88
		std::byte* loadedDataSubBuffer;				// 90
		NiPointer<BGSArtObjectCloneTask> cloneTask; // 98
		bool animationComplete;						// 99
	};
	static_assert(sizeof(SummonPlacementEffect) == 0xA0);
}
