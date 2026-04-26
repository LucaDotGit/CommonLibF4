#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class IAnimationGraphManagerHolder;
}

namespace RE::BGSAnimationSystemUtils
{
	class ActiveSyncInfo
	{
	public:
		// members
		BSTScrapObjectArena<BSTPair<BSFixedString, REX::Float32>> otherSyncInfo; // 00
		REX::Float32 currentAnimTime;											 // 40
		REX::Float32 animSpeedMult;												 // 44
		REX::Float32 totalAnimTime;												 // 48
	};
	static_assert(sizeof(ActiveSyncInfo) == 0x50);

	bool GetActiveSyncInfo(const IAnimationGraphManagerHolder* a_graphHolder, ActiveSyncInfo& a_infoOut);
	bool InitializeActorInstant(Actor& a_actor, bool a_update3D);
	bool IsActiveGraphInTransition(const TESObjectREFR* a_ref);
}
