#pragma once

#include "RE/B/BSResource_Location.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) GlobalLocations :
		public Location,						// 0x00
		public BSTSingletonSDM<GlobalLocations> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource____GlobalLocations;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource____GlobalLocations;

		class Entry
		{
		public:
			// members
			Entry* next;			// 0x00
			Location* location;		// 0x08
			std::uint32_t priority; // 0x10
		};

		static_assert(sizeof(Entry) == 0x18);

		~GlobalLocations() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(GlobalLocations);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> GlobalLocations*
		{
			static const auto SINGLETON =
				REL::Relocation<GlobalLocations**>{RE::ID::BSResource::GlobalLocations::Singleton};
			return *SINGLETON;
		}

		// members
		mutable BSSpinLock lock; // 0x14
		Entry* head;			 // 0x20
		Entry* pendingMount;	 // 0x28
		Entry* free;			 // 0x30
	};

	static_assert(sizeof(GlobalLocations) == 0x38);
}
