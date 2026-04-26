#pragma once

#include "RE/D/DifficultyLevel.hpp"
#include "RE/L/LOCK_LEVEL.hpp"

namespace RE::GamePlayFormulas
{
	enum class ExperienceActivity : std::int32_t
	{
		kKillNPC = 0,
		kHackComputer = 1
	};

	[[nodiscard]] bool CanHackGateCheck(LOCK_LEVEL a_lockLevel);
	[[nodiscard]] bool CanPickLockGateCheck(LOCK_LEVEL a_lockLevel);
	[[nodiscard]] REX::Float32 CalcSprintingActionPoints(REX::Float32 a_equippedWeight, REX::Float32 a_elapsedTime, REX::Float32 a_endurance);
	[[nodiscard]] REX::Float32 CalculateItemHealthDamageBonus(REX::Float32 a_itemHealth);
	[[nodiscard]] REX::Float32 GetExperienceReward(ExperienceActivity a_activity, DifficultyLevel a_difficulty, REX::Float32 a_xpBase);
	[[nodiscard]] REX::Float32 GetHackingWordCount(REX::Float32 a_playerIntelligence);
	[[nodiscard]] REX::Float32 GetLockXPReward(LOCK_LEVEL a_lockLevel);
}
