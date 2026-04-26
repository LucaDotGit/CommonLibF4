#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t;

	class NiControllerManager;
	class NiControllerSequence;
	class NiNode;

	class __declspec(novtable) LockpickingMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::LockpickingMenu };
		inline static constexpr auto VTABLE{ VTABLE::LockpickingMenu };
		inline static constexpr auto MENU_NAME{ "LockpickingMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kLockpickingMenu };

		~LockpickingMenu() override; // 00

		// override (GameMenuBase)
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;			// 03
		void AdvanceMovie(REX::Float32 a_timeDelta, std::uint64_t a_time) override; // 04
		bool OnButtonEventRelease(const BSFixedString& a_eventName) override;		// 0F

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent*) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent*) override; // 04
		void OnMouseMoveEvent(const MouseMoveEvent*) override;	 // 06
		void OnButtonEvent(const ButtonEvent*) override;		 // 08

		[[nodiscard]] static TESObjectREFR* GetCurrentLockRef()
		{
			static const auto CURRENT_LOCK_REF = REL::Relocation<TESObjectREFR**>{ ID::LockpickingMenu::CurrentLockRef };
			return *CURRENT_LOCK_REF;
		}

		[[nodiscard]] static LOCK_LEVEL& GetCurrentLockLevel()
		{
			static const auto CURRENT_LOCK_LEVEL = REL::Relocation<LOCK_LEVEL*>{ ID::LockpickingMenu::CurrentLockLevel };
			return *CURRENT_LOCK_LEVEL;
		}

		static void OpenLockpickingMenu(TESObjectREFR* a_lockedRef)
		{
			using FuncType = decltype(&LockpickingMenu::OpenLockpickingMenu);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::LockpickingMenu::OpenLockpickingMenu };
			FUNC(a_lockedRef);
		}

		// members
		NiMatrix3 origPickRotate;			  // 0E0
		NiPoint3 origPickTranslate;			  // 110
		NiControllerManager* lockAnimManager; // 120
		NiControllerSequence* lockIntroAnim;  // 128
		NiControllerSequence* lockRotateAnim; // 130
		NiControllerManager* pickAnimManager; // 138
		NiControllerSequence* pickIntroAnim;  // 140
		NiControllerSequence* pickBendAnim;	  // 148
		NiControllerSequence* pickBreakAnim;  // 150
		NiControllerSequence* currPickAnim;	  // 158
		NiControllerSequence* currLockAnim;	  // 160
		void* lockModel;					  // 168 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		void* pickModel;					  // 170 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> lockRoot;			  // 178
		REX::Float32 currPickAnimElapsedSecs; // 180
		REX::Float32 currLockAnimElapsedSecs; // 184
		REX::Float32 pickAngle;				  // 188
		REX::Float32 lockAngle;				  // 18C
		REX::Float32 lockDamagePickAngle;	  // 190
		REX::Float32 pickBreakSecs;			  // 194
		BSSoundHandle pickTensionSound;		  // 198
		REX::Float32 sweetSpotCenter;		  // 1A0
		REX::Float32 sweetSpotLength;		  // 1A4
		REX::Float32 partialPickLength;		  // 1A8
		std::uint32_t picksBroken;			  // 1AC
		bool modelsInit;					  // 1B0
		bool animating;						  // 1B1
		bool turningLock;					  // 1B2
		bool menuCleanedUp;					  // 1B3
		bool tutorialMenuOpening;			  // 1B4
		bool crimeDetected;					  // 1B5
		bool vatsWasEnabled;				  // 1B6
		bool vatsDepthTestMask;				  // 1B7
	};
	static_assert(sizeof(LockpickingMenu) == 0x1C0);
}
