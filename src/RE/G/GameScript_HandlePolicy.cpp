#include "RE/G/GameScript_HandlePolicy.hpp"

#include "RE/A/ActiveEffect.hpp"
#include "RE/A/Actor.hpp" // IWYU pragma: keep
#include "RE/B/BGSBaseAlias.hpp"
#include "RE/B/BSInputEnableLayer.hpp"
#include "RE/G/GameScript_FormOrInventoryObj.hpp"
#include "RE/G/GameScript_RefrOrInventoryObj.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESQuest.hpp"

namespace RE::GameScript
{
	void HandlePolicy::DropSaveLoadRemapData()
	{
		using FuncType = decltype(&HandlePolicy::DropSaveLoadRemapData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::HandlePolicy::DropSaveLoadRemapData };
		FUNC(this);
	}

	void HandlePolicy::GetInventoryObjFromHandle(BSScript::ObjectHandle a_cobject, TESObjectREFR*& a_container, ContainerID& a_uniqueID, TESObjectREFR*& a_inWorldRef) const
	{
		using FuncType = decltype(&HandlePolicy::GetInventoryObjFromHandle);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::HandlePolicy::GetInventoryObjFromHandle };
		FUNC(this, a_cobject, a_container, a_uniqueID, a_inWorldRef);
	}

	void HandlePolicy::GetInventoryObjOrFormFromHandle(BSScript::ObjectHandle a_cobject, TESObjectREFR*& a_container, ContainerID& a_uniqueID) const
	{
		using FuncType = decltype(&HandlePolicy::GetInventoryObjOrFormFromHandle);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::HandlePolicy::GetInventoryObjOrFormFromHandle };
		FUNC(this, a_cobject, a_container, a_uniqueID);
	}

	void HandlePolicy::UpdatePersistence()
	{
		using FuncType = decltype(&HandlePolicy::UpdatePersistence);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::HandlePolicy::UpdatePersistence };
		FUNC(this);
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForAlias(const BGSBaseAlias* a_alias)
	{
		if (!a_alias) {
			return EMPTY_HANDLE;
		}

		const auto* owningQuest = a_alias->GetOwningQuest();
		if (!owningQuest) {
			return EMPTY_HANDLE;
		}

		return GetHandleForAlias(static_cast<std::uint16_t>(a_alias->GetAliasID()), owningQuest->GetFormID());
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForForm(const TESForm* a_form)
	{
		if (!a_form) {
			return EMPTY_HANDLE;
		}

		return GetHandleForForm(a_form->GetFormID());
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForFormOrInventoryObject(const FormOrInventoryObj& a_inventoryObject)
	{
		const auto* container = a_inventoryObject.GetContainer();
		if (!container) {
			return EMPTY_HANDLE;
		}

		const auto uniqueID = a_inventoryObject.GetUniqueID();
		if (uniqueID == FormOrInventoryObj::INVALID_UNIQUE_ID) {
			return EMPTY_HANDLE;
		}

		return GetHandleForInventoryObject(uniqueID, container->GetFormID());
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForRefOrInventoryObject(const RefrOrInventoryObj& a_inventoryObject)
	{
		const auto* container = a_inventoryObject.GetContainerRef();
		if (!container) {
			return EMPTY_HANDLE;
		}

		const auto uniqueID = a_inventoryObject.GetUniqueID();
		if (uniqueID == RefrOrInventoryObj::INVALID_UNIQUE_ID) {
			return EMPTY_HANDLE;
		}

		return GetHandleForInventoryObject(uniqueID, container->GetFormID());
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForActiveEffect(const ActiveEffect* a_activeEffect)
	{
		if (!a_activeEffect) {
			return EMPTY_HANDLE;
		}

		const auto targetActor = a_activeEffect->GetTargetActor();
		if (!targetActor) {
			return EMPTY_HANDLE;
		}

		const auto uniqueID = a_activeEffect->GetUniqueID();
		if (uniqueID == ActiveEffect::INVALID_UNIQUE_ID) {
			return EMPTY_HANDLE;
		}

		return GetHandleForActiveEffect(uniqueID, targetActor->GetFormID());
	}

	BSScript::ObjectHandle HandlePolicy::GetHandleForInputEnableLayer(const BSInputEnableLayer* a_inputEnableLayer)
	{
		if (!a_inputEnableLayer) {
			return EMPTY_HANDLE;
		}

		return GetHandleForInputEnableLayer(a_inputEnableLayer->GetLayerID());
	}
}
