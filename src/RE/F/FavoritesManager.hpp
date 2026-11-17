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

	class __declspec(novtable) FavoritesManager :
		public BSInputEventSingleUser,									  // 0x000
		public BSTEventSink<BGSInventoryListEvent::Event>,				  // 0x020
		public BSTEventSink<InventoryInterface::FavoriteChangedEvent>,	  // 0x028
		public BSTSingletonSDM<FavoritesManager>,						  // 0x030
		public BSTEventSource<FavoriteMgr_Events::ComponentFavoriteEvent> // 0x038
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FavoritesManager;
		inline static constexpr const auto& VTABLE = VTABLE::FavoritesManager;

		enum class FAVORITE_SLOT : std::int32_t
		{
			Left3 = 0,
			Left2 = 1,
			Left1 = 2,
			Right1 = 3,
			Right2 = 4,
			Right3 = 5,
			Up3 = 6,
			Up2 = 7,
			Up1 = 8,
			Down1 = 9,
			Down2 = 10,
			Down3 = 11,

			_Count = 12
		};

		~FavoritesManager() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(FavoritesManager);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> FavoritesManager*
		{
			static const auto SINGLETON = REL::Relocation<FavoritesManager**>(ID::FavoritesManager::Singleton);
			return *SINGLETON;
		}

		void ClearCurrentAmmoCount()
		{
			using FuncType = decltype(&FavoritesManager::ClearCurrentAmmoCount);
			static const auto FUNC = REL::Relocation<FuncType>(ID::FavoritesManager::ClearCurrentAmmoCount);
			std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto UseQuickkeyItem(std::uint32_t a_quickkeyIndex) -> bool
		{
			using FuncType = decltype(&FavoritesManager::UseQuickkeyItem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::FavoritesManager::UseQuickkeyItem);
			return std::invoke(FUNC, this, a_quickkeyIndex);
		}

		// members
		std::array<TESBoundObject*, std::to_underlying(FAVORITE_SLOT::_Count)> storedFavTypes;				// 0x090
		std::array<NiPointer<QueuedFile>, std::to_underlying(FAVORITE_SLOT::_Count)> bufferedFavGeometries; // 0x0F0
		BSTSet<const BGSConstructibleObject*> favoriteMods;													// 0x150
		BSTHashMap<const TESBoundObject*, std::uint32_t> favoritedComponents;								// 0x180
		BSTSmallArray<std::int32_t, std::to_underlying(FAVORITE_SLOT::_Count)> weaponLoadedAmmo;			// 0x1B0
		BSTValueEventSink<QuickContainerStateEvent> quickContainerMode;										// 0x1F0
		bool allowStimpakUse;																				// 0x2C8
	};

	static_assert(sizeof(FavoritesManager) == 0x2D0);
}
