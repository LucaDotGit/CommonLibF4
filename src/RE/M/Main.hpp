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
	class NiNode;
	class PositionPlayerEvent;
	class SceneGraph;
	class TESPageCache;

	class Main : public BSTEventSink<PositionPlayerEvent>
	{
	public:
		~Main() override; // 0x00

		// override (BSTEventSink<PositionPlayerEvent>)
		auto ProcessEvent(
			const PositionPlayerEvent& a_event,
			BSTEventSource<PositionPlayerEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> Main*;

		[[nodiscard]]
		static auto GetWorldRootNode() noexcept -> NiPointer<SceneGraph>&;
		[[nodiscard]]
		static auto GetMenuRootNode() noexcept -> NiPointer<SceneGraph>&;
		[[nodiscard]]
		static auto GetLandLODNode() noexcept -> NiNode*&;
		[[nodiscard]]
		static auto GetObjectLODNode() noexcept -> NiNode*&;
		[[nodiscard]]
		static auto GetDoneNewOrLoadGame() noexcept -> bool&;
		[[nodiscard]]
		static auto GetGameDataLoaded() noexcept -> bool&;
		[[nodiscard]]
		static auto GetGameSystemsShouldUpdate() noexcept -> bool&;
		void SetCameraFOV(REX::Float32 a_fov);

		// members
		BSTArray<BSTPair<REX::Float32, ActorHandle>> sortedVisibleHighActors; // 0x08
		std::uint32_t localMapRenderDelay;									  // 0x20
		bool quitGame;														  // 0x24
		bool resetGame;														  // 0x25
		bool fullReset;														  // 0x26
		bool gameActive;													  // 0x27
		bool onIdle;														  // 0x28
		bool reloadContent;													  // 0x29
		bool freezeTime;													  // 0x2A
		bool freezeNextFrame;												  // 0x2B
		REX::W32::HWND hwnd;												  // 0x30
		void* instance;														  // 0x38
		std::uint32_t threadID;												  // 0x40
		ScrapHeap packedTaskHeap;											  // 0x48
		BSPackedTaskQueue taskQueue;										  // 0xD8
		ScrapHeap secondaryPackedTaskHeap;									  // 0x108
		BSPackedTaskQueue secondaryTaskQueue;								  // 0x198
		TESPageCache* pageCache;											  // 0x1C8
		bool inMenuMode;													  // 0x1D0
		bool inDialog;														  // 0x1D1
		bool renderingMenuBG;												  // 0x1D2
		bool signOutPending;												  // 0x1D3
		std::array<BSSaveDataSystemUtilityImage, 3> saveDataBackgroundImages; // 0x1D8
		std::array<BSSaveDataSystemUtilityImage, 3> saveDataIconImages;		  // 0x220
	};

	static_assert(sizeof(Main) == 0x268);
}
