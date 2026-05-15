#include "RE/G/GameScript.hpp"

#include "RE/B/BGSInventoryList.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/C/ContainerItemExtra.hpp"
#include "RE/C/ContainerObject.hpp"
#include "RE/E/ExtraReferenceHandles.hpp"
#include "RE/E/ExtraUniqueID.hpp"
#include "RE/G/GameScript_FormOrInventoryObj.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameScript_RefrOrInventoryObj.hpp"
#include "RE/G/GameVM.hpp"
#include "RE/T/TESContainer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE::GameScript
{
	void BindCObject(const BSTSmartPointer<BSScript::Object>& a_object, const FormOrInventoryObj& a_inventoryObject, BSScript::IVirtualMachine& a_vm)
	{
		using FuncType = void (*)(const BSTSmartPointer<BSScript::Object>&, const FormOrInventoryObj&, BSScript::IVirtualMachine&);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::BindCObject01 };
		std::invoke(FUNC, a_object, a_inventoryObject, a_vm);
	}

	void BindCObject(const BSTSmartPointer<BSScript::Object>& a_object, const RefrOrInventoryObj& a_inventoryObject, BSScript::IVirtualMachine& a_vm)
	{
		using FuncType = void (*)(const BSTSmartPointer<BSScript::Object>&, const RefrOrInventoryObj&, BSScript::IVirtualMachine&);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::GameScript::BindCObject02 };
		std::invoke(FUNC, a_object, a_inventoryObject, a_vm);
	}

	NiPointer<TESObjectREFR> GetRefInventoryObjectRef(const NiPointer<TESObjectREFR>& a_ref, ContainerID a_itemUniqueID)
	{
		if (!a_ref) {
			return {};
		}

		const auto* containerInventoryList = a_ref->inventoryList;
		if (!containerInventoryList) {
			return {};
		}

		const auto containerInventoryLock = BSAutoReadLock(containerInventoryList->rwLock);

		auto result = NiPointer<TESObjectREFR>();
		containerInventoryList->ForEachStack([&result, a_itemUniqueID](const BSTSmartPointer<BGSInventoryItem::Stack>& a_stack) -> BSContainer::ForEachResult {
			if (!a_stack) {
				return BSContainer::ForEachResult::kContinue;
			}

			const auto stackExtraList = a_stack->extra;
			if (!stackExtraList) {
				return BSContainer::ForEachResult::kContinue;
			}

			const auto stackExtraLock = BSAutoReadLock(stackExtraList->extraRWLock);

			const auto* extraUniqueID = stackExtraList->GetExtra<ExtraUniqueID>();
			if (!extraUniqueID || extraUniqueID->uniqueID != a_itemUniqueID) {
				return BSContainer::ForEachResult::kContinue;
			}

			const auto* extraRefHandle = stackExtraList->GetExtra<ExtraReferenceHandles>();
			if (!extraRefHandle) {
				return BSContainer::ForEachResult::kContinue;
			}

			result = extraRefHandle->originalRef.get();
			return BSContainer::ForEachResult::kStop;
		});

		return result;
	}

	NiPointer<TESObjectREFR> GetContainerInventoryObjectRef(const TESContainer* a_container, ContainerID a_itemUniqueID)
	{
		if (!a_container) {
			return {};
		}

		auto result = NiPointer<TESObjectREFR>();
		a_container->ForEachObject([&result, a_itemUniqueID](ContainerObject* a_object) -> BSContainer::ForEachResult {
			if (!a_object) {
				return BSContainer::ForEachResult::kContinue;
			}

			const auto* objectExtra = a_object->itemExtra;
			if (!objectExtra) {
				return BSContainer::ForEachResult::kContinue;
			}

			auto* objectOwnerForm = objectExtra->ownerForm;
			if (!objectOwnerForm) {
				return BSContainer::ForEachResult::kContinue;
			}

			auto* objectOwnerRef = DynamicCast<TESObjectREFR*>(objectOwnerForm);
			if (!objectOwnerRef) {
				return BSContainer::ForEachResult::kContinue;
			}

			const auto objectOwnerRefPtr = NiPointer{ objectOwnerRef };
			if (!objectOwnerRefPtr) {
				return BSContainer::ForEachResult::kContinue;
			}

			result = GetRefInventoryObjectRef(objectOwnerRefPtr, a_itemUniqueID);
			return BSContainer::ForEachResult::kStop;
		});

		return result;
	}

	NiPointer<TESObjectREFR> GetInventoryObjectRef(TESFormID a_containerFormID, ContainerID a_itemUniqueID)
	{
		const auto formOrRef = TESObjectREFR::FindFormOrRefByNumericID(a_containerFormID);
		if (!formOrRef) {
			return {};
		}

		const auto* refPtr = std::get_if<NiPointer<TESObjectREFR>>(std::addressof(formOrRef.value()));
		if (refPtr) {
			return GetRefInventoryObjectRef(*refPtr, a_itemUniqueID);
		}

		const auto* formPtr = std::get_if<TESForm*>(std::addressof(formOrRef.value()));
		if (!formPtr) {
			std::unreachable();
		}

		const auto* container = DynamicCast<const TESContainer*>(*formPtr);
		if (!container) {
			return {};
		}

		return GetContainerInventoryObjectRef(container, a_itemUniqueID);
	}
}
