#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/E/EquippedItemData.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class ATTACK_STATE_ENUM : std::uint32_t;

	class AimModel;
	class BSCloneReserver;
	class MuzzleFlash;
	class NiAVObject;
	class QueuedFile;

	class __declspec(novtable) EquippedWeaponData : public EquippedItemData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::EquippedWeaponData;
		inline static constexpr const auto& VTABLE = VTABLE::EquippedWeaponData;

		void SetupFireSounds(Actor& a_actor, BGSObjectInstanceT<TESObjectWEAP>& a_weapon)
		{
			using FuncType = decltype(&EquippedWeaponData::SetupFireSounds);
			static const auto FUNC = REL::Relocation<FuncType>(ID::EquippedWeaponData::SetupFireSounds);
			std::invoke(FUNC, this, a_actor, a_weapon);
		}

		// members
		TESAmmo* ammo;										   // 0x10
		std::uint32_t ammoCount;							   // 0x18
		AimModel* aimModel;									   // 0x20
		MuzzleFlash* muzzleFlash;							   // 0x28
		NiAVObject* fireNode;								   // 0x30
		ATTACK_STATE_ENUM attackState;						   // 0x38
		BSTArray<BSTPair<std::uint32_t, void*>> fireLocations; // 0x40 - AnimationStanceFireLocationData<NiPoint3>
		NiPointer<QueuedFile> weaponPreload;				   // 0x58
		NiPointer<QueuedFile> projectilePreload;			   // 0x60
		NiPointer<BSCloneReserver> reserveProjectileClones;	   // 0x68
		BSSoundHandle idleSound;							   // 0x70
		BSSoundHandle attackSound;							   // 0x78
		BSSoundHandle reverbSound;							   // 0x80
		BSSoundHandle prevAttack;							   // 0x88
		BSSoundHandle prevReverb;							   // 0x90
		BGSSoundKeywordMapping* attackSoundData;			   // 0x98
		bool reverbSoundIsTail;								   // 0xA0
	};

	static_assert(sizeof(EquippedWeaponData) == 0xA8);
}
