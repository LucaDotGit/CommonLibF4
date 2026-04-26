#pragma once

#include "RE/B/BIPED_OBJECT.hpp"
#include "RE/B/BIPOBJECT.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class NiNode;

	class BipedAnim
		: public BSIntrusiveRefCounted // 00
	{
	public:
		[[nodiscard]] BIPOBJECT* GetBipObject(BIPED_OBJECT a_bipedObject)
		{
			REX::Assert(a_bipedObject >= BIPED_OBJECT::kNone && a_bipedObject < BIPED_OBJECT::kTotal);
			return std::addressof(objects[std::to_underlying(a_bipedObject)]);
		}

		[[nodiscard]] const BIPOBJECT* GetBipObject(BIPED_OBJECT a_bipedObject) const
		{
			REX::Assert(a_bipedObject >= BIPED_OBJECT::kNone && a_bipedObject < BIPED_OBJECT::kTotal);
			return std::addressof(objects[std::to_underlying(a_bipedObject)]);
		}

		// members
		NiNode* root;																	 // 0008
		std::array<BIPOBJECT, std::to_underlying(BIPED_OBJECT::kTotal)> objects;		 // 0010
		std::array<BIPOBJECT, std::to_underlying(BIPED_OBJECT::kTotal)> bufferedObjects; // 0F30
		ObjectRefHandle actorRef;														 // 1E50
	};
	static_assert(sizeof(BipedAnim) == 0x1E58);
}
