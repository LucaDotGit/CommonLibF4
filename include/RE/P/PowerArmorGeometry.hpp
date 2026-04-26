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

	class __declspec(novtable) PowerArmorGeometry
		: public SimpleAnimationGraphManagerHolder,		 // 00
		  public BSTEventSink<PreloadPowerArmor::Event>, // 18
		  public BSTEventSink<ExitPowerArmor::Event>,	 // 20
		  public BSIntrusiveRefCounted,					 // 28
		  public BSTSingletonSDM<PowerArmorGeometry>	 // 2C
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PowerArmorGeometry };
		inline static constexpr auto VTABLE{ VTABLE::PowerArmorGeometry };

		~PowerArmorGeometry() override; // 00

		// override (SimpleAnimationGraphManagerHolder)
		void BackgroundTaskFinishedLoading() override; // 01

		// override (BSTEventSink<PreloadPowerArmor::Event>)
		BSEventNotifyControl ProcessEvent(const PreloadPowerArmor::Event& a_event, BSTEventSource<PreloadPowerArmor::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<ExitPowerArmor::Event>)
		BSEventNotifyControl ProcessEvent(const ExitPowerArmor::Event& a_event, BSTEventSource<ExitPowerArmor::Event>* a_eventSource) override; // 01

		[[nodiscard]] static PowerArmorGeometry* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<PowerArmorGeometry**>{ ID::PowerArmorGeometry::Singleton };
			return *SINGLETON;
		}

		void HidePipboyPAGeometry()
		{
			using FuncType = decltype(&PowerArmorGeometry::HidePipboyPAGeometry);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmorGeometry::HidePipboyPAGeometry };
			FUNC(this);
		}

		void ShowPipboyPAGeometry()
		{
			using FuncType = decltype(&PowerArmorGeometry::ShowPipboyPAGeometry);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerArmorGeometry::ShowPipboyPAGeometry };
			FUNC(this);
		}

		// members
		BSTValueEventSink<PipboyLightEvent> pipboySpotLightEvent;			 // 030
		BSTValueEventSink<PlayerAmmoCountEvent> nextAmmoCount;				 // 048
		BSTValueEventSink<PlayerWeaponReloadEvent> playerReloaded;			 // 068
		BSTValueEventSink<CurrentRadsDisplayMagnitude> radsCount;			 // 080
		BSTValueEventSink<CurrentRadsPercentOfLethal> radsPercentOfLethal;	 // 0A0
		BSTValueEventSink<CurrentRadiationSourceCount> radiationSourceCount; // 0C0
		TESImageSpaceModifier* paPipboyEffect;								 // 0E0
		NiPointer<NiNode> paDashDials;										 // 0E8
		NiPointer<NiNode> pipboyPAGlass;									 // 0F0
		NiAVObject* paDashLightSpot;										 // 0F8
		NiAVObject* paDashLightScope;										 // 100
		NiAVObject* paDashLightAux;											 // 108
		NiAVObject* paDash;													 // 110
		NiAVObject* plane;													 // 118
		NiAVObject* compass;												 // 120
		BSTArray<void*> queued3D;											 // 128
		HUDModes validHUDModes;												 // 140
		REX::Float32 radiationSmoother;										 // 160
		NiPointer<NiNode> dbHUDRain;										 // 168
		bool hudRain;														 // 170
		bool prevShouldBeVisible;											 // 171
		bool powerArmorEmergencyLightOn;									 // 172
		bool queueInit;														 // 173
		bool prevIsFirstPerson;												 // 174
		bool ammoDirty;														 // 175
		bool initialized;													 // 176
	};
	static_assert(sizeof(PowerArmorGeometry) == 0x178);
}
