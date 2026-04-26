#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class BGSActorCellEvent;
	class MapMarkerData;
	class PlayerUpdateEvent;
	class TESLocationClearedEvent;
}

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE::CustomMarkerUpdate
{
	class Event;
}

namespace RE::LocalMapCameraUpdate
{
	class Event;
}

namespace RE::LocationMarkerArrayUpdate
{
	class Event;
}

namespace RE::PlayerCharacterQuestEvent
{
	class Event;
}

namespace RE::TESQuestEvent
{
	class Event;
}

namespace RE::TravelMarkerStateChange
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) PipboyMapData
		: public PipboyDataGroup,										// 00
		  public BSTEventSink<TravelMarkerStateChange::Event>,			// 98
		  public BSTEventSink<PlayerUpdateEvent>,						// A0
		  public BSTEventSink<BGSActorCellEvent>,						// A8
		  public BSTEventSink<TESQuestEvent::Event>,					// B0
		  public BSTEventSink<PlayerCharacterQuestEvent::Event>,		// B8
		  public BSTEventSink<CustomMarkerUpdate::Event>,				// C0
		  public BSTEventSink<LocationMarkerArrayUpdate::Event>,		// C8
		  public BSTEventSink<LocalMapCameraUpdate::Event>,				// D0
		  public BSTEventSink<TESLocationClearedEvent>,					// D8
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent> // E0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyMapData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyMapData };

		~PipboyMapData() override; // 00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<TravelMarkerStateChange::Event>)
		BSEventNotifyControl ProcessEvent(const TravelMarkerStateChange::Event& a_event, BSTEventSource<TravelMarkerStateChange::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const PlayerUpdateEvent& a_event, BSTEventSource<PlayerUpdateEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSActorCellEvent>)
		BSEventNotifyControl ProcessEvent(const BGSActorCellEvent& a_event, BSTEventSource<BGSActorCellEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESQuestEvent::Event>)
		BSEventNotifyControl ProcessEvent(const TESQuestEvent::Event& a_event, BSTEventSource<TESQuestEvent::Event>* a_eventSource) override; // 01

		/// override (BSTEventSink<PlayerCharacterQuestEvent::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerCharacterQuestEvent::Event& a_event, BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<CustomMarkerUpdate::Event>)
		BSEventNotifyControl ProcessEvent(const CustomMarkerUpdate::Event& a_event, BSTEventSource<CustomMarkerUpdate::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<LocationMarkerArrayUpdate::Event>)
		BSEventNotifyControl ProcessEvent(const LocationMarkerArrayUpdate::Event& a_event, BSTEventSource<LocationMarkerArrayUpdate::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<LocalMapCameraUpdate::Event>)
		BSEventNotifyControl ProcessEvent(const LocalMapCameraUpdate::Event& a_event, BSTEventSource<LocalMapCameraUpdate::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<TESLocationClearedEvent>)
		BSEventNotifyControl ProcessEvent(const TESLocationClearedEvent& a_event, BSTEventSource<TESLocationClearedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01

		// members
		PipboyObject* mapObject;												// E8
		BSTHashMap<const MapMarkerData*, PipboyObject*> travelLocationsMarkers; // F0
		BSTHashMap<std::uint32_t, ObjectRefHandle> travelLocationRefrHandles;	// 120
		BSTArray<PipboyObject*> doorMarkers;									// 150
		BSTArray<ObjectRefHandle> doorRefHandles;								// 168
		BSTHashMap<ObjectRefHandle, PipboyObject*> localQuestMarkers;			// 180
		BSTHashMap<ObjectRefHandle, PipboyObject*> worldQuestMarkers;			// 1B0
		NiPoint3 playerLastLocationPosition;									// 1E0
		NiPoint3 playerLastWorldPosition;										// 1EC
		PipboyObject* localPlayerMarker;										// 1F8
		PipboyObject* worldPlayerMarker;										// 200
		PipboyObject* localCustomMarker;										// 208
		PipboyObject* worldCustomMarker;										// 210
		PipboyObject* localPowerArmorMarker;									// 218
		PipboyObject* worldPowerArmorMarker;									// 220
		PipboyObject* worldMapExtents;											// 230
		PipboyObject* localMapExtents;											// 238
	};
	static_assert(sizeof(PipboyMapData) == 0x238);
}
