#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) FleePackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FleePackage };
		inline static constexpr auto VTABLE{ VTABLE::FleePackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		~FleePackage() override; // 00

		// members
		BSTArray<ObjectRefHandle> avoidRefs; // 0C8
		NiPoint3 fleePoint;					 // 0E0
		REX::Float32 fleeTimer;				 // 0EC
		ObjectRefHandle teleportDoor;		 // 0F0
		ObjectRefHandle refFleeTo;			 // 0F4
		bool evaluatePoint;					 // 0F8
		bool combatMode;					 // 0F9
		bool fleeSucceeded;					 // 0FA
		bool knowsTarget;					 // 0FB
		bool useHorse;						 // 0FC
	};
	static_assert(sizeof(FleePackage) == 0x100);
}
