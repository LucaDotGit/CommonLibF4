#pragma once

#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTList.hpp"
#include "RE/Bethesda/TESCondition.hpp"
#include "RE/Bethesda/TESForms.hpp"
#include "RE/NetImmerse/NiPoint.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	enum class PACK_EVENT_ACTION_TYPE;
	enum class PACKAGE_PROCEDURE_TYPE;
	enum class TOPIC_MODE;

	class Crime;
	class NiAVObject;
	class PackageLocation;
	class PackageTarget;

	struct PACKAGE_DATA
	{
	public:
		// members
		std::uint32_t packFlags;			// 00
		std::int8_t packType;				// 04
		std::int8_t interruptOverrideType;	// 05
		std::int8_t maxSpeed;				// 06
		std::uint16_t foBehaviorFlags;		// 08
		std::uint16_t packageSpecificFlags; // 0A
	};
	static_assert(sizeof(PACKAGE_DATA) == 0xC);

	struct PACK_SCHED_DATA
	{
	public:
		// members
		std::int8_t month;	   // 00
		std::int8_t dayOfWeek; // 01
		std::int8_t date;	   // 02
		std::int8_t hour;	   // 03
		std::int8_t min;	   // 04
		std::int32_t duration; // 08
	};
	static_assert(sizeof(PACK_SCHED_DATA) == 0xC);

	class PackageSchedule
	{
	public:
		// members
		PACK_SCHED_DATA psData; // 00
	};
	static_assert(sizeof(PackageSchedule) == 0xC);

	class BGSTopicSubtypeUnion
	{
	public:
		enum class TOPIC_MODE;

		// members
		REX::Enum<TOPIC_MODE, std::int32_t> mode; // 00
		union
		{
			DIALOGUE_SUBTYPE generalTopicSubtype;
			std::uint32_t specificTopicID;
		}; // 4
	};
	static_assert(sizeof(BGSTopicSubtypeUnion) == 0x8);

	class PackageEventAction
	{
	public:
		// members
		TESIdleForm* idle;									  // 00
		REX::Enum<PACK_EVENT_ACTION_TYPE, std::int32_t> type; // 08
		BGSTopicSubtypeUnion topicSubtypeUnion;				  // 0C
	};
	static_assert(sizeof(PackageEventAction) == 0x18);

	class __declspec(novtable) TESPackage
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESPackage };
		inline static constexpr auto VTABLE{ VTABLE::TESPackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// add
		virtual bool IsActorAtLocation(Actor* a_ctor, bool a_ignoredistance, float a_extraRadius, bool a_infurniture);									   // 4A
		virtual bool IsActorAtSecondLocation(Actor* a_mobileObject, Actor* a_packageowner, bool a_ignoredistance, float a_otherRadius, bool bInfurniture); // 4B
		virtual bool IsActorAtRefTarget(Actor* a_mobileObject, std::int32_t a_extraRadius);																   // 4C
		virtual bool IsTargetAtLocation(Actor* a_actor, std::int32_t a_extraRadius);																	   // 4D
		virtual bool IsPackageOwner(Actor*) { return true; }																							   // 4E

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

	class __declspec(novtable) AlarmPackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AlarmPackage };
		inline static constexpr auto VTABLE{ VTABLE::AlarmPackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		// members
		BSSimpleList<Crime*> crimes; // C8
		bool forceGreet;			 // D8
	};
	static_assert(sizeof(AlarmPackage) == 0xE0);

	class __declspec(novtable) DialoguePackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DialoguePackage };
		inline static constexpr auto VTABLE{ VTABLE::DialoguePackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		// members
		ActorHandle talkingActor;		  // C8
		ObjectRefHandle genericSecondLoc; // CC
		ActorHandle actor;				  // D0
		ActorHandle targetActor;		  // D4
		bool actorHeadTrack;			  // D8
		bool createdPack;				  // D9
		float eventWaitTimer;			  // DC
		float listenTimer;				  // E0
		bool sceneGenerated;			  // E4
	};
	static_assert(sizeof(DialoguePackage) == 0xE8);

	class __declspec(novtable) FleePackage
		: public TESPackage // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FleePackage };
		inline static constexpr auto VTABLE{ VTABLE::FleePackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		// members
		BSTArray<ObjectRefHandle> avoidRefs; // 0C8
		NiPoint3 fleePoint;					 // 0E0
		float fleeTimer;					 // 0EC
		ObjectRefHandle teleportDoor;		 // 0F0
		ObjectRefHandle refFleeTo;			 // 0F4
		bool evaluatePoint;					 // 0F8
		bool combatMode;					 // 0F9
		bool fleeSucceeded;					 // 0FA
		bool knowstarget;					 // 0FB
		bool usehorse;						 // 0FC
	};
	static_assert(sizeof(FleePackage) == 0x100);

	class SpectatorThreatInfo
	{
	public:
		enum class THREAT_LEVEL;

		// members
		ActorHandle source;								   // 00
		ActorHandle target;								   // 04
		REX::Enum<THREAT_LEVEL, std::int32_t> threatLevel; // 08
		std::time_t lastPerceivedTime;					   // 10
		float radius;									   // 18
		NiPoint3 lastKnownPosSource;					   // 1C
		NiPoint3 lastKnownPosTarget;					   // 28
		bool hasSource;									   // 34
		bool hasTarget;									   // 35
		NiPointer<NiAVObject> debugGeometry;			   // 38
	};
	static_assert(sizeof(SpectatorThreatInfo) == 0x40);

	class __declspec(novtable) SpectatorPackage
		: public TESPackage // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SpectatorPackage };
		inline static constexpr auto VTABLE{ VTABLE::SpectatorPackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		// members
		std::time_t lastPathRequestTime;			  // 0C8
		float timer;								  // 0D0
		float conversationTimer;					  // 0D4
		float eventRadius;							  // 0D8
		bool flagCompleted;							  // 0DC
		NiPoint3 eventCenter;						  // 0E0
		BSTArray<SpectatorThreatInfo> threatInfoList; // 0F0
		NiPointer<NiAVObject> debugGeometry;		  // 108
	};
	static_assert(sizeof(SpectatorPackage) == 0x110);

	class __declspec(novtable) TrespassPackage
		: public TESPackage // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TrespassPackage };
		inline static constexpr auto VTABLE{ VTABLE::TrespassPackage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPACK };

		// members
		float warningtimer;		   // C8
		std::int32_t warning;	   // CC
		TESForm* owner;			   // D0
		std::int32_t crimeNumber;  // D9
		std::int32_t warninglevel; // DC
		std::int32_t numberActors; // E0
	};
	static_assert(sizeof(TrespassPackage) == 0xE8);
}
