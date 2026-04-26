#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_Location.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) GlobalPaths
		: public Location,					  // 00
		  public BSTSingletonSDM<GlobalPaths> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource____GlobalPaths };
		inline static constexpr auto VTABLE{ VTABLE::BSResource____GlobalPaths };

		~GlobalPaths() override; // 00

		GAME_HEAP_REDEFINE_NEW(GlobalPaths);

		[[nodiscard]] static GlobalPaths* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<GlobalPaths**>{ RE::ID::BSResource::GlobalPaths::Singleton };
			return *SINGLETON;
		}

		// members
		BSTArray<BSFixedString> names; // 18
		Location* rootLocation;		   // 30
	};
	static_assert(sizeof(GlobalPaths) == 0x38);
}
