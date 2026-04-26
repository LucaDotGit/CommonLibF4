#pragma once

#include "RE/B/BSResource_Location.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) GlobalLocations
		: public Location,						  // 00
		  public BSTSingletonSDM<GlobalLocations> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource____GlobalLocations };
		inline static constexpr auto VTABLE{ VTABLE::BSResource____GlobalLocations };

		class Entry
		{
		public:
			// members
			Entry* next;			// 00
			Location* location;		// 08
			std::uint32_t priority; // 10
		};
		static_assert(sizeof(Entry) == 0x18);

		~GlobalLocations() override; // 00

		GAME_HEAP_REDEFINE_NEW(GlobalLocations);

		[[nodiscard]] static GlobalLocations* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<GlobalLocations**>{ RE::ID::BSResource::GlobalLocations::Singleton };
			return *SINGLETON;
		}

		// members
		mutable BSSpinLock lock; // 14
		Entry* head;			 // 20
		Entry* pendingMount;	 // 28
		Entry* free;			 // 30
	};
	static_assert(sizeof(GlobalLocations) == 0x38);
}
