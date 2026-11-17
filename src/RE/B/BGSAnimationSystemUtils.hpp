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
		BSTScrapObjectArena<BSTPair<BSFixedString, REX::Float32>, 0x20> otherSyncInfo; // 0x00
		REX::Float32 currentAnimTime;												   // 0x40
		REX::Float32 animSpeedMult;													   // 0x44
		REX::Float32 totalAnimTime;													   // 0x48
	};

	static_assert(sizeof(ActiveSyncInfo) == 0x50);

	auto GetActiveSyncInfo(const IAnimationGraphManagerHolder* a_graphHolder, ActiveSyncInfo& a_infoOut) -> bool;
	auto InitializeActorInstant(Actor& a_actor, bool a_update3D) -> bool;
	auto IsActiveGraphInTransition(const TESObjectREFR* a_ref) -> bool;
}
