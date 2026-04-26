#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class BGSDecalEmitter;
	class BGSParticleObjectCloneTask;
	class NiNode;

	class __declspec(novtable) BSTempEffectParticle
		: public BSTempEffect // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTempEffectParticle };
		inline static constexpr auto VTABLE{ VTABLE::BSTempEffectParticle };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffectParticle };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kParticle };

		~BSTempEffectParticle() override; // 00

		// members
		NiPointer<NiAVObject> particleObject;			 // 30
		NiPointer<BGSParticleObjectCloneTask> cloneTask; // 38
		void* modelHandle;								 // 40 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> parentNode;					 // 48
		NiMatrix3 rotation;								 // 50
		NiPoint3 position;								 // 80
		REX::Float32 scale;								 // 8C
		std::uint32_t flags;							 // 90
		NiPointer<NiAVObject> followObject;				 // 98
		NiTransform followOffset;						 // A0
		BGSImpactData* decalImpactData;					 // E0
		BGSDecalEmitter* decalEmitter;					 // E8
		BSSoundHandle sound01;							 // F0
		BSSoundHandle sound02;							 // F8
	};
	static_assert(sizeof(BSTempEffectParticle) == 0x100);
}
