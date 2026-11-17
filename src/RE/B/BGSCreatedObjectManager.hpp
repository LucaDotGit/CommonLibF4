#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BGSCreatedObjectManager : public BSTSingletonSDM<BGSCreatedObjectManager> // 0x00
	{
	public:
		template <class T>
		class BSTCreatedObjectSmartPointerPolicy
		{
		public:
			static void Acquire(const T* a_ptr)
			{
				auto* objectManager = BGSCreatedObjectManager::GetSingleton();
				if (objectManager && a_ptr->IsCreated() && a_ptr->IsAlchemyItem()) {
					objectManager->IncrementRef(static_cast<const AlchemyItem*>(a_ptr));
				}
			}

			static void Release(const T* a_ptr)
			{
				auto* objectManager = BGSCreatedObjectManager::GetSingleton();
				if (objectManager && a_ptr->IsCreated() && a_ptr->IsAlchemyItem()) {
					objectManager->DecrementRef(static_cast<const AlchemyItem*>(a_ptr));
				}
			}
		};

		class CreatedMagicItemData
		{
		public:
			// members
			const MagicItem* createdItem; // 0x00
			std::uint32_t count;		  // 0x08
		};

		static_assert(sizeof(CreatedMagicItemData) == 0x10);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSCreatedObjectManager*
		{
			static const auto SINGLETON =
				REL::Relocation<BGSCreatedObjectManager**>{ID::BGSCreatedObjectManager::Singleton};
			return *SINGLETON;
		}

		void IncrementRef(const AlchemyItem* a_alchemyItem)
		{
			using FuncType = decltype(&BGSCreatedObjectManager::IncrementRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSCreatedObjectManager::IncrementRef);
			std::invoke(FUNC, this, a_alchemyItem);
		}

		void DecrementRef(const AlchemyItem* a_alchemyItem)
		{
			using FuncType = decltype(&BGSCreatedObjectManager::DecrementRef);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSCreatedObjectManager::DecrementRef);
			std::invoke(FUNC, this, a_alchemyItem);
		}

		// members
		BSTArray<CreatedMagicItemData> weaponEnchantments;	 // 0x08
		BSTArray<CreatedMagicItemData> armorEnchantments;	 // 0x20
		BSTHashMap<TESFormID, CreatedMagicItemData> potions; // 0x38
		BSTHashMap<TESFormID, CreatedMagicItemData> poisons; // 0x68
		BSTSet<const MagicItem*> queuedDeleteMagicItems;	 // 0x98
		mutable BSSpinLock dataLock;						 // 0xC8
	};

	static_assert(sizeof(BGSCreatedObjectManager) == 0xD0);

	template <class T>
	using CreatedObjectPointer = BSTSmartPointer<T, BGSCreatedObjectManager::BSTCreatedObjectSmartPointerPolicy>;
}
