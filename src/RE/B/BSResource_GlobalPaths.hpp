#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_Location.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) GlobalPaths :
		public Location,					// 0x00
		public BSTSingletonSDM<GlobalPaths> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource____GlobalPaths;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource____GlobalPaths;

		~GlobalPaths() override; // 0x00

		GAME_HEAP_REDEFINE_NEW(GlobalPaths);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> GlobalPaths*
		{
			static const auto SINGLETON = REL::Relocation<GlobalPaths**>(RE::ID::BSResource::GlobalPaths::Singleton);
			return *SINGLETON;
		}

		// members
		BSTArray<BSFixedString> names; // 0x18
		Location* rootLocation;		   // 0x30
	};

	static_assert(sizeof(GlobalPaths) == 0x38);
}
