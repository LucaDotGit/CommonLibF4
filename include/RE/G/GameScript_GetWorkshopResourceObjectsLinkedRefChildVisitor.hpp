#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::GameScript
{
	class GetWorkshopResourceObjectsLinkedRefChildVisitor
	{
	public:
		enum class OPTIONS : std::int32_t
		{
			kAllObjects = 0,
			kDamagedObjects = 1,
			kUndamagedObjects = 2
		};

		// members
		BSScrapArray<TESObjectREFR*>* array;	 // 00
		ActorValueInfo* filter;					 // 08
		REX::Enum<OPTIONS, std::int32_t> option; // 10
	};
	static_assert(sizeof(GetWorkshopResourceObjectsLinkedRefChildVisitor) == 0x18);
}
