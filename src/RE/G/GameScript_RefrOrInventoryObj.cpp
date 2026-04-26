#include "RE/G/GameScript_RefrOrInventoryObj.hpp"

#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::GameScript
{
	RefrOrInventoryObj::RefrOrInventoryObj(const GameVM& a_gameVM, BSScript::ObjectHandle a_objectHandle)
	{
		a_gameVM.handlePolicy.GetInventoryObjFromHandle(a_objectHandle, _containerRef, _uniqueID, _ref);
	}

	BSScript::ObjectHandle RefrOrInventoryObj::GetHandle() const
	{
		return HandlePolicy::GetHandleForRefOrInventoryObject(*this);
	}
}
