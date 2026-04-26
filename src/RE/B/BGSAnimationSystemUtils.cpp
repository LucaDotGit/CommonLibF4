#include "RE/B/BGSAnimationSystemUtils.hpp"

namespace RE::BGSAnimationSystemUtils
{
	bool GetActiveSyncInfo(const IAnimationGraphManagerHolder* a_graphHolder, ActiveSyncInfo& a_infoOut)
	{
		using FuncType = decltype(&BGSAnimationSystemUtils::GetActiveSyncInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSAnimationSystemUtils::GetActiveSyncInfo };
		return std::invoke(FUNC, a_graphHolder, a_infoOut);
	}

	bool InitializeActorInstant(Actor& a_actor, bool a_update3D)
	{
		using FuncType = decltype(&BGSAnimationSystemUtils::InitializeActorInstant);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSAnimationSystemUtils::InitializeActorInstant };
		return std::invoke(FUNC, a_actor, a_update3D);
	}

	bool IsActiveGraphInTransition(const TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&BGSAnimationSystemUtils::IsActiveGraphInTransition);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSAnimationSystemUtils::IsActiveGraphInTransition };
		return std::invoke(FUNC, a_ref);
	}
}
