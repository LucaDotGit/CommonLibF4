#include "RE/Bethesda/Actor.hpp"

#include "RE/Bethesda/TESBoundAnimObjects.hpp"
#include "RE/Bethesda/TESBoundObjects.hpp"

namespace RE
{
	TESNPC* Actor::GetActorBase() const noexcept
	{
		const auto objRef = GetBaseObject();
		assert(objRef->GetFormType() == ENUM_FORMTYPE::kNPC_);
		return static_cast<TESNPC*>(objRef);
	}
}
