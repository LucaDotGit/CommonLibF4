#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkNPCollisionObject;

	class __declspec(novtable) bhkIWorldStepListener
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkIWorldStepListener;
		inline static constexpr const auto& VTABLE = VTABLE::bhkIWorldStepListener;

		virtual ~bhkIWorldStepListener(); // 0x00

		// members
		BSTArray<BSTArray<NiPointer<bhkNPCollisionObject>>>* deferredReleaseColObjs; // 0x08
	};

	static_assert(sizeof(bhkIWorldStepListener) == 0x10);
}
