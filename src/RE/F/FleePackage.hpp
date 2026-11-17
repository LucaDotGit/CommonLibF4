#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESPackage.hpp"

namespace RE
{
	class __declspec(novtable) FleePackage : public TESPackage // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FleePackage;
		inline static constexpr const auto& VTABLE = VTABLE::FleePackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		~FleePackage() override; // 0x00

		// members
		BSTArray<ObjectRefHandle> avoidRefs; // 0x0C8
		NiPoint3 fleePoint;					 // 0x0E0
		REX::Float32 fleeTimer;				 // 0x0EC
		ObjectRefHandle teleportDoor;		 // 0x0F0
		ObjectRefHandle refFleeTo;			 // 0x0F4
		bool evaluatePoint;					 // 0x0F8
		bool combatMode;					 // 0x0F9
		bool fleeSucceeded;					 // 0x0FA
		bool knowsTarget;					 // 0x0FB
		bool useHorse;						 // 0x0FC
	};

	static_assert(sizeof(FleePackage) == 0x100);
}
