#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTPoint2.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/I/InventoryInterface_Handle.hpp"
#include "RE/I/IsPipboyActiveEvent.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRect.hpp"
#include "RE/P/PipboyRadioController.hpp"

namespace RE
{
	class BSTriShape;
	class IMenu;
	class BSAnimationGraphEvent;

	class __declspec(novtable) PipboyManager :
		public BSTEventSink<BSAnimationGraphEvent>, // 0x00
		public BSInputEventUser,					// 0x08
		public BSTSingletonSDM<PipboyManager>		// 0x18
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyManager;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyManager;

		enum class LOWER_REASON : std::int32_t
		{
			None = 0,
			Book = 1,
			PerkGrid = 2,
			Inspect = 3
		};

		enum class PipboyScreenEffectTriggerType : std::int32_t
		{
			PipboyOpen = 0,
			TabChange = 1,
			CategoryChange = 2,
			SmallTransition = 3,
			MapChange = 4
		};

		~PipboyManager() override; // 0x00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		auto ProcessEvent(
			const BSAnimationGraphEvent& a_event,
			BSTEventSource<BSAnimationGraphEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnMouseMoveEvent(const MouseMoveEvent* a_event) override;		// 0x06
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		[[nodiscard]]
		static auto GetSingleton() noexcept -> PipboyManager*
		{
			static const auto SINGLETON = REL::Relocation<PipboyManager**>(ID::PipboyManager::Singleton);
			return *SINGLETON;
		}

		void AddMenuToPipboy(IMenu& a_menu, const NiRectF& a_standVP, const NiRectF& a_powerVP)
		{
			using FuncType = decltype(&PipboyManager::AddMenuToPipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::AddMenuToPipboy);
			std::invoke(FUNC, this, a_menu, a_standVP, a_powerVP);
		}

		void ClosedownPipboy()
		{
			using FuncType = decltype(&PipboyManager::ClosedownPipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::ClosedownPipboy);
			std::invoke(FUNC, this);
		}

		void DisablePipboyShader()
		{
			using FuncType = decltype(&PipboyManager::DisablePipboyShader);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::DisablePipboyShader);
			std::invoke(FUNC, this);
		}

		void EnablePipboyShader()
		{
			using FuncType = decltype(&PipboyManager::EnablePipboyShader);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::EnablePipboyShader);
			std::invoke(FUNC, this);
		}

		void InitPipboy()
		{
			using FuncType = decltype(&PipboyManager::InitPipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::InitPipboy);
			std::invoke(FUNC, this);
		}

		void LowerPipboy(LOWER_REASON a_reason)
		{
			using FuncType = decltype(&PipboyManager::LowerPipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::LowerPipboy);
			std::invoke(FUNC, this, a_reason);
		}

		void OnPipboyCloseAnim()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyCloseAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyCloseAnim);
			std::invoke(FUNC, this);
		}

		void OnPipboyCloseAnimFailed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyCloseAnimFailed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyCloseAnimFailed);
			std::invoke(FUNC, this);
		}

		void OnPipboyClosed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyClosed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyClosed);
			std::invoke(FUNC, this);
		}

		void OnPipboyOpenAnim()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyOpenAnim);
			std::invoke(FUNC, this);
		}

		void OnPipboyOpenAnimFailed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpenAnimFailed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyOpenAnimFailed);
			std::invoke(FUNC, this);
		}

		void OnPipboyOpened()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpened);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::OnPipboyOpened);
			std::invoke(FUNC, this);
		}

		void PlayItemAnimOnClose()
		{
			using FuncType = decltype(&PipboyManager::PlayItemAnimOnClose);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayItemAnimOnClose);
			std::invoke(FUNC, this);
		}

		void PlayPipboyCloseAnim(bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyCloseAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayPipboyCloseAnim);
			std::invoke(FUNC, this, a_noAnim);
		}

		void PlayPipboyGenericOpenAnim(const BSFixedString& a_menu, const BSFixedString& a_anim, bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyGenericOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayPipboyGenericOpenAnim);
			std::invoke(FUNC, this, a_menu, a_anim, a_noAnim);
		}

		void PlayPipboyLoadHolotapeAnim(BGSNote* a_holotape, bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyLoadHolotapeAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayPipboyLoadHolotapeAnim);
			std::invoke(FUNC, this, a_holotape, a_noAnim);
		}

		void PlayPipboyOpenAnim(const BSFixedString& a_menuName)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayPipboyOpenAnim);
			std::invoke(FUNC, this, a_menuName);
		}

		void PlayPipboyOpenTerminalAnim(BGSTerminal* a_terminal)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyOpenTerminalAnim);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::PlayPipboyOpenTerminalAnim);
			std::invoke(FUNC, this, a_terminal);
		}

		void ProcessLoweringReason()
		{
			using FuncType = decltype(&PipboyManager::ProcessLoweringReason);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::ProcessLoweringReason);
			std::invoke(FUNC, this);
		}

		auto QPipboyActive() -> bool
		{
			using FuncType = decltype(&PipboyManager::QPipboyActive);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::QPipboyActive);
			return std::invoke(FUNC, this);
		}

		void RaisePipboy()
		{
			using FuncType = decltype(&PipboyManager::RaisePipboy);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::RaisePipboy);
			std::invoke(FUNC, this);
		}

		void RefreshPipboyRenderSurface()
		{
			using FuncType = decltype(&PipboyManager::RefreshPipboyRenderSurface);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::RefreshPipboyRenderSurface);
			std::invoke(FUNC, this);
		}

		void StartAnimationGraphListening()
		{
			using FuncType = decltype(&PipboyManager::StartAnimationGraphListening);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::StartAnimationGraphListening);
			std::invoke(FUNC, this);
		}

		void StopAnimationGraphListening()
		{
			using FuncType = decltype(&PipboyManager::StopAnimationGraphListening);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::StopAnimationGraphListening);
			std::invoke(FUNC, this);
		}

		void UpdateCursorConstraint(bool a_enable)
		{
			using FuncType = decltype(&PipboyManager::UpdateCursorConstraint);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyManager::UpdateCursorConstraint);
			std::invoke(FUNC, this, a_enable);
		}

		// members
		BSSoundHandle pipboyHumSound;						   // 0x01C
		BSTPoint2F inputVector;								   // 0x024
		BSTPoint2F newInput;								   // 0x02C
		NiPointer<BSTriShape> debugModeGeom;				   // 0x038
		Inventory3DManager inv3DModelManager;				   // 0x040
		BGSNote* holotapeToLoad;							   // 0x180
		BGSTerminal* terminalToLoad;						   // 0x188
		BSFixedString menuToOpen;							   // 0x190
		BSFixedString openAnimEvent;						   // 0x198
		BSFixedString closeAnimEvent;						   // 0x1A0
		REX::Enum<LOWER_REASON, std::int32_t> loweringReason;  // 0x1A8
		PipboyRadioController radioController;				   // 0x1AC
		TESBoundObject* itemAnimOnClose;					   // 0x1B0
		ObjectRefHandle fastTravelLocation;					   // 0x1B8
		InventoryInterface::Handle inspectRequestItem;		   // 0x1BC
		std::uint32_t inspectRequestStack;					   // 0x1C0
		bool pipboyExamineMode;								   // 0x1C4
		bool pipboyExamineDirtyFlag;						   // 0x1C5
		bool pipboyOpening;									   // 0x1C6
		bool pipboyClosing;									   // 0x1C7
		BSTValueEventSource<IsPipboyActiveEvent> pipboyActive; // 0x1C8
		bool ignoreOpeningFlag;								   // 0x1E0
		bool autoSaveOnClose;								   // 0x1E1
		bool pipboyMenuCloseQueued;							   // 0x1E2
		bool pipboyRaising;									   // 0x1E3
		bool wasMotionBlurActive;							   // 0x1E4
		bool wasPipboyLightActive;							   // 0x1E5
	};

	static_assert(sizeof(PipboyManager) == 0x1F0);
}
