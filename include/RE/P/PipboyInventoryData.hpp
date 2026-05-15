#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/F/FormType.hpp"
#include "RE/I/InventoryInterface.hpp"
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
	class __declspec(novtable) PipboyInventoryData
		: public PipboyDataGroup,										   // 00
		  public BSTEventSink<BGSInventoryListEvent::Event>,			   // 98
		  public BSTEventSink<ActorEquipManagerEvent::Event>,			   // A0
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>,   // A8
		  public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>,	   // B0
		  public BSTEventSink<PerkValueEvents::PerkValueChangedEvent>,	   // B8
		  public BSTEventSink<InventoryInterface::FavoriteChangedEvent>,   // C0
		  public BSTEventSink<HolotapeStateChanged::Event>,				   // C8
		  public BSTEventSink<BGSInventoryItemEvent::Event>,			   // D0
		  public BSTEventSink<FavoriteMgr_Events::ComponentFavoriteEvent>, // D8
		  public BSTEventSink<PlayerDifficultySettingChanged::Event>	   // E0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyInventoryData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyInventoryData };

		enum class EntryType : std::int32_t
		{
			kInt = 0,
			kString = 1,
			kFloat = 2
		};

		enum class ITEM_ICON_ID : std::int32_t
		{
			kNone = 1,
			kBasicPistol = 2,
			kLaserPistol = 3,
			kPlasmaPistol = 4,
			kShotgun = 5,
			kBasicRifle = 6,
			kAssaultRifle = 7,
			kGaussRifle = 8,
			kLaserMusket = 9,
			kLaserRifle = 10,
			kPlasmaRifle = 11,
			kOneHandMelee = 12,
			kTwoHandMelee = 13,
			kHandToHandWeapon = 14,
			kMissileLauncher = 15,
			kFatman = 16,
			kMinigun = 17,
			kGatlingLaser = 18,
			kCryolator = 19,
			kFlamer = 20,
			kFlareGun = 21,
			kGammaGun = 22,
			kJunkJet = 23,
			kRailwayRifle = 24,
			kSyringer = 25,
			kBroadsider = 26,
			kAlienBlaster = 27,
			kRipper = 28,
			kShishkebab = 29,
			kThrownWeapon = 30,
			kExplosiveMine = 31,
			kBottlecapMine = 32,
			kCryoMine = 33,
			kCryoGrenade = 34,
			kPlasmaMine = 35,
			kPlasmaGrenade = 36,
			kPulseMine = 37,
			kPulseGrenade = 38,
			kMolotov = 39,
			kNukaGrenade = 40,
			kRepairKit = 41,
			kSurgeryKit = 42,
			kArmor = 43,
			kGloves = 44,
			kHelmet = 45,
			kBook = 46,
			kClothes = 47,
			kAmmo = 48,
			kAdrenaline = 49,
			kDisease = 50,
			kSleep = 51,
			kHunger = 52,
			kThirst = 53,
			kChems = 54,
			kStimpak = 55,
			kFood = 56,
			kAlcohol = 57,
			kStealthBoy = 58,
			kUnknown = 59,

			kTotal = 60
		};

		enum class SortOnField : std::int32_t
		{
			kAlphabetically = 0,
			kDamage = 1,
			kRof = 2,
			kRange = 3,
			kAccuracy = 4,
			kValue = 5,
			kWeight = 6
		};

		class StackEntry
		{
		public:
			// members
			PipboyObject* linkedObject;					// 00
			InventoryInterface::Handle inventoryHandle; // 08
		};
		static_assert(sizeof(StackEntry) == 0x10);

		class ItemEntry
		{
		public:
			// members
			void* stackEntries; // 00 - TODO: `BSTList<PipboyInventoryData::StackEntry*>`
		};
		static_assert(sizeof(ItemEntry) == 0x08);

		~PipboyInventoryData() override; // 00

		// override (PipboyDataGroup)
		BSEventNotifyControl ProcessEvent(const PipboyValueChangedEvent& a_event, BSTEventSource<PipboyValueChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		BSEventNotifyControl ProcessEvent(const BGSInventoryListEvent::Event& a_event, BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<ActorEquipManagerEvent::Event>)
		BSEventNotifyControl ProcessEvent(const ActorEquipManagerEvent::Event& a_event, BSTEventSource<ActorEquipManagerEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>)
		BSEventNotifyControl ProcessEvent(const PerkValueEvents::PerkEntryUpdatedEvent& a_event, BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PerkValueEvents::PerkValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const PerkValueEvents::PerkValueChangedEvent& a_event, BSTEventSource<PerkValueEvents::PerkValueChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<InventoryInterface::FavoriteChangedEvent>)
		BSEventNotifyControl ProcessEvent(const InventoryInterface::FavoriteChangedEvent& a_event, BSTEventSource<InventoryInterface::FavoriteChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HolotapeStateChanged::Event>)
		BSEventNotifyControl ProcessEvent(const HolotapeStateChanged::Event& a_event, BSTEventSource<HolotapeStateChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSInventoryItemEvent::Event>)
		BSEventNotifyControl ProcessEvent(const BGSInventoryItemEvent::Event& a_event, BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<FavoriteMgr_Events::ComponentFavoriteEvent>)
		BSEventNotifyControl ProcessEvent(const FavoriteMgr_Events::ComponentFavoriteEvent& a_event, BSTEventSource<FavoriteMgr_Events::ComponentFavoriteEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerDifficultySettingChanged::Event& a_event, BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource) override; // 01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0C
		void DoClearData() override;		  // 0D
		void DoClearSink() override;		  // 0E

		void AddItemCardInfoEntry(const BSFixedStringCS* a_string, REX::Float32 a_value, PipboyArray& a_itemCardSection)
		{
			using FuncType = decltype(&PipboyInventoryData::AddItemCardInfoEntry);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryData::AddItemCardInfoEntry };
			std::invoke(FUNC, this, a_string, a_value, a_itemCardSection);
		}

		PipboyObject* BaseAddItemCardInfoEntry(const BSFixedStringCS* a_string, PipboyArray* a_itemCardSection)
		{
			using FuncType = decltype(&PipboyInventoryData::BaseAddItemCardInfoEntry);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryData::BaseAddItemCardInfoEntry };
			return std::invoke(FUNC, this, a_string, a_itemCardSection);
		}

		void PopulateItemCardInfo(const BGSInventoryItem* a_inventoryItem, const BGSInventoryItem::Stack* a_stack, PipboyObject* a_data)
		{
			using FuncType = decltype(&PipboyInventoryData::PopulateItemCardInfo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryData::PopulateItemCardInfo };
			std::invoke(FUNC, this, a_inventoryItem, a_stack, a_data);
		}

		void RepopulateItemCardsOnSection(FormType itemTypeID)
		{
			using FuncType = decltype(&PipboyInventoryData::RepopulateItemCardsOnSection);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryData::RepopulateItemCardsOnSection };
			std::invoke(FUNC, this, itemTypeID);
		}

		// members
		PipboyObject* inventoryObject;										   // 0E8
		BSTHashMap<std::uint32_t, PipboyInventoryData::ItemEntry> itemEntries; // 0F0
		BSTHashMap<const BGSComponent*, PipboyObject*> invComponents;		   // 120
		BSTArray<PipboyObject*> sortedItems;								   // 150
		BSTSet<FormType> queuedRepopulateCategories;						   // 168
	};
	static_assert(sizeof(PipboyInventoryData) == 0x198);
}
