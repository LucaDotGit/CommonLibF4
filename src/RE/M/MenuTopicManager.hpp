#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
	class PositionPlayerEvent;

	class __declspec(novtable) MenuTopicManager :
		public BSTEventSink<MenuOpenCloseEvent>,  // 0x00
		public BSTEventSink<PositionPlayerEvent>, // 0x08
		public BSTSingletonSDM<MenuTopicManager>  // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MenuTopicManager;
		inline static constexpr const auto& VTABLE = VTABLE::MenuTopicManager;

		[[nodiscard]]
		static auto GetSingleton() noexcept -> MenuTopicManager*
		{
			static const auto SINGLETON = REL::Relocation<MenuTopicManager**>(ID::MenuTopicManager::Singleton);
			return *SINGLETON;
		}

		[[nodiscard]]
		auto IsCurrentSpeaker(const ObjectRefHandle& a_refHandle) const noexcept -> bool
		{
			return menuOpen && speaker == a_refHandle;
		}

		// members
		ObjectRefHandle speaker;						// 0x14
		ObjectRefHandle lastSpeaker;					// 0x18
		BSTSmartPointer<BSInputEnableLayer> inputLayer; // 0x20
		REX::Float32 reLookTimer;						// 0x28
		REX::Float32 notInMenuTimer;					// 0x2C
		REX::Float32 restartMenuOnFocus;				// 0x30
		REX::Float32 menuStart;							// 0x34
		REX::Float32 buttonShowTimer;					// 0x38
		NiPoint3 centerPoint;							// 0x3C
		uint32_t numRefsInScene;						// 0x48
		bool menuOpen;									// 0x4C
		bool shutMenu;									// 0x4D
		bool canSkip;									// 0x4E
		bool shuttingDown;								// 0x4F
		bool menuSlow;									// 0x50
		bool doneFOV;									// 0x51
		bool leaveMenuOpen;								// 0x52
		bool showHelpButton;							// 0x53
		bool needEnterDialogueAction;					// 0x54
		bool allowInput;								// 0x55
		bool thirdPartyCameraReady;						// 0x56
		bool speechChallengeAlwaysSucceed;				// 0x57
		bool speechChallengeAlwaysFail;					// 0x58
		bool overSceneActor;							// 0x59
		bool forceCameraRotationStart;					// 0x5A
	};

	static_assert(sizeof(MenuTopicManager) == 0x60);
}
