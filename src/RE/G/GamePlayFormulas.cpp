#include "RE/G/GamePlayFormulas.hpp"

namespace RE::GamePlayFormulas
{
	bool CanHackGateCheck(LOCK_LEVEL a_lockLevel)
	{
		using FuncType = decltype(&GamePlayFormulas::CanHackGateCheck);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::CanHackGateCheck };
		return std::invoke(FUNC, a_lockLevel);
	}

	bool CanPickLockGateCheck(LOCK_LEVEL a_lockLevel)
	{
		using FuncType = decltype(&GamePlayFormulas::CanPickLockGateCheck);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::CanPickLockGateCheck };
		return std::invoke(FUNC, a_lockLevel);
	}

	REX::Float32 CalcSprintingActionPoints(REX::Float32 a_equippedWeight, REX::Float32 a_elapsedTime, REX::Float32 a_endurance)
	{
		using FuncType = decltype(&GamePlayFormulas::CalcSprintingActionPoints);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::CalcSprintingActionPoints };
		return std::invoke(FUNC, a_equippedWeight, a_elapsedTime, a_endurance);
	}

	REX::Float32 CalculateItemHealthDamageBonus(REX::Float32 a_itemHealth)
	{
		using FuncType = decltype(&GamePlayFormulas::CalculateItemHealthDamageBonus);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::CalculateItemHealthDamageBonus };
		return std::invoke(FUNC, a_itemHealth);
	}

	REX::Float32 GetExperienceReward(ExperienceActivity a_activity, DifficultyLevel a_difficulty, REX::Float32 a_xpBase)
	{
		using FuncType = decltype(&GamePlayFormulas::GetExperienceReward);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::GetExperienceReward };
		return std::invoke(FUNC, a_activity, a_difficulty, a_xpBase);
	}

	REX::Float32 GetHackingWordCount(REX::Float32 a_playerIntelligence)
	{
		using FuncType = decltype(&GamePlayFormulas::GetHackingWordCount);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::GetHackingWordCount };
		return std::invoke(FUNC, a_playerIntelligence);
	}

	REX::Float32 GetLockXPReward(LOCK_LEVEL a_lockLevel)
	{
		using FuncType = decltype(&GamePlayFormulas::GetLockXPReward);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GamePlayFormulas::GetLockXPReward };
		return std::invoke(FUNC, a_lockLevel);
	}
}
