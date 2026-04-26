#pragma once

#include "RE/P/PACKAGE_DATA.hpp"
#include "RE/P/PackageEventAction.hpp"
#include "RE/P/PackageSchedule.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	enum class PACKAGE_PROCEDURE_TYPE : std::int32_t;

	class BGSIdleCollection;
	class PackageLocation;
	class PackageTarget;
	class TESPackageData;

	class __declspec(novtable) TESPackage
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESPackage };
		inline static constexpr auto VTABLE{ VTABLE::TESPackage };
		inline static constexpr auto FORM_TYPE{ FormType::kPackage };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kWaiting = 1 << 30,
				kNeverRun = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		~TESPackage() override; // 00

		// add
		virtual bool IsActorAtLocation(Actor* a_actor, bool a_ignoredistance, REX::Float32 a_extraRadius, bool a_inFurniture);									   // 4A
		virtual bool IsActorAtSecondLocation(Actor* a_mobileObject, Actor* a_packageOwner, bool a_ignoredistance, REX::Float32 a_otherRadius, bool a_inFurniture); // 4B
		virtual bool IsActorAtRefTarget(Actor* a_mobileObject, std::int32_t a_extraRadius);																		   // 4C
		virtual bool IsTargetAtLocation(Actor* a_actor, std::int32_t a_extraRadius);																			   // 4D
		virtual bool IsPackageOwner(Actor*);																													   // 4E - { return true; }

		// members
		PACKAGE_DATA data;											   // 20
		TESPackageData* packData;									   // 30
		PackageLocation* packLoc;									   // 38
		PackageTarget* packTarg;									   // 40
		BGSIdleCollection* idleCollection;							   // 48
		PackageSchedule packSched;									   // 50
		TESCondition packConditions;								   // 60
		TESCombatStyle* combatStyle;								   // 68
		TESQuest* ownerQuest;										   // 70
		PackageEventAction onBegin;									   // 78
		PackageEventAction onEnd;									   // 90
		PackageEventAction onChange;								   // A8
		REX::Enum<PACKAGE_PROCEDURE_TYPE, std::int32_t> procedureType; // C0
		std::uint32_t refCount;										   // C4
	};
	static_assert(sizeof(TESPackage) == 0xC8);
}
