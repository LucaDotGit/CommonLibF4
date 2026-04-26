#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTPoint.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/I/InventoryInterface.hpp"
#include "RE/I/IsPipboyActiveEvent.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRect.hpp"
#include "RE/P/PipboyRadioController.hpp"

namespace RE
{
	class BSTriShape;
	class IMenu;
	class BSAnimationGraphEvent;

	class __declspec(novtable) PipboyManager
		: public BSTEventSink<BSAnimationGraphEvent>, // 00
		  public BSInputEventUser,					  // 08
		  public BSTSingletonSDM<PipboyManager>		  // 18
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyManager };
		inline static constexpr auto VTABLE{ VTABLE::PipboyManager };

		enum class LOWER_REASON : std::int32_t
		{
			kNone = 0,
			kBook = 1,
			kPerkGrid = 2,
			kInspect = 3
		};

		enum class PipboyScreenEffectTriggerType : std::int32_t
		{
			kPipboyOpen = 0,
			kTabChange = 1,
			kCategoryChange = 2,
			kSmallTransition = 3,
			kMapChange = 4
		};

		~PipboyManager() override; // 00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override; // 01

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04
		void OnMouseMoveEvent(const MouseMoveEvent* a_event) override;	 // 06
		void OnButtonEvent(const ButtonEvent* a_event) override;		 // 08

		[[nodiscard]] static PipboyManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<PipboyManager**>{ ID::PipboyManager::Singleton };
			return *SINGLETON;
		}

		void AddMenuToPipboy(IMenu& a_menu, const NiRect<REX::Float32>& a_standVP, const NiRect<REX::Float32>& a_powerVP)
		{
			using FuncType = decltype(&PipboyManager::AddMenuToPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::AddMenuToPipboy };
			FUNC(this, a_menu, a_standVP, a_powerVP);
		}

		void ClosedownPipboy()
		{
			using FuncType = decltype(&PipboyManager::ClosedownPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::ClosedownPipboy };
			FUNC(this);
		}

		void DisablePipboyShader()
		{
			using FuncType = decltype(&PipboyManager::DisablePipboyShader);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::DisablePipboyShader };
			FUNC(this);
		}

		void EnablePipboyShader()
		{
			using FuncType = decltype(&PipboyManager::EnablePipboyShader);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::EnablePipboyShader };
			FUNC(this);
		}

		void InitPipboy()
		{
			using FuncType = decltype(&PipboyManager::InitPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::InitPipboy };
			FUNC(this);
		}

		void LowerPipboy(LOWER_REASON a_reason)
		{
			using FuncType = decltype(&PipboyManager::LowerPipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::LowerPipboy };
			FUNC(this, a_reason);
		}

		void OnPipboyCloseAnim()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyCloseAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyCloseAnim };
			FUNC(this);
		}

		void OnPipboyCloseAnimFailed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyCloseAnimFailed);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyCloseAnimFailed };
			FUNC(this);
		}

		void OnPipboyClosed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyClosed);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyClosed };
			FUNC(this);
		}

		void OnPipboyOpenAnim()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyOpenAnim };
			FUNC(this);
		}

		void OnPipboyOpenAnimFailed()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpenAnimFailed);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyOpenAnimFailed };
			FUNC(this);
		}

		void OnPipboyOpened()
		{
			using FuncType = decltype(&PipboyManager::OnPipboyOpened);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::OnPipboyOpened };
			FUNC(this);
		}

		void PlayItemAnimOnClose()
		{
			using FuncType = decltype(&PipboyManager::PlayItemAnimOnClose);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayItemAnimOnClose };
			FUNC(this);
		}

		void PlayPipboyCloseAnim(bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyCloseAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayPipboyCloseAnim };
			FUNC(this, a_noAnim);
		}

		void PlayPipboyGenericOpenAnim(const BSFixedString& a_menu, const BSFixedString& a_anim, bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyGenericOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayPipboyGenericOpenAnim };
			FUNC(this, a_menu, a_anim, a_noAnim);
		}

		void PlayPipboyLoadHolotapeAnim(BGSNote* a_holotape, bool a_noAnim)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyLoadHolotapeAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayPipboyLoadHolotapeAnim };
			FUNC(this, a_holotape, a_noAnim);
		}

		void PlayPipboyOpenAnim(const BSFixedString& a_menuName)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyOpenAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayPipboyOpenAnim };
			FUNC(this, a_menuName);
		}

		void PlayPipboyOpenTerminalAnim(BGSTerminal* a_terminal)
		{
			using FuncType = decltype(&PipboyManager::PlayPipboyOpenTerminalAnim);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::PlayPipboyOpenTerminalAnim };
			FUNC(this, a_terminal);
		}

		void ProcessLoweringReason()
		{
			using FuncType = decltype(&PipboyManager::ProcessLoweringReason);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::ProcessLoweringReason };
			FUNC(this);
		}

		bool QPipboyActive()
		{
			using FuncType = decltype(&PipboyManager::QPipboyActive);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::QPipboyActive };
			return std::invoke(FUNC, this);
		}

		void RaisePipboy()
		{
			using FuncType = decltype(&PipboyManager::RaisePipboy);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::RaisePipboy };
			FUNC(this);
		}

		void RefreshPipboyRenderSurface()
		{
			using FuncType = decltype(&PipboyManager::RefreshPipboyRenderSurface);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::RefreshPipboyRenderSurface };
			FUNC(this);
		}

		void StartAnimationGraphListening()
		{
			using FuncType = decltype(&PipboyManager::StartAnimationGraphListening);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::StartAnimationGraphListening };
			FUNC(this);
		}

		void StopAnimationGraphListening()
		{
			using FuncType = decltype(&PipboyManager::StopAnimationGraphListening);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::StopAnimationGraphListening };
			FUNC(this);
		}

		void UpdateCursorConstraint(bool a_enable)
		{
			using FuncType = decltype(&PipboyManager::UpdateCursorConstraint);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyManager::UpdateCursorConstraint };
			FUNC(this, a_enable);
		}

		// members
		BSSoundHandle pipboyHumSound;						   // 01C
		BSTPoint2<REX::Float32> inputVector;				   // 024
		BSTPoint2<REX::Float32> newInput;					   // 02C
		NiPointer<BSTriShape> debugModeGeom;				   // 038
		Inventory3DManager inv3DModelManager;				   // 040
		BGSNote* holotapeToLoad;							   // 180
		BGSTerminal* terminalToLoad;						   // 188
		BSFixedString menuToOpen;							   // 190
		BSFixedString openAnimEvent;						   // 198
		BSFixedString closeAnimEvent;						   // 1A0
		REX::Enum<LOWER_REASON, std::int32_t> loweringReason;  // 1A8
		PipboyRadioController radioController;				   // 1AC
		TESBoundObject* itemAnimOnClose;					   // 1B0
		ObjectRefHandle fastTravelLocation;					   // 1B8
		InventoryInterface::Handle inspectRequestItem;		   // 1BC
		std::uint32_t inspectRequestStack;					   // 1C0
		bool pipboyExamineMode;								   // 1C4
		bool pipboyExamineDirtyFlag;						   // 1C5
		bool pipboyOpening;									   // 1C6
		bool pipboyClosing;									   // 1C7
		BSTValueEventSource<IsPipboyActiveEvent> pipboyActive; // 1C8
		bool ignoreOpeningFlag;								   // 1E0
		bool autoSaveOnClose;								   // 1E1
		bool pipboyMenuCloseQueued;							   // 1E2
		bool pipboyRaising;									   // 1E3
		bool wasMotionBlurActive;							   // 1E4
		bool wasPipboyLightActive;							   // 1E5
	};
	static_assert(sizeof(PipboyManager) == 0x1F0);
}
