#include "RE/B/BSScript_ObjectBindPolicy.hpp"

#include "RE/B/BSScript_IVMObjectBindInterface.hpp"

namespace RE::BSScript
{
	void ObjectBindPolicy::BindObject(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle) const
	{
		if (!bindInterface) {
			return;
		}

		constexpr auto IS_CONDITIONAL = false;
		bindInterface->BindObject(a_object, a_objectHandle, IS_CONDITIONAL);
	}

	void ObjectBindPolicy::UnbindObject(const BSTSmartPointer<Object>& a_object) const
	{
		if (!bindInterface) {
			return;
		}

		bindInterface->UnbindObject(a_object);
	}
}
