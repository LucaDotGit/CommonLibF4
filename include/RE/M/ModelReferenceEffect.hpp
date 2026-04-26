#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/RefAttachTechniqueInput.hpp"
#include "RE/R/ReferenceEffect.hpp"
#include "RE/S/SimpleAnimationGraphManagerHolder.hpp"

namespace RE
{
	class BGSArtObjectCloneTask;
	class NiAVObject;
	class BSAnimationGraphEvent;

	class __declspec(novtable) ModelReferenceEffect
		: public ReferenceEffect,					 // 00
		  public SimpleAnimationGraphManagerHolder,	 // 48
		  public BSTEventSink<BSAnimationGraphEvent> // 60
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ModelReferenceEffect };
		inline static constexpr auto VTABLE{ VTABLE::ModelReferenceEffect };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::ModelReferenceEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kRefModel };

		~ModelReferenceEffect() override;

		// members
		RefAttachTechniqueInput hitEffectArtData;	// 70
		void* loadedDataSubBuffer;					// B8
		BGSArtObject* artObject;					// C0
		NiPointer<BGSArtObjectCloneTask> cloneTask; // C8
		NiPointer<NiAVObject> artObject3D;			// D0
		std::uint32_t flags;						// D4
	};
	static_assert(sizeof(ModelReferenceEffect) == 0xD8);
}
