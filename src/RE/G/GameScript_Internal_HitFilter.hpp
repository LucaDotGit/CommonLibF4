#pragma once

#include "RE/G/GameScript_CombatEventHandler.hpp"

namespace RE::GameScript
{
	class HitFilter
	{
	public:
		// members
		BSScript::ObjectHandle causeHandle;								  // 0x00
		TESFormID sourceFormID;											  // 0x08
		TESFormID projectileFormID;										  // 0x0C
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> powerHit; // 0x10
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> sneakHit; // 0x14
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> bashHit;  // 0x18
		REX::Enum<CombatEventHandler::BoolFilter, std::int32_t> blockHit; // 0x1C
		bool matchFilter;												  // 0x20
	};

	static_assert(sizeof(HitFilter) == 0x28);
}
