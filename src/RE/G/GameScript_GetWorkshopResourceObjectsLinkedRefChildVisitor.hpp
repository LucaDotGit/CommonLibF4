#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::GameScript
{
	class GetWorkshopResourceObjectsLinkedRefChildVisitor
	{
	public:
		enum class OPTIONS : std::int32_t
		{
			AllObjects = 0,
			DamagedObjects = 1,
			UndamagedObjects = 2
		};

		// members
		BSScrapArray<TESObjectREFR*>* array;	 // 0x00
		ActorValueInfo* filter;					 // 0x08
		REX::Enum<OPTIONS, std::int32_t> option; // 0x10
	};

	static_assert(sizeof(GetWorkshopResourceObjectsLinkedRefChildVisitor) == 0x18);
}
