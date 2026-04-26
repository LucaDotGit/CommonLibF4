#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkNPCollisionObject.hpp"
#include "RE/N/NiExtraData.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) bhkNPCollisionObjectUnlinked
		: public bhkNPCollisionObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkNPCollisionObjectUnlinked };
		inline static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObjectUnlinked };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::bhkNPCollisionObjectUnlinked };

		class __declspec(novtable) LinkExtraData
			: public NiExtraData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::bhkNPCollisionObjectUnlinked__LinkExtraData };
			inline static constexpr auto VTABLE{ VTABLE::bhkNPCollisionObjectUnlinked__LinkExtraData };

			// members
			BSTSet<NiPointer<bhkNPCollisionObjectUnlinked>> linkedCollisionObjSet;
		};
	};
	static_assert(sizeof(bhkNPCollisionObjectUnlinked) == 0x30);
}
