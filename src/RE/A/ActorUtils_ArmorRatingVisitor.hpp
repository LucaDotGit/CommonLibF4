#pragma once

#include "RE/A/ActorUtils_ArmorRatingVisitorBase.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::ActorUtils
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) ArmorRatingVisitor : public ArmorRatingVisitorBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorUtils__ArmorRatingVisitor;
		inline static constexpr const auto& VTABLE = VTABLE::ActorUtils__ArmorRatingVisitor;

		ArmorRatingVisitor()
		{
			REL::EmplaceVtable(this);
		}

		// members
		BSScrapArray<TESBoundObject*> foundArmor; // 0x20
	};

	static_assert(sizeof(ArmorRatingVisitor) == 0x40);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
