#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSResource/Location.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"

namespace RE::BSResource
{
	class __declspec(novtable) GlobalPaths
		: public Location,					  // 00
		  public BSTSingletonSDM<GlobalPaths> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource____GlobalPaths };
		inline static constexpr auto VTABLE{ VTABLE::BSResource____GlobalPaths };

		[[nodiscard]] static GlobalPaths* GetSingleton()
		{
			static REL::Relocation<GlobalPaths**> singleton{ REL::ID(210868) };
			return *singleton;
		}

		// members
		BSTArray<BSFixedString> names; // 18
		Location* rootLocation;		   // 30
	};
	static_assert(sizeof(GlobalPaths) == 0x38);
}
