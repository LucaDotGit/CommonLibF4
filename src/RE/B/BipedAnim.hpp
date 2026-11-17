#pragma once

#include "RE/B/BIPED_OBJECT.hpp"
#include "RE/B/BIPOBJECT.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class NiNode;

	class BipedAnim : public BSIntrusiveRefCounted // 0x00
	{
	public:
		[[nodiscard]]
		auto GetBipObject(BIPED_OBJECT a_bipedObject) -> BIPOBJECT*
		{
			REX::Assert(a_bipedObject >= BIPED_OBJECT::None && a_bipedObject < BIPED_OBJECT::_Count);
			return std::addressof(objects[REX::ToUnsigned(std::to_underlying(a_bipedObject))]);
		}

		[[nodiscard]]
		auto GetBipObject(BIPED_OBJECT a_bipedObject) const -> const BIPOBJECT*
		{
			REX::Assert(a_bipedObject >= BIPED_OBJECT::None && a_bipedObject < BIPED_OBJECT::_Count);
			return std::addressof(objects[REX::ToUnsigned(std::to_underlying(a_bipedObject))]);
		}

		// members
		NiNode* root;																	 // 0x0008
		std::array<BIPOBJECT, std::to_underlying(BIPED_OBJECT::_Count)> objects;		 // 0x0010
		std::array<BIPOBJECT, std::to_underlying(BIPED_OBJECT::_Count)> bufferedObjects; // 0x0F30
		ObjectRefHandle actorRef;														 // 0x1E50
	};

	static_assert(sizeof(BipedAnim) == 0x1E58);
}
