#pragma once

#include "RE/B/BSInputEventSingleUser.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/Q/QuickContainerStateEvent.hpp"

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::FavoriteMgr_Events
{
	class ComponentFavoriteEvent;
}

namespace RE::InventoryInterface
{
	class FavoriteChangedEvent;
}

namespace RE
{
	class QueuedFile;

	class __declspec(novtable) FavoritesManager
		: public BSInputEventSingleUser,									// 000
		  public BSTEventSink<BGSInventoryListEvent::Event>,				// 020
		  public BSTEventSink<InventoryInterface::FavoriteChangedEvent>,	// 028
		  public BSTSingletonSDM<FavoritesManager>,							// 030
		  public BSTEventSource<FavoriteMgr_Events::ComponentFavoriteEvent> // 038
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FavoritesManager };
		inline static constexpr auto VTABLE{ VTABLE::FavoritesManager };

		enum class FAVORITE_SLOT : std::int32_t
		{
			kLeft3 = 0,
			kLeft2 = 1,
			kLeft1 = 2,
			kRight1 = 3,
			kRight2 = 4,
			kRight3 = 5,
			kUp3 = 6,
			kUp2 = 7,
			kUp1 = 8,
			kDown1 = 9,
			kDown2 = 10,
			kDown3 = 11,

			kTotal = 12
		};

		~FavoritesManager() override; // 00

		GAME_HEAP_REDEFINE_NEW(FavoritesManager);

		[[nodiscard]] static FavoritesManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<FavoritesManager**>{ ID::FavoritesManager::Singleton };
			return *SINGLETON;
		}

		void ClearCurrentAmmoCount()
		{
			using FuncType = decltype(&FavoritesManager::ClearCurrentAmmoCount);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::FavoritesManager::ClearCurrentAmmoCount };
			FUNC(this);
		}

		[[nodiscard]] bool UseQuickkeyItem(std::uint32_t a_quickkeyIndex)
		{
			using FuncType = decltype(&FavoritesManager::UseQuickkeyItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::FavoritesManager::UseQuickkeyItem };
			return std::invoke(FUNC, this, a_quickkeyIndex);
		}

		// members
		std::array<TESBoundObject*, std::to_underlying(FAVORITE_SLOT::kTotal)> storedFavTypes;				// 090
		std::array<NiPointer<QueuedFile>, std::to_underlying(FAVORITE_SLOT::kTotal)> bufferedFavGeometries; // 0F0
		BSTSet<const BGSConstructibleObject*> favoriteMods;													// 150
		BSTHashMap<const TESBoundObject*, std::uint32_t> favoritedComponents;								// 180
		BSTSmallArray<std::int32_t, std::to_underlying(FAVORITE_SLOT::kTotal)> weaponLoadedAmmo;			// 1B0
		BSTValueEventSink<QuickContainerStateEvent> quickContainerMode;										// 1F0
		bool allowStimpakUse;																				// 2C8
	};
	static_assert(sizeof(FavoritesManager) == 0x2D0);
}
