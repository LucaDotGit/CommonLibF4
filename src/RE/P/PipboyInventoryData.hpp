#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/F/FormType.hpp"
#include "RE/I/InventoryInterface_Handle.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::ActorEquipManagerEvent
{
	class Event;
}

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE::BGSInventoryItemEvent
{
	class Event;
}

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::HolotapeStateChanged
{
	class Event;
}

namespace RE::InventoryInterface
{
	class FavoriteChangedEvent;
}

namespace RE::FavoriteMgr_Events
{
	class ComponentFavoriteEvent;
}

namespace RE::PerkValueEvents
{
	class PerkValueChangedEvent;
	class PerkEntryUpdatedEvent;
}

namespace RE::PlayerDifficultySettingChanged
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) PipboyInventoryData :
		public PipboyDataGroup,											 // 0x00
		public BSTEventSink<BGSInventoryListEvent::Event>,				 // 0x98
		public BSTEventSink<ActorEquipManagerEvent::Event>,				 // 0xA0
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>,	 // 0xA8
		public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>,	 // 0xB0
		public BSTEventSink<PerkValueEvents::PerkValueChangedEvent>,	 // 0xB8
		public BSTEventSink<InventoryInterface::FavoriteChangedEvent>,	 // 0xC0
		public BSTEventSink<HolotapeStateChanged::Event>,				 // 0xC8
		public BSTEventSink<BGSInventoryItemEvent::Event>,				 // 0xD0
		public BSTEventSink<FavoriteMgr_Events::ComponentFavoriteEvent>, // 0xD8
		public BSTEventSink<PlayerDifficultySettingChanged::Event>		 // 0xE0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyInventoryData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyInventoryData;

		enum class ENTRY_TYPE : std::int32_t
		{
			Int = 0,
			String = 1,
			Float = 2
		};

		enum class ITEM_ICON_ID : std::int32_t
		{
			None = 1,
			BasicPistol = 2,
			LaserPistol = 3,
			PlasmaPistol = 4,
			Shotgun = 5,
			BasicRifle = 6,
			AssaultRifle = 7,
			GaussRifle = 8,
			LaserMusket = 9,
			LaserRifle = 10,
			PlasmaRifle = 11,
			OneHandMelee = 12,
			TwoHandMelee = 13,
			HandToHandWeapon = 14,
			MissileLauncher = 15,
			Fatman = 16,
			Minigun = 17,
			GatlingLaser = 18,
			Cryolator = 19,
			Flamer = 20,
			FlareGun = 21,
			GammaGun = 22,
			JunkJet = 23,
			RailwayRifle = 24,
			Syringer = 25,
			Broadsider = 26,
			AlienBlaster = 27,
			Ripper = 28,
			Shishkebab = 29,
			ThrownWeapon = 30,
			ExplosiveMine = 31,
			BottlecapMine = 32,
			CryoMine = 33,
			CryoGrenade = 34,
			PlasmaMine = 35,
			PlasmaGrenade = 36,
			PulseMine = 37,
			PulseGrenade = 38,
			Molotov = 39,
			NukaGrenade = 40,
			RepairKit = 41,
			SurgeryKit = 42,
			Armor = 43,
			Gloves = 44,
			Helmet = 45,
			Book = 46,
			Clothes = 47,
			Ammo = 48,
			Adrenaline = 49,
			Disease = 50,
			Sleep = 51,
			Hunger = 52,
			Thirst = 53,
			Chems = 54,
			Stimpak = 55,
			Food = 56,
			Alcohol = 57,
			StealthBoy = 58,
			Unknown = 59,

			_Count = 60
		};

		enum class SORT_ON_FIELD : std::int32_t
		{
			Alphabetically = 0,
			Damage = 1,
			Rof = 2,
			Range = 3,
			Accuracy = 4,
			Value = 5,
			Weight = 6
		};

		class StackEntry
		{
		public:
			// members
			PipboyObject* linkedObject;					// 0x00
			InventoryInterface::Handle inventoryHandle; // 0x08
		};

		static_assert(sizeof(StackEntry) == 0x10);

		class ItemEntry
		{
		public:
			// members
			void* stackEntries; // 0x00 - To-Do: `BSTList<PipboyInventoryData::StackEntry*>`
		};

		static_assert(sizeof(ItemEntry) == 0x08);

		~PipboyInventoryData() override; // 0x00

		// override (PipboyDataGroup)
		auto ProcessEvent(
			const PipboyValueChangedEvent& a_event,
			BSTEventSource<PipboyValueChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		auto ProcessEvent(
			const BGSInventoryListEvent::Event& a_event,
			BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ActorEquipManagerEvent::Event>)
		auto ProcessEvent(
			const ActorEquipManagerEvent::Event& a_event,
			BSTEventSource<ActorEquipManagerEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>)
		auto ProcessEvent(
			const PerkValueEvents::PerkEntryUpdatedEvent& a_event,
			BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PerkValueEvents::PerkValueChangedEvent>)
		auto ProcessEvent(
			const PerkValueEvents::PerkValueChangedEvent& a_event,
			BSTEventSource<PerkValueEvents::PerkValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<InventoryInterface::FavoriteChangedEvent>)
		auto ProcessEvent(
			const InventoryInterface::FavoriteChangedEvent& a_event,
			BSTEventSource<InventoryInterface::FavoriteChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HolotapeStateChanged::Event>)
		auto ProcessEvent(
			const HolotapeStateChanged::Event& a_event,
			BSTEventSource<HolotapeStateChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSInventoryItemEvent::Event>)
		auto ProcessEvent(
			const BGSInventoryItemEvent::Event& a_event,
			BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<FavoriteMgr_Events::ComponentFavoriteEvent>)
		auto ProcessEvent(
			const FavoriteMgr_Events::ComponentFavoriteEvent& a_event,
			BSTEventSource<FavoriteMgr_Events::ComponentFavoriteEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		auto ProcessEvent(
			const PlayerDifficultySettingChanged::Event& a_event,
			BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x0C
		void DoClearData() override;		  // 0x0D
		void DoClearSink() override;		  // 0x0E

		void AddItemCardInfoEntry(const BSFixedStringCS* a_string, REX::Float32 a_value, PipboyArray& a_itemCardSection)
		{
			using FuncType = decltype(&PipboyInventoryData::AddItemCardInfoEntry);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::AddItemCardInfoEntry);
			std::invoke(FUNC, this, a_string, a_value, a_itemCardSection);
		}

		auto BaseAddItemCardInfoEntry(const BSFixedStringCS* a_string, PipboyArray* a_itemCardSection) -> PipboyObject*
		{
			using FuncType = decltype(&PipboyInventoryData::BaseAddItemCardInfoEntry);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::BaseAddItemCardInfoEntry);
			return std::invoke(FUNC, this, a_string, a_itemCardSection);
		}

		void PopulateItemCardInfo(
			const BGSInventoryItem* a_inventoryItem,
			const BGSInventoryItem::Stack* a_stack,
			PipboyObject* a_data)
		{
			using FuncType = decltype(&PipboyInventoryData::PopulateItemCardInfo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::PopulateItemCardInfo);
			std::invoke(FUNC, this, a_inventoryItem, a_stack, a_data);
		}

		void QueueItemCardRepopulate(FormType a_itemType)
		{
			using FuncType = decltype(&PipboyInventoryData::QueueItemCardRepopulate);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::QueueItemCardRepopulate);
			std::invoke(FUNC, this, a_itemType);
		}

		void RepopulateItemCardsOnSection(FormType a_itemType)
		{
			using FuncType = decltype(&PipboyInventoryData::RepopulateItemCardsOnSection);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::RepopulateItemCardsOnSection);
			std::invoke(FUNC, this, a_itemType);
		}

		void SortItems(SORT_ON_FIELD a_sortType)
		{
			using FuncType = decltype(&PipboyInventoryData::SortItems);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryData::SortItems);
			std::invoke(FUNC, this, a_sortType);
		}

		// members
		PipboyObject* inventoryObject;										   // 0x0E8
		BSTHashMap<std::uint32_t, PipboyInventoryData::ItemEntry> itemEntries; // 0x0F0
		BSTHashMap<const BGSComponent*, PipboyObject*> invComponents;		   // 0x120
		BSTArray<PipboyObject*> sortedItems;								   // 0x150
		BSTSet<FormType> queuedRepopulateCategories;						   // 0x168
	};

	static_assert(sizeof(PipboyInventoryData) == 0x198);
}
