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

	class __declspec(novtable) TESPackage : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESPackage;
		inline static constexpr const auto& VTABLE = VTABLE::TESPackage;
		inline static constexpr auto FORM_TYPE = FormType::Package;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Waiting = 1 << 30,
				NeverRun = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESPackage() override; // 0x00

		// add
		virtual auto IsActorAtLocation(
			Actor* a_actor,
			bool a_ignoredistance,
			REX::Float32 a_extraRadius,
			bool a_inFurniture) -> bool; // 0x4A
		virtual auto IsActorAtSecondLocation(
			Actor* a_mobileObject,
			Actor* a_packageOwner,
			bool a_ignoredistance,
			REX::Float32 a_otherRadius,
			bool a_inFurniture) -> bool;															// 0x4B
		virtual auto IsActorAtRefTarget(Actor* a_mobileObject, std::int32_t a_extraRadius) -> bool; // 0x4C
		virtual auto IsTargetAtLocation(Actor* a_actor, std::int32_t a_extraRadius) -> bool;		// 0x4D
		virtual auto IsPackageOwner(Actor*) -> bool; // 0x4E - { return true; }

		// members
		PACKAGE_DATA data;											   // 0x20
		TESPackageData* packData;									   // 0x30
		PackageLocation* packLoc;									   // 0x38
		PackageTarget* packTarg;									   // 0x40
		BGSIdleCollection* idleCollection;							   // 0x48
		PackageSchedule packSched;									   // 0x50
		TESCondition packConditions;								   // 0x60
		TESCombatStyle* combatStyle;								   // 0x68
		TESQuest* ownerQuest;										   // 0x70
		PackageEventAction onBegin;									   // 0x78
		PackageEventAction onEnd;									   // 0x90
		PackageEventAction onChange;								   // 0xA8
		REX::Enum<PACKAGE_PROCEDURE_TYPE, std::int32_t> procedureType; // 0xC0
		std::uint32_t refCount;										   // 0xC4
	};

	static_assert(sizeof(TESPackage) == 0xC8);
}
