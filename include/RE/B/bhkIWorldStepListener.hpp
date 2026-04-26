#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkNPCollisionObject;

	class __declspec(novtable) bhkIWorldStepListener
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkIWorldStepListener };
		inline static constexpr auto VTABLE{ VTABLE::bhkIWorldStepListener };

		virtual ~bhkIWorldStepListener(); // 00

		// members
		BSTArray<BSTArray<NiPointer<bhkNPCollisionObject>>>* deferredReleaseColObjs; // 08
	};
	static_assert(sizeof(bhkIWorldStepListener) == 0x10);
}
