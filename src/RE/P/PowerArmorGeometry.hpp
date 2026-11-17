#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/C/CurrentRadiationSourceCount.hpp"
#include "RE/C/CurrentRadsDisplayMagnitude.hpp"
#include "RE/C/CurrentRadsPercentOfLethal.hpp"
#include "RE/H/HUDModes.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/P/PipboyLightEvent.hpp"
#include "RE/P/PlayerAmmoCountEvent.hpp"
#include "RE/P/PlayerWeaponReloadEvent.hpp"
#include "RE/S/SimpleAnimationGraphManagerHolder.hpp"

namespace RE::ExitPowerArmor
{
	class Event;
}

namespace RE::PreloadPowerArmor
{
	class Event;
}

namespace RE
{
	class NiAVObject;
	class NiNode;

	class __declspec(novtable) PowerArmorGeometry :
		public SimpleAnimationGraphManagerHolder,	   // 0x00
		public BSTEventSink<PreloadPowerArmor::Event>, // 0x18
		public BSTEventSink<ExitPowerArmor::Event>,	   // 0x20
		public BSIntrusiveRefCounted,				   // 0x28
		public BSTSingletonSDM<PowerArmorGeometry>	   // 0x2C
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PowerArmorGeometry;
		inline static constexpr const auto& VTABLE = VTABLE::PowerArmorGeometry;

		~PowerArmorGeometry() override; // 0x00

		// override (SimpleAnimationGraphManagerHolder)
		void BackgroundTaskFinishedLoading() override; // 0x01

		// override (BSTEventSink<PreloadPowerArmor::Event>)
		auto ProcessEvent(
			const PreloadPowerArmor::Event& a_event,
			BSTEventSource<PreloadPowerArmor::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ExitPowerArmor::Event>)
		auto ProcessEvent(
			const ExitPowerArmor::Event& a_event,
			BSTEventSource<ExitPowerArmor::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> PowerArmorGeometry*
		{
			static const auto SINGLETON = REL::Relocation<PowerArmorGeometry**>(ID::PowerArmorGeometry::Singleton);
			return *SINGLETON;
		}

		void HidePipboyPAGeometry()
		{
			using FuncType = decltype(&PowerArmorGeometry::HidePipboyPAGeometry);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmorGeometry::HidePipboyPAGeometry);
			std::invoke(FUNC, this);
		}

		void ShowPipboyPAGeometry()
		{
			using FuncType = decltype(&PowerArmorGeometry::ShowPipboyPAGeometry);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PowerArmorGeometry::ShowPipboyPAGeometry);
			std::invoke(FUNC, this);
		}

		// members
		BSTValueEventSink<PipboyLightEvent> pipboySpotLightEvent;			 // 0x030
		BSTValueEventSink<PlayerAmmoCountEvent> nextAmmoCount;				 // 0x048
		BSTValueEventSink<PlayerWeaponReloadEvent> playerReloaded;			 // 0x068
		BSTValueEventSink<CurrentRadsDisplayMagnitude> radsCount;			 // 0x080
		BSTValueEventSink<CurrentRadsPercentOfLethal> radsPercentOfLethal;	 // 0x0A0
		BSTValueEventSink<CurrentRadiationSourceCount> radiationSourceCount; // 0x0C0
		TESImageSpaceModifier* paPipboyEffect;								 // 0x0E0
		NiPointer<NiNode> paDashDials;										 // 0x0E8
		NiPointer<NiNode> pipboyPAGlass;									 // 0x0F0
		NiAVObject* paDashLightSpot;										 // 0x0F8
		NiAVObject* paDashLightScope;										 // 0x100
		NiAVObject* paDashLightAux;											 // 0x108
		NiAVObject* paDash;													 // 0x110
		NiAVObject* plane;													 // 0x118
		NiAVObject* compass;												 // 0x120
		BSTArray<void*> queued3D;											 // 0x128
		HUDModes validHUDModes;												 // 0x140
		REX::Float32 radiationSmoother;										 // 0x160
		NiPointer<NiNode> dbHUDRain;										 // 0x168
		bool hudRain;														 // 0x170
		bool prevShouldBeVisible;											 // 0x171
		bool powerArmorEmergencyLightOn;									 // 0x172
		bool queueInit;														 // 0x173
		bool prevIsFirstPerson;												 // 0x174
		bool ammoDirty;														 // 0x175
		bool initialized;													 // 0x176
	};

	static_assert(sizeof(PowerArmorGeometry) == 0x178);
}
