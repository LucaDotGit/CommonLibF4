#pragma once

#include "RE/B/BGSLoadGameSubBuffer.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/M/MagicCaster.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/RefAttachTechniqueInput.hpp"
#include "RE/S/SimpleAnimationGraphManagerHolder.hpp"

namespace RE::MagicSystem
{
	enum class CastingSource : std::int32_t;
}

namespace RE
{
	class BGSArtObjectCloneTask;
	class BSAnimationGraphEvent;
	class BSLight;
	class WeaponEnchantmentController;

	class __declspec(novtable) ActorMagicCaster :
		public MagicCaster,						   // 0x00
		public SimpleAnimationGraphManagerHolder,  // 0x48
		public BSTEventSink<BSAnimationGraphEvent> // 0x60
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorMagicCaster;
		inline static constexpr const auto& VTABLE = VTABLE::ActorMagicCaster;

		~ActorMagicCaster() override; // 0x00

		// members
		RefAttachTechniqueInput castingArtData;							   // 0x68
		NiPointer<BGSArtObjectCloneTask> cloneTask;						   // 0xB0
		Actor* casterActor;												   // 0xB8
		NiNode* magicNode;												   // 0xC0
		NiPointer<BSLight> light;										   // 0xC8
		void (*interruptHandler)(Actor*);								   // 0xD0
		BGSLoadGameSubBuffer loadGameSubBuffer;							   // 0xD8
		BGSArtObject* waitingForCastingArt;								   // 0xE0
		WeaponEnchantmentController* weaponEnchantmentController;		   // 0xE8
		REX::Float32 costCharged;										   // 0xF0
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 0xF4
		std::uint32_t flags;											   // 0xF8
	};

	static_assert(sizeof(ActorMagicCaster) == 0x100);
}
