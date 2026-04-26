#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
	class PositionPlayerEvent;

	class __declspec(novtable) MenuTopicManager
		: public BSTEventSink<MenuOpenCloseEvent>,	// 00
		  public BSTEventSink<PositionPlayerEvent>, // 08
		  public BSTSingletonSDM<MenuTopicManager>	// 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MenuTopicManager };
		inline static constexpr auto VTABLE{ VTABLE::MenuTopicManager };

		[[nodiscard]] static MenuTopicManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<MenuTopicManager**>{ ID::MenuTopicManager::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] bool IsCurrentSpeaker(const ObjectRefHandle& a_refHandle) const noexcept
		{
			return menuOpen && speaker == a_refHandle;
		}

		// members
		ObjectRefHandle speaker;						// 14
		ObjectRefHandle lastSpeaker;					// 18
		BSTSmartPointer<BSInputEnableLayer> inputLayer; // 20
		REX::Float32 reLookTimer;						// 28
		REX::Float32 notInMenuTimer;					// 2C
		REX::Float32 restartMenuOnFocus;				// 30
		REX::Float32 menuStart;							// 34
		REX::Float32 buttonShowTimer;					// 38
		NiPoint3 centerPoint;							// 3C
		uint32_t numRefsInScene;						// 48
		bool menuOpen;									// 4C
		bool shutMenu;									// 4D
		bool canSkip;									// 4E
		bool shuttingDown;								// 4F
		bool menuSlow;									// 50
		bool doneFOV;									// 51
		bool leaveMenuOpen;								// 52
		bool showHelpButton;							// 53
		bool needEnterDialogueAction;					// 54
		bool allowInput;								// 55
		bool thirdPartyCameraReady;						// 56
		bool speechChallengeAlwaysSucceed;				// 57
		bool speechChallengeAlwaysFail;					// 58
		bool overSceneActor;							// 59
		bool forceCameraRotationStart;					// 5A
	};
	static_assert(sizeof(MenuTopicManager) == 0x60);
}
