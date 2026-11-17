#include "RE/G/GameScript_FormOrInventoryObj.hpp"

#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::GameScript
{
	FormOrInventoryObj::FormOrInventoryObj(const HandlePolicy& a_handlePolicy, BSScript::ObjectHandle a_objectHandle)
	{
		auto* formOrContainer = static_cast<TESObjectREFR*>(nullptr);
		a_handlePolicy.GetInventoryObjOrFormFromHandle(a_objectHandle, formOrContainer, _uniqueID);
		_formOrContainer = formOrContainer;
	}

	auto FormOrInventoryObj::GetHandle() const -> BSScript::ObjectHandle
	{
		return HandlePolicy::GetHandleForFormOrInventoryObject(*this);
	}
}
