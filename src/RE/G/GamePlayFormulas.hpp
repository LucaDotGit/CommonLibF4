#pragma once

#include "RE/D/DifficultyLevel.hpp"
#include "RE/L/LOCK_LEVEL.hpp"

namespace RE::GamePlayFormulas
{
	enum class ExperienceActivity : std::int32_t
	{
		KillNPC = 0,
		HackComputer = 1
	};

	[[nodiscard]]
	auto CalcSprintingActionPoints(REX::Float32 a_equippedWeight, REX::Float32 a_elapsedTime, REX::Float32 a_endurance)
		-> REX::Float32;
	[[nodiscard]]
	auto CalculateItemHealthDamageBonus(REX::Float32 a_itemHealth) -> REX::Float32;
	[[nodiscard]]
	auto CalculateItemValue(REX::Float32 a_baseValue, REX::Float32 a_health) -> REX::Float32;
	[[nodiscard]]
	auto CanHackGateCheck(LOCK_LEVEL a_lockLevel) -> bool;
	[[nodiscard]]
	auto CanPickLockGateCheck(LOCK_LEVEL a_lockLevel) -> bool;
	[[nodiscard]]
	auto GetExperienceReward(ExperienceActivity a_activity, DifficultyLevel a_difficulty, REX::Float32 a_xpBase)
		-> REX::Float32;
	[[nodiscard]]
	auto GetHackingWordCount(REX::Float32 a_playerIntelligence) -> REX::Float32;
	[[nodiscard]]
	auto GetLockXPReward(LOCK_LEVEL a_lockLevel) -> REX::Float32;
}
