#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESContainer;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class Object;
}

namespace RE::GameScript
{
	class FormOrInventoryObj;
	class RefrOrInventoryObj;

	void BindCObject(const BSTSmartPointer<BSScript::Object>& a_object, const FormOrInventoryObj& a_inventoryObject, BSScript::IVirtualMachine& a_vm);
	void BindCObject(const BSTSmartPointer<BSScript::Object>& a_object, const RefrOrInventoryObj& a_inventoryObject, BSScript::IVirtualMachine& a_vm);

	[[nodiscard]] NiPointer<TESObjectREFR> GetRefInventoryObjectRef(const NiPointer<TESObjectREFR>& a_ref, ContainerID a_itemUniqueID);
	[[nodiscard]] NiPointer<TESObjectREFR> GetContainerInventoryObjectRef(const TESContainer* a_container, ContainerID a_itemUniqueID);
	[[nodiscard]] NiPointer<TESObjectREFR> GetInventoryObjectRef(TESFormID a_containerFormID, ContainerID a_itemUniqueID);
}
