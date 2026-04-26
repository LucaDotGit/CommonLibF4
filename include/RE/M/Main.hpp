#pragma once

#include "RE/B/BSPackedTaskQueue.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSaveDataSystemUtilityImage.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/ScrapHeap.hpp"

namespace RE
{
	class NiCamera;
	class PositionPlayerEvent;
	class SceneGraph;
	class TESPageCache;

	class Main
		: public BSTEventSink<PositionPlayerEvent>
	{
	public:
		~Main() override; // 00

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent& a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override; // 01

		[[nodiscard]] static Main* GetSingleton();

		[[nodiscard]] static NiPointer<SceneGraph>& GetWorldRootNode();
		[[nodiscard]] static NiPointer<SceneGraph>& GetMenuRootNode();
		[[nodiscard]] static bool& GetDoneNewOrLoadGame();
		[[nodiscard]] static bool& GetGameDataLoaded();
		[[nodiscard]] static bool& GetGameSystemsShouldUpdate();
		void SetCameraFOV(REX::Float32 a_fov);

		// members
		BSTArray<BSTPair<REX::Float32, ActorHandle>> sortedVisibleHighActors; // 08
		std::uint32_t localMapRenderDelay;									  // 20
		bool quitGame;														  // 24
		bool resetGame;														  // 25
		bool fullReset;														  // 26
		bool gameActive;													  // 27
		bool onIdle;														  // 28
		bool reloadContent;													  // 29
		bool freezeTime;													  // 2A
		bool freezeNextFrame;												  // 2B
		REX::W32::HWND hwnd;												  // 30
		void* instance;														  // 38
		std::uint32_t threadID;												  // 40
		ScrapHeap packedTaskHeap;											  // 48
		BSPackedTaskQueue taskQueue;										  // D8
		ScrapHeap secondaryPackedTaskHeap;									  // 108
		BSPackedTaskQueue secondaryTaskQueue;								  // 198
		TESPageCache* pageCache;											  // 1C8
		bool inMenuMode;													  // 1D0
		bool inDialog;														  // 1D1
		bool renderingMenuBG;												  // 1D2
		bool signOutPending;												  // 1D3
		std::array<BSSaveDataSystemUtilityImage, 3> saveDataBackgroundImages; // 1D8
		std::array<BSSaveDataSystemUtilityImage, 3> saveDataIconImages;		  // 220
	};
	static_assert(sizeof(Main) == 0x268);
}
