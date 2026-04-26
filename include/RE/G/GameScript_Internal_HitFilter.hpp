#pragma once

#include "RE/G/GameScript_CombatEventHandler.hpp"

namespace RE::GameScript
{
	class HitFilter
	{
	public:
		// members
		BSScript::ObjectHandle causeHandle;								  // 00
		TESFormID sourceFormID;											  // 08
		TESFormID projectileFormID;										  // 0C
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> powerHit; // 10
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> sneakHit; // 14
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> bashHit;  // 18
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> blockHit; // 1C
		bool matchFilter;												  // 20
	};
	static_assert(sizeof(HitFilter) == 0x28);
}
