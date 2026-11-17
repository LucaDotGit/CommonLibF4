#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BGSAttackData;

	class __declspec(novtable) BGSAttackDataMap : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAttackDataMap;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAttackDataMap;

		// members
		BSTHashMap<BSFixedString, NiPointer<BGSAttackData>> attackDataMap; // 0x10
		TESRace* defaultDataRace;										   // 0x40
	};

	static_assert(sizeof(BGSAttackDataMap) == 0x48);
}
