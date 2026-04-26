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

	class __declspec(novtable) EquippedWeaponData
		: public EquippedItemData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::EquippedWeaponData };
		inline static constexpr auto VTABLE{ VTABLE::EquippedWeaponData };

		void SetupFireSounds(Actor& a_actor, BGSObjectInstanceT<TESObjectWEAP>& a_weapon)
		{
			using FuncType = decltype(&EquippedWeaponData::SetupFireSounds);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::EquippedWeaponData::SetupFireSounds };
			FUNC(this, a_actor, a_weapon);
		}

		// members
		TESAmmo* ammo;										   // 10
		std::uint32_t ammoCount;							   // 18
		AimModel* aimModel;									   // 20
		MuzzleFlash* muzzleFlash;							   // 28
		NiAVObject* fireNode;								   // 30
		ATTACK_STATE_ENUM attackState;						   // 38
		BSTArray<BSTPair<std::uint32_t, void*>> fireLocations; // 40 - AnimationStanceFireLocationData<NiPoint3>
		NiPointer<QueuedFile> weaponPreload;				   // 58
		NiPointer<QueuedFile> projectilePreload;			   // 60
		NiPointer<BSCloneReserver> reserveProjectileClones;	   // 68
		BSSoundHandle idleSound;							   // 70
		BSSoundHandle attackSound;							   // 78
		BSSoundHandle reverbSound;							   // 80
		BSSoundHandle prevAttack;							   // 88
		BSSoundHandle prevReverb;							   // 90
		BGSSoundKeywordMapping* attackSoundData;			   // 98
		bool reverbSoundIsTail;								   // A0
	};
	static_assert(sizeof(EquippedWeaponData) == 0xA8);
}
