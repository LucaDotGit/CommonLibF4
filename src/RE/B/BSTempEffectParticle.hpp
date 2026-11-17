#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class BGSDecalEmitter;
	class BGSParticleObjectCloneTask;
	class NiNode;

	class __declspec(novtable) BSTempEffectParticle : public BSTempEffect // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTempEffectParticle;
		inline static constexpr const auto& VTABLE = VTABLE::BSTempEffectParticle;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffectParticle;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::Particle;

		~BSTempEffectParticle() override; // 0x00

		// members
		NiPointer<NiAVObject> particleObject;			 // 0x30
		NiPointer<BGSParticleObjectCloneTask> cloneTask; // 0x38
		void* modelHandle;			  // 0x40 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
									  // BSResource::EntryDBTraits<BSModelDB::DBTraits,
									  // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>,
									  // BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> parentNode; // 0x48
		NiMatrix3 rotation;			  // 0x50
		NiPoint3 position;			  // 0x80
		REX::Float32 scale;			  // 0x8C
		std::uint32_t flags;		  // 0x90
		NiPointer<NiAVObject> followObject; // 0x98
		NiTransform followOffset;			// 0xA0
		BGSImpactData* decalImpactData;		// 0xE0
		BGSDecalEmitter* decalEmitter;		// 0xE8
		BSSoundHandle sound01;				// 0xF0
		BSSoundHandle sound02;				// 0xF8
	};

	static_assert(sizeof(BSTempEffectParticle) == 0x100);
}
