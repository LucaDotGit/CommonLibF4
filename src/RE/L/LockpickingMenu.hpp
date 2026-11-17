#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	enum class LOCK_LEVEL : std::int32_t;

	class NiControllerManager;
	class NiControllerSequence;
	class NiNode;

	class __declspec(novtable) LockpickingMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::LockpickingMenu;
		inline static constexpr const auto& VTABLE = VTABLE::LockpickingMenu;
		inline static constexpr auto MENU_NAME = "LockpickingMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::LockpickingMenu;

		~LockpickingMenu() override; // 0x00

		// override (GameMenuBase)
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override;	  // 0x03
		void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time) override;		  // 0x04
		auto OnButtonEventRelease(const BSFixedString& a_eventName) -> bool override; // 0x0F

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnMouseMoveEvent(const MouseMoveEvent* a_event) override;		// 0x06
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		[[nodiscard]]
		static auto GetCurrentLockRef() noexcept -> TESObjectREFR*
		{
			static const auto CURRENT_LOCK_REF = REL::Relocation<TESObjectREFR**>(ID::LockpickingMenu::CurrentLockRef);
			return *CURRENT_LOCK_REF;
		}

		[[nodiscard]]
		static auto GetCurrentLockLevel() noexcept -> LOCK_LEVEL&
		{
			static const auto CURRENT_LOCK_LEVEL = REL::Relocation<LOCK_LEVEL*>(ID::LockpickingMenu::CurrentLockLevel);
			return *CURRENT_LOCK_LEVEL;
		}

		static void DamageLockpick()
		{
			using FuncType = decltype(&LockpickingMenu::DamageLockpick);
			static const auto FUNC = REL::Relocation<FuncType>(ID::LockpickingMenu::DamageLockpick);
			std::invoke(FUNC);
		}

		static void OpenLockpickingMenu(TESObjectREFR* a_lockedRef)
		{
			using FuncType = decltype(&LockpickingMenu::OpenLockpickingMenu);
			static const auto FUNC = REL::Relocation<FuncType>(ID::LockpickingMenu::OpenLockpickingMenu);
			std::invoke(FUNC, a_lockedRef);
		}

		// members
		NiMatrix3 origPickRotate;			  // 0x0E0
		NiPoint3 origPickTranslate;			  // 0x110
		NiControllerManager* lockAnimManager; // 0x120
		NiControllerSequence* lockIntroAnim;  // 0x128
		NiControllerSequence* lockRotateAnim; // 0x130
		NiControllerManager* pickAnimManager; // 0x138
		NiControllerSequence* pickIntroAnim;  // 0x140
		NiControllerSequence* pickBendAnim;	  // 0x148
		NiControllerSequence* pickBreakAnim;  // 0x150
		NiControllerSequence* currPickAnim;	  // 0x158
		NiControllerSequence* currLockAnim;	  // 0x160
		void*
			lockModel; // 0x168 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
					   // BSResource::EntryDBTraits<BSModelDB::DBTraits,
					   // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		void*
			pickModel; // 0x170 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
					   // BSResource::EntryDBTraits<BSModelDB::DBTraits,
					   // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
		NiPointer<NiNode> lockRoot;			  // 0x178
		REX::Float32 currPickAnimElapsedSecs; // 0x180
		REX::Float32 currLockAnimElapsedSecs; // 0x184
		REX::Float32 pickAngle;				  // 0x188
		REX::Float32 lockAngle;				  // 0x18C
		REX::Float32 lockDamagePickAngle;	  // 0x190
		REX::Float32 pickBreakSecs;			  // 0x194
		BSSoundHandle pickTensionSound;		  // 0x198
		REX::Float32 sweetSpotCenter;		  // 0x1A0
		REX::Float32 sweetSpotLength;		  // 0x1A4
		REX::Float32 partialPickLength;		  // 0x1A8
		std::uint32_t picksBroken;			  // 0x1AC
		bool modelsInit;					  // 0x1B0
		bool animating;						  // 0x1B1
		bool turningLock;					  // 0x1B2
		bool menuCleanedUp;					  // 0x1B3
		bool tutorialMenuOpening;			  // 0x1B4
		bool crimeDetected;					  // 0x1B5
		bool vatsWasEnabled;				  // 0x1B6
		bool vatsDepthTestMask;				  // 0x1B7
	};

	static_assert(sizeof(LockpickingMenu) == 0x1C0);
}
