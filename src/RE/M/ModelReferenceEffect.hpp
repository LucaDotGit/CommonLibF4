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

	class __declspec(novtable) ModelReferenceEffect :
		public ReferenceEffect,					   // 0x00
		public SimpleAnimationGraphManagerHolder,  // 0x48
		public BSTEventSink<BSAnimationGraphEvent> // 0x60
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ModelReferenceEffect;
		inline static constexpr const auto& VTABLE = VTABLE::ModelReferenceEffect;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::ModelReferenceEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::RefModel;

		~ModelReferenceEffect() override; // 0x00

		// members
		RefAttachTechniqueInput hitEffectArtData;	// 0x70
		void* loadedDataSubBuffer;					// 0xB8
		BGSArtObject* artObject;					// 0xC0
		NiPointer<BGSArtObjectCloneTask> cloneTask; // 0xC8
		NiPointer<NiAVObject> artObject3D;			// 0xD0
		std::uint32_t flags;						// 0xD4
	};

	static_assert(sizeof(ModelReferenceEffect) == 0xD8);
}
