#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint3.hpp"
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

namespace RE::MapMarker
{
	enum class MARKER_SCOPE : std::int32_t;
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
	class __declspec(novtable) PipboyMapData :
		public PipboyDataGroup,										  // 0x00
		public BSTEventSink<TravelMarkerStateChange::Event>,		  // 0x98
		public BSTEventSink<PlayerUpdateEvent>,						  // 0xA0
		public BSTEventSink<BGSActorCellEvent>,						  // 0xA8
		public BSTEventSink<TESQuestEvent::Event>,					  // 0xB0
		public BSTEventSink<PlayerCharacterQuestEvent::Event>,		  // 0xB8
		public BSTEventSink<CustomMarkerUpdate::Event>,				  // 0xC0
		public BSTEventSink<LocationMarkerArrayUpdate::Event>,		  // 0xC8
		public BSTEventSink<LocalMapCameraUpdate::Event>,			  // 0xD0
		public BSTEventSink<TESLocationClearedEvent>,				  // 0xD8
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent> // 0xE0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyMapData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyMapData;

		~PipboyMapData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<TravelMarkerStateChange::Event>)
		auto ProcessEvent(
			const TravelMarkerStateChange::Event& a_event,
			BSTEventSource<TravelMarkerStateChange::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerUpdateEvent>)
		auto ProcessEvent(
			const PlayerUpdateEvent& a_event,
			BSTEventSource<PlayerUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSActorCellEvent>)
		auto ProcessEvent(
			const BGSActorCellEvent& a_event,
			BSTEventSource<BGSActorCellEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESQuestEvent::Event>)
		auto ProcessEvent(
			const TESQuestEvent::Event& a_event,
			BSTEventSource<TESQuestEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		/// override (BSTEventSink<PlayerCharacterQuestEvent::Event>)
		auto ProcessEvent(
			const PlayerCharacterQuestEvent::Event& a_event,
			BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<CustomMarkerUpdate::Event>)
		auto ProcessEvent(
			const CustomMarkerUpdate::Event& a_event,
			BSTEventSource<CustomMarkerUpdate::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<LocationMarkerArrayUpdate::Event>)
		auto ProcessEvent(
			const LocationMarkerArrayUpdate::Event& a_event,
			BSTEventSource<LocationMarkerArrayUpdate::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<LocalMapCameraUpdate::Event>)
		auto ProcessEvent(
			const LocalMapCameraUpdate::Event& a_event,
			BSTEventSource<LocalMapCameraUpdate::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESLocationClearedEvent>)
		auto ProcessEvent(
			const TESLocationClearedEvent& a_event,
			BSTEventSource<TESLocationClearedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		auto GetTravelLocationRefr(TESFormID a_markerId) const -> ObjectRefHandle
		{
			using FuncType = decltype(&PipboyMapData::GetTravelLocationRefr);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyMapData::GetTravelLocationRefr);
			return std::invoke(FUNC, this, a_markerId);
		}

		void UpdateQuestMarkers(
			PipboyArray& a_questMarkers,
			BSTHashMap<ObjectRefHandle, PipboyObject*>& a_questMarkerMap,
			MapMarker::MARKER_SCOPE a_scope,
			REX::Float32 a_heightReference)
		{
			using FuncType = decltype(&PipboyMapData::UpdateQuestMarkers);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyMapData::UpdateQuestMarkers);
			std::invoke(FUNC, this, a_questMarkers, a_questMarkerMap, a_scope, a_heightReference);
		}

		// members
		PipboyObject* mapObject;												// 0xE8
		BSTHashMap<const MapMarkerData*, PipboyObject*> travelLocationsMarkers; // 0xF0
		BSTHashMap<std::uint32_t, ObjectRefHandle> travelLocationRefrHandles;	// 0x120
		BSTArray<PipboyObject*> doorMarkers;									// 0x150
		BSTArray<ObjectRefHandle> doorRefHandles;								// 0x168
		BSTHashMap<ObjectRefHandle, PipboyObject*> localQuestMarkers;			// 0x180
		BSTHashMap<ObjectRefHandle, PipboyObject*> worldQuestMarkers;			// 0x1B0
		NiPoint3 playerLastLocationPosition;									// 0x1E0
		NiPoint3 playerLastWorldPosition;										// 0x1EC
		PipboyObject* localPlayerMarker;										// 0x1F8
		PipboyObject* worldPlayerMarker;										// 0x200
		PipboyObject* localCustomMarker;										// 0x208
		PipboyObject* worldCustomMarker;										// 0x210
		PipboyObject* localPowerArmorMarker;									// 0x218
		PipboyObject* worldPowerArmorMarker;									// 0x220
		PipboyObject* worldMapExtents;											// 0x230
		PipboyObject* localMapExtents;											// 0x238
	};

	static_assert(sizeof(PipboyMapData) == 0x238);
}
