#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkNPCollisionObject.hpp"
#include "RE/N/NiExtraData.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class __declspec(novtable) bhkNPCollisionObjectUnlinked : public bhkNPCollisionObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkNPCollisionObjectUnlinked;
		inline static constexpr const auto& VTABLE = VTABLE::bhkNPCollisionObjectUnlinked;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::bhkNPCollisionObjectUnlinked;

		class __declspec(novtable) LinkExtraData : public NiExtraData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::bhkNPCollisionObjectUnlinked__LinkExtraData;
			inline static constexpr const auto& VTABLE = VTABLE::bhkNPCollisionObjectUnlinked__LinkExtraData;

			LinkExtraData()
			{
				REL::EmplaceVtable(this);
			}

			explicit LinkExtraData(BSFixedString a_name) :
				NiExtraData(std::move(a_name))
			{
				REL::EmplaceVtable(this);
			}

			~LinkExtraData() override; // 0x00

			// members
			BSTSet<NiPointer<bhkNPCollisionObjectUnlinked>> linkedCollisionObjSet;
		};

		~bhkNPCollisionObjectUnlinked() override; // 0x00
	};

	static_assert(sizeof(bhkNPCollisionObjectUnlinked) == 0x30);
}
