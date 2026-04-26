#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRefObject.hpp"

namespace RE
{
	class BGSAttackData;

	class __declspec(novtable) BGSAttackDataMap
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAttackDataMap };
		inline static constexpr auto VTABLE{ VTABLE::BGSAttackDataMap };

		// members
		BSTHashMap<BSFixedString, NiPointer<BGSAttackData>> attackDataMap; // 10
		TESRace* defaultDataRace;										   // 40
	};
	static_assert(sizeof(BGSAttackDataMap) == 0x48);
}
