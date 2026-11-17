#include "RE/G/GameScript_RefrOrInventoryObj.hpp"

#include "RE/G/GameScript_HandlePolicy.hpp"

namespace RE::GameScript
{
	RefrOrInventoryObj::RefrOrInventoryObj(const HandlePolicy& a_handlePolicy, BSScript::ObjectHandle a_objectHandle)
	{
		a_handlePolicy.GetInventoryObjFromHandle(a_objectHandle, _containerRef, _uniqueID, _ref);
	}

	auto RefrOrInventoryObj::GetHandle() const -> BSScript::ObjectHandle
	{
		return HandlePolicy::GetHandleForRefOrInventoryObject(*this);
	}
}
