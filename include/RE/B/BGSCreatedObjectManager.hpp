#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BGSCreatedObjectManager
		: public BSTSingletonSDM<BGSCreatedObjectManager> // 00
	{
	public:
		template <class T>
		class BSTCreatedObjectSmartPointerPolicy
		{
		public:
			static void Acquire(T* a_ptr)
			{
				auto* manager = BGSCreatedObjectManager::GetSingleton();
				if (manager && a_ptr->IsCreated() && a_ptr->IsAlchemyItem()) {
					manager->IncrementRef(static_cast<AlchemyItem*>(a_ptr));
				}
			}

			static void Release(T* a_ptr)
			{
				auto* manager = BGSCreatedObjectManager::GetSingleton();
				if (manager && a_ptr->IsCreated() && a_ptr->IsAlchemyItem()) {
					manager->DecrementRef(static_cast<AlchemyItem*>(a_ptr));
				}
			}
		};

		class CreatedMagicItemData
		{
		public:
			// members
			MagicItem* createdItem; // 00
			std::uint32_t count;	// 08
		};
		static_assert(sizeof(CreatedMagicItemData) == 0x10);

		[[nodiscard]] static BGSCreatedObjectManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSCreatedObjectManager**>{ ID::BGSCreatedObjectManager::Singleton };
			return *SINGLETON;
		}

		void IncrementRef(AlchemyItem* a_alchemyItem)
		{
			using FuncType = decltype(&BGSCreatedObjectManager::IncrementRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSCreatedObjectManager::IncrementRef };
			std::invoke(FUNC, this, a_alchemyItem);
		}

		void DecrementRef(AlchemyItem* a_alchemyItem)
		{
			using FuncType = decltype(&BGSCreatedObjectManager::DecrementRef);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSCreatedObjectManager::DecrementRef };
			std::invoke(FUNC, this, a_alchemyItem);
		}

		// members
		BSTArray<CreatedMagicItemData> weaponEnchantments;		 // 08
		BSTArray<CreatedMagicItemData> armorEnchantments;		 // 20
		BSTHashMap<std::uint32_t, CreatedMagicItemData> potions; // 38
		BSTHashMap<std::uint32_t, CreatedMagicItemData> poisons; // 68
		BSTSet<MagicItem*> queuedDeleteMagicItems;				 // 98
		mutable BSSpinLock dataLock;							 // C8
	};
	static_assert(sizeof(BGSCreatedObjectManager) == 0xD0);

	extern template class BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<AlchemyItem>;
	extern template class BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy<TESForm>;

	template <class T>
	using CreatedObjPtr = BSTSmartPointer<T, BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy>;
}
