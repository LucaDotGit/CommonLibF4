#pragma once

#include "RE/A/ActorUtils_ArmorRatingVisitorBase.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::ActorUtils
{
	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ArmorRatingVisitor
		: public ArmorRatingVisitorBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorUtils__ArmorRatingVisitor };
		inline static constexpr auto VTABLE{ VTABLE::ActorUtils__ArmorRatingVisitor };

		// members
		BSScrapArray<TESBoundObject*> foundArmor; // 20
	};
	static_assert(sizeof(ArmorRatingVisitor) == 0x40);
}
