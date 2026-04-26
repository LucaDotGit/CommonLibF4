#include "RE/G/GameScript_FormOrInventoryObj.hpp"

#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameVM.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::GameScript
{
	FormOrInventoryObj::FormOrInventoryObj(const GameVM& a_gameVM, BSScript::ObjectHandle a_objectHandle)
	{
		auto* formOrContainer = static_cast<TESObjectREFR*>(nullptr);
		a_gameVM.handlePolicy.GetInventoryObjOrFormFromHandle(a_objectHandle, formOrContainer, _uniqueID);
		_formOrContainer = formOrContainer;
	}

	BSScript::ObjectHandle FormOrInventoryObj::GetHandle() const
	{
		return HandlePolicy::GetHandleForFormOrInventoryObject(*this);
	}
}
