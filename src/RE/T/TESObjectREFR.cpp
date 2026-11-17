#include "RE/T/TESObjectREFR.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/E/ExtraDataList.hpp"
#include "RE/E/ExtraKeywords.hpp"
#include "RE/E/ExtraLocationRefType.hpp"
#include "RE/E/ExtraLock.hpp"
#include "RE/E/ExtraTextDisplayData.hpp"
#include "RE/L/LOADED_REF_DATA.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESObjectCELL.hpp"

namespace RE
{
	auto TESObjectREFR::ActivateRef(
		TESObjectREFR* a_actionRef,
		TESBoundObject* a_objectToGet,
		std::int32_t a_count,
		bool a_defaultProcessingOnly,
		bool a_fromScript,
		bool a_looping) -> bool
	{
		using FuncType = decltype(&TESObjectREFR::ActivateRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::ActivateRef);
		return std::invoke(
			FUNC,
			this,
			a_actionRef,
			a_objectToGet,
			a_count,
			a_defaultProcessingOnly,
			a_fromScript,
			a_looping);
	}

	void TESObjectREFR::AddInventoryItem(
		TESBoundObject* a_object,
		BSTSmartPointer<ExtraDataList> a_extra,
		std::uint32_t a_count,
		TESObjectREFR* a_oldContainer,
		const INSTANCE_FILTER* a_filter,
		TESObjectREFR* a_overrideRef)
	{
		using FuncType = decltype(&TESObjectREFR::AddInventoryItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::AddInventoryItem);
		std::invoke(FUNC, this, a_object, a_extra, a_count, a_oldContainer, a_filter, a_overrideRef);
	}

	void TESObjectREFR::AddLockChange()
	{
		using FuncType = decltype(&TESObjectREFR::AddLockChange);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::AddLockChange);
		std::invoke(FUNC, this);
	}

	auto TESObjectREFR::ApplyArtObject(
		BGSArtObject* a_art,
		REX::Float32 a_time,
		TESObjectREFR* a_facingRef,
		bool a_attachToCamera,
		bool a_inheritRotation,
		NiAVObject* a_3D,
		bool a_interfaceEffect) -> ModelReferenceEffect*
	{
		using FuncType = decltype(&TESObjectREFR::ApplyArtObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::ApplyArtObject);
		return std::invoke(
			FUNC,
			this,
			a_art,
			a_time,
			a_facingRef,
			a_attachToCamera,
			a_inheritRotation,
			a_3D,
			a_interfaceEffect);
	}

	auto TESObjectREFR::ApplyEffectShader(
		TESEffectShader* a_art,
		REX::Float32 a_time,
		TESObjectREFR* a_facingRef,
		bool a_attachToCamera,
		bool a_inheritRotation,
		NiAVObject* a_3D,
		bool a_interfaceEffect) -> ShaderReferenceEffect*
	{
		using FuncType = decltype(&TESObjectREFR::ApplyEffectShader);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::ApplyEffectShader);
		return std::invoke(
			FUNC,
			this,
			a_art,
			a_time,
			a_facingRef,
			a_attachToCamera,
			a_inheritRotation,
			a_3D,
			a_interfaceEffect);
	}

	auto TESObjectREFR::CanBeMoved() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::CanBeMoved);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::CanBeMoved);
		return std::invoke(FUNC, this);
	}

	void TESObjectREFR::Enable(bool a_resetInventory)
	{
		using FuncType = decltype(&TESObjectREFR::Enable);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::Enable);
		std::invoke(FUNC, this, a_resetInventory);
	}

	void TESObjectREFR::FindAndWriteStackDataForInventoryItem(
		TESBoundObject* a_object,
		BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
		BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
		bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*),
		bool a_alwaysContinue) const
	{
		if (inventoryList) {
			inventoryList->FindAndWriteStackDataForItem(
				a_object,
				a_compareFunc,
				a_writeFunc,
				a_objCompFn,
				a_alwaysContinue);
		}
	}

	auto TESObjectREFR::FindReferenceFor3D(NiAVObject* a_object3D) -> TESObjectREFR*
	{
		using FuncType = decltype(&TESObjectREFR::FindReferenceFor3D);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::FindReferenceFor3D);
		return std::invoke(FUNC, a_object3D);
	}

	auto TESObjectREFR::GetAngle() const noexcept -> NiPoint3A
	{
		return {GetAngleX(), GetAngleY(), GetAngleZ()};
	}

	auto TESObjectREFR::GetAngleX() const noexcept -> REX::Float32
	{
		return REX::RadToDeg(data.angle.x);
	}

	auto TESObjectREFR::GetAngleY() const noexcept -> REX::Float32
	{
		return REX::RadToDeg(data.angle.y);
	}

	auto TESObjectREFR::GetAngleZ() const noexcept -> REX::Float32
	{
		return REX::RadToDeg(data.angle.z);
	}

	auto TESObjectREFR::GetBaseObject() const noexcept -> TESBoundObject*
	{
		return data.objectReference;
	}

	auto TESObjectREFR::GetCurrentLocation() const -> BGSLocation*
	{
		using FuncType = decltype(&TESObjectREFR::GetCurrentLocation);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetCurrentLocation);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetDisplayName() const -> std::optional<BGSLocalizedString>
	{
		const auto* baseObject = data.objectReference;
		if (!baseObject) {
			return std::nullopt;
		}

		if (!extraList) {
			return TESFullName::GetFormFullName(baseObject);
		}

		const auto* extraData = extraList->GetExtra<ExtraTextDisplayData>();
		if (!extraData) {
			return TESFullName::GetFormFullName(baseObject);
		}

		const auto displayName = extraData->GetDisplayName(data.objectReference);
		return BGSLocalizedString(displayName);
	}

	auto TESObjectREFR::GetEditorDead() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::GetEditorDead);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetEditorDead);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetGoldAmount() const -> std::int64_t
	{
		using FuncType = decltype(&TESObjectREFR::GetGoldAmount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetGoldAmount);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetHandle() const -> ObjectRefHandle
	{
		return BSPointerHandleManagerInterface<TESObjectREFR>::GetHandle(this);
	}

	auto TESObjectREFR::GetHasOwner() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::GetHasOwner);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetHasOwner);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetHeadingAngle(const NiPoint3& a_position) const noexcept -> REX::Float32
	{
		const auto theta = std::atan2f(a_position.x - GetPositionX(), a_position.y - GetPositionY());
		auto heading = REX::RadToDeg(theta - data.angle.z);
		heading = REX::ClampDeg(heading);
		return heading;
	}

	auto TESObjectREFR::GetInventoryObjectCount(const TESBoundObject* a_object) const -> std::uint32_t
	{
		using FuncType = decltype(&TESObjectREFR::GetInventoryObjectCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetInventoryObjectCount);
		return std::invoke(FUNC, this, a_object);
	}

	auto TESObjectREFR::GetItemCount(std::uint32_t& a_count, TESForm* a_item, bool a_countComponent) const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::GetItemCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetItemCount);
		return std::invoke(FUNC, this, a_count, a_item, a_countComponent);
	}

	auto TESObjectREFR::GetLinkedRef(BGSKeyword* a_keyword) const -> TESObjectREFR*
	{
		using FuncType = decltype(&TESObjectREFR::GetLinkedRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetLinkedRef);
		return std::invoke(FUNC, this, a_keyword);
	}

	auto TESObjectREFR::GetLock() const noexcept -> REFR_LOCK*
	{
		if (!extraList) {
			return nullptr;
		}

		const auto* extraData = extraList->GetExtra<ExtraLock>();
		return extraData ? extraData->lock : nullptr;
	}

	void TESObjectREFR::GetObjectCenter(NiPoint3& a_center) const
	{
		using FuncType = decltype(&TESObjectREFR::GetObjectCenter);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetObjectCenter);
		std::invoke(FUNC, this, a_center);
	}

	auto TESObjectREFR::GetOrCreateExtraList() -> BSTSmartPointer<ExtraDataList>
	{
		if (extraList) {
			return extraList;
		}

		auto newExtraList = make_shared<ExtraDataList>();
		if (!newExtraList) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		extraList = newExtraList;
		return newExtraList;
	}

	auto TESObjectREFR::GetOwner() const -> TESForm*
	{
		using FuncType = decltype(&TESObjectREFR::GetOwner);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetOwner);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetParentCell() const noexcept -> TESObjectCELL*
	{
		return parentCell;
	}

	auto TESObjectREFR::GetPosition() const noexcept -> NiPoint3A
	{
		return data.location;
	}

	auto TESObjectREFR::GetPositionX() const noexcept -> REX::Float32
	{
		return data.location.x;
	}

	auto TESObjectREFR::GetPositionY() const noexcept -> REX::Float32
	{
		return data.location.y;
	}

	auto TESObjectREFR::GetPositionZ() const noexcept -> REX::Float32
	{
		return data.location.z;
	}

	auto TESObjectREFR::GetWaterHeight() const -> REX::Float32
	{
		if (loadedData) {
			const auto waterHeight = loadedData->relevantWaterHeight;
			if (waterHeight != -std::numeric_limits<REX::Float32>::infinity()) {
				return waterHeight;
			}
		}

		return parentCell ? parentCell->GetExteriorWaterHeight() : -std::numeric_limits<REX::Float32>::infinity();
	}

	auto TESObjectREFR::GetWeightInContainer() const -> REX::Float32
	{
		using FuncType = decltype(&TESObjectREFR::GetWeightInContainer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::GetWeightInContainer);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::HasContainer() const -> BaseFormComponent*
	{
		using FuncType = decltype(&TESObjectREFR::HasContainer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::HasContainer);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::HasLocationRefType(BGSLocationRefType* a_locationRefType) const noexcept -> bool
	{
		if (!extraList) {
			return false;
		}

		const auto* extraData = extraList->GetExtra<ExtraLocationRefType>();
		if (!extraData) {
			return false;
		}

		return std::ranges::any_of(
			extraData->locationRefTypes,
			[a_locationRefType](const BGSLocationRefType* a_otherLocationRefType) -> bool {
				return a_otherLocationRefType == a_locationRefType;
			});
	}

	auto TESObjectREFR::Is3DLoaded() const noexcept -> bool
	{
		return loadedData && loadedData->data3D;
	}

	auto TESObjectREFR::IsAnOwner(Actor* a_testOwner, bool a_useFaction, bool a_requiresOwner) const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::IsAnOwner);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::IsAnOwner);
		return std::invoke(FUNC, this, a_testOwner, a_useFaction, a_requiresOwner);
	}

	auto TESObjectREFR::IsCrimeToActivate() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::IsCrimeToActivate);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::IsCrimeToActivate);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::IsDecalRef() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::IsDecalRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::IsDecalRef);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::IsInWater() const -> bool
	{
		const auto waterHeight = GetWaterHeight();
		return waterHeight != -std::numeric_limits<REX::Float32>::infinity() && waterHeight > GetPositionZ();
	}

	auto TESObjectREFR::IsLeveledCreature() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::IsLeveledCreature);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::IsLeveledCreature);
		return std::invoke(FUNC, this);
	}

	auto TESObjectREFR::IsMarker() const -> bool
	{
		using FuncType = decltype(&TESObjectREFR::IsMarker);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::IsMarker);
		return std::invoke(FUNC, this);
	}

	void TESObjectREFR::MarkAsDeleted()
	{
		using FuncType = decltype(&TESObjectREFR::MarkAsDeleted);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::MarkAsDeleted);
		std::invoke(FUNC, this);
	}

	void TESObjectREFR::ModAngle(const NiPoint3A& a_delta) noexcept
	{
		data.angle.x += REX::DegToRad(a_delta.x);
		data.angle.y += REX::DegToRad(a_delta.y);
		data.angle.z += REX::DegToRad(a_delta.z);
	}

	void TESObjectREFR::ModAngleX(REX::Float32 a_x) noexcept
	{
		data.angle.x += REX::DegToRad(a_x);
	}

	void TESObjectREFR::ModAngleY(REX::Float32 a_y) noexcept
	{
		data.angle.y += REX::DegToRad(a_y);
	}

	void TESObjectREFR::ModAngleZ(REX::Float32 a_z) noexcept
	{
		data.angle.z += REX::DegToRad(a_z);
	}

	void TESObjectREFR::ModPosition(const NiPoint3A& a_delta) noexcept
	{
		data.location.x += a_delta.x;
		data.location.y += a_delta.y;
		data.location.z += a_delta.z;
	}

	void TESObjectREFR::ModPositionX(REX::Float32 a_x) noexcept
	{
		data.location.x += a_x;
	}

	void TESObjectREFR::ModPositionY(REX::Float32 a_y) noexcept
	{
		data.location.y += a_y;
	}

	void TESObjectREFR::ModPositionZ(REX::Float32 a_z) noexcept
	{
		data.location.z += a_z;
	}

	void TESObjectREFR::MoveRefToNewSpace(TESObjectCELL* a_interior, TESWorldSpace* a_world)
	{
		using FuncType = decltype(&TESObjectREFR::MoveRefToNewSpace);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::MoveRefToNewSpace);
		std::invoke(FUNC, this, a_interior, a_world);
	}

	void TESObjectREFR::RebuildBendableSpline(bool a_rebuildCollision, NiAVObject* a_target)
	{
		using FuncType = decltype(&TESObjectREFR::RebuildBendableSpline);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::RebuildBendableSpline);
		std::invoke(FUNC, this, a_rebuildCollision, a_target);
	}

	void TESObjectREFR::SetAngle(const NiPoint3A& a_point) noexcept
	{
		SetAngleX(a_point.x);
		SetAngleY(a_point.y);
		SetAngleZ(a_point.z);
	}

	void TESObjectREFR::SetAngleX(REX::Float32 a_x) noexcept
	{
		data.angle.x = REX::DegToRad(a_x);
	}

	void TESObjectREFR::SetAngleY(REX::Float32 a_y) noexcept
	{
		data.angle.y = REX::DegToRad(a_y);
	}

	void TESObjectREFR::SetAngleZ(REX::Float32 a_z) noexcept
	{
		data.angle.z = REX::DegToRad(a_z);
	}

	void TESObjectREFR::SetAngleOnReference(const NiPoint3& a_point)
	{
		using FuncType = decltype(&TESObjectREFR::SetAngleOnReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::SetAngleOnReference);
		std::invoke(FUNC, this, a_point);
	}

	void TESObjectREFR::SetBaseObject(TESBoundObject* a_object)
	{
		SetObjectReference(a_object);
	}

	auto TESObjectREFR::SetDisplayName(const BGSLocalizedString& a_name) -> bool
	{
		extraList = GetOrCreateExtraList();
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetOrCreateExtra<ExtraTextDisplayData>();
		if (!extraData) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		extraData->SetCustomName(a_name.operator BSFixedStringCS());
		return true;
	}

	void TESObjectREFR::SetHeadingAngle(const NiPoint3& a_position, REX::Float32 a_angleOffset) noexcept
	{
		const auto heading = GetHeadingAngle(a_position);
		auto angleZ = GetAngleZ() + heading + a_angleOffset;
		angleZ = REX::ClampDeg(angleZ);
		SetAngleZ(angleZ);
	}

	void TESObjectREFR::SetLinkedRef(TESObjectREFR* a_actor, BGSKeyword* a_keyword)
	{
		using FuncType = decltype(&TESObjectREFR::SetLinkedRef);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::SetLinkedRef);
		std::invoke(FUNC, this, a_actor, a_keyword);
	}

	void TESObjectREFR::SetLocationOnReference(const NiPoint3& a_point)
	{
		using FuncType = decltype(&TESObjectREFR::SetLocationOnReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::SetLocationOnReference);
		std::invoke(FUNC, this, a_point);
	}

	void TESObjectREFR::SetPosition(const NiPoint3A& a_position) noexcept
	{
		data.location = a_position;
	}

	void TESObjectREFR::SetPositionX(REX::Float32 a_x) noexcept
	{
		data.location.x = a_x;
	}

	void TESObjectREFR::SetPositionY(REX::Float32 a_y) noexcept
	{
		data.location.y = a_y;
	}

	void TESObjectREFR::SetPositionZ(REX::Float32 a_z) noexcept
	{
		data.location.z = a_z;
	}

	void TESObjectREFR::SetScale(REX::Float32 a_scale)
	{
		using FuncType = decltype(&TESObjectREFR::SetScale);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::SetScale);
		std::invoke(FUNC, this, a_scale);
	}

	void TESObjectREFR::SetWantsDelete(bool a_delete)
	{
		using FuncType = decltype(&TESObjectREFR::SetWantsDelete);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::SetWantsDelete);
		std::invoke(FUNC, this, a_delete);
	}

	void TESObjectREFR::UpdateDynamicNavmesh(bool a_active)
	{
		using FuncType = decltype(&TESObjectREFR::UpdateDynamicNavmesh);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::UpdateDynamicNavmesh);
		std::invoke(FUNC, this, a_active);
	}

	void TESObjectREFR::UpdateReference3D()
	{
		using FuncType = decltype(&TESObjectREFR::UpdateReference3D);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFR::UpdateReference3D);
		std::invoke(FUNC, this);
	}

	auto TESObjectREFR::GetRefByNumericID(TESFormID a_formID) noexcept -> NiPointer<TESObjectREFR>
	{
		const auto&& [formIDMap, formIDMutex] = TESForm::GetAllFormsByNumericID();
		if (!formIDMap) {
			return {};
		}

		const auto formIDLock = BSAutoReadLock(formIDMutex.get());

		const auto formIt = formIDMap->find(a_formID);
		if (formIt == formIDMap->end()) {
			return {};
		}

		auto* form = formIt->second;
		if (!form) {
			return {};
		}

		auto* ref = DynamicCast<TESObjectREFR*>(form);
		if (!ref) {
			return {};
		}

		return NiPointer(ref);
	}

	auto TESObjectREFR::GetRefByEditorID(const BSFixedString& a_editorID) noexcept -> NiPointer<TESObjectREFR>
	{
		const auto&& [editorIDMap, editorIDMutex] = TESForm::GetAllFormsByEditorID();
		if (!editorIDMap) {
			return {};
		}

		const auto formIDLock = BSAutoReadLock(editorIDMutex.get());

		const auto formIt = editorIDMap->find(a_editorID);
		if (formIt == editorIDMap->end()) {
			return {};
		}

		auto* form = formIt->second;
		if (!form) {
			return {};
		}

		auto* ref = DynamicCast<TESObjectREFR*>(form);
		if (!ref) {
			return {};
		}

		return NiPointer(ref);
	}

	auto TESObjectREFR::FindFormOrRefByNumericID(TESFormID a_formID) noexcept
		-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>
	{
		// Returning only a `TESForm` pointer may end up in a dangling pointer if the form is a reference
		// and gets deleted right after the pointer is returned.
		// So if the form is a reference, return its handle instead.

		const auto&& [formIDMap, formIDMutex] = TESForm::GetAllFormsByNumericID();
		const auto formIDLock = BSAutoReadLock(formIDMutex.get());

		if (!formIDMap) {
			return std::nullopt;
		}

		const auto formIt = formIDMap->find(a_formID);
		if (formIt == formIDMap->end()) {
			return std::nullopt;
		}

		auto* form = formIt->second;
		if (!form) {
			return std::nullopt;
		}

		auto* ref = DynamicCast<TESObjectREFR*>(form);
		if (!ref) {
			return form;
		}

		return NiPointer(ref);
	}

	auto TESObjectREFR::FindFormOrRefByEditorID(const BSFixedString& a_editorID) noexcept
		-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>
	{
		// Returning only a `TESForm` pointer may end up in a dangling pointer if the form is a reference
		// and gets deleted right after the pointer is returned.
		// So if the form is a reference, return its handle instead.

		const auto&& [editorIDMap, editorIDMutex] = TESForm::GetAllFormsByEditorID();
		const auto formIDLock = BSAutoReadLock(editorIDMutex.get());

		if (!editorIDMap) {
			return std::nullopt;
		}

		const auto formIt = editorIDMap->find(a_editorID);
		if (formIt == editorIDMap->end()) {
			return std::nullopt;
		}

		auto* form = formIt->second;
		if (!form) {
			return std::nullopt;
		}

		auto* ref = DynamicCast<TESObjectREFR*>(form);
		if (!ref) {
			return form;
		}

		return NiPointer(ref);
	}

	auto TESObjectREFR::ContainsKeyword(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) noexcept
		-> std::optional<bool>
	{
		if (!a_ref || !a_keyword) {
			return std::nullopt;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return std::nullopt;
		}

		if (TESForm::ContainsKeyword(baseObject, a_keyword)) {
			return true;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return std::nullopt;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return std::nullopt;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);
		return std::ranges::contains(extraData->extraKeywords, a_keyword);
	}

	auto TESObjectREFR::GetKeywordCount(const TESObjectREFR* a_ref) noexcept -> std::optional<std::uint32_t>
	{
		if (!a_ref) {
			return std::nullopt;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return std::nullopt;
		}

		const auto baseKeywordCount = TESForm::GetKeywordCount(baseObject);

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return baseKeywordCount;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return baseKeywordCount;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);
		return baseKeywordCount.value_or(0) + extraData->extraKeywords.size();
	}

	auto TESObjectREFR::GetKeywordIndex(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) noexcept
		-> std::optional<std::uint32_t>
	{
		if (!a_ref || !a_keyword) {
			return std::nullopt;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return std::nullopt;
		}

		const auto baseIndex = TESForm::GetKeywordIndex(baseObject, a_keyword);
		if (baseIndex) {
			return baseIndex;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return std::nullopt;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return std::nullopt;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);
		const auto& extraKeywords = extraData->extraKeywords;

		const auto* keywordIt = std::ranges::find(extraKeywords, a_keyword);
		if (keywordIt == extraKeywords.end()) {
			return std::nullopt;
		}

		const auto baseKeywordCount = TESForm::GetKeywordCount(baseObject);
		const auto extraIndex = static_cast<std::uint32_t>(std::distance(extraKeywords.begin(), keywordIt));
		return baseKeywordCount.value_or(0) + extraIndex;
	}

	auto TESObjectREFR::GetKeywords(const TESObjectREFR* a_ref) -> std::optional<BSTArray<BGSKeyword*>>
	{
		if (!a_ref) {
			return std::nullopt;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return std::nullopt;
		}

		auto baseKeywords = TESForm::GetKeywords(baseObject);

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return baseKeywords;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return baseKeywords;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);
		const auto& extraKeywords = extraData->extraKeywords;

		auto result = BSTArray<BGSKeyword*>();
		result.reserve(baseKeywords ? baseKeywords->size() + extraKeywords.size() : extraKeywords.size());

		if (baseKeywords) {
			result.insert(result.end(), baseKeywords->begin(), baseKeywords->end());
		}

		result.insert(result.end(), extraKeywords.begin(), extraKeywords.end());
		return result;
	}

	void TESObjectREFR::SetKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords)
	{
		if (!a_ref) {
			return;
		}

		if (a_keywords.empty()) {
			TESObjectREFR::ClearKeywords(a_ref);
			return;
		}

		const auto extraList = a_ref->GetOrCreateExtraList();

		auto* extraData = extraList->GetOrCreateExtra<ExtraKeywords>();
		if (!extraData) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);

		auto& extraKeywords = extraData->extraKeywords;
		extraKeywords.reserve(static_cast<std::uint32_t>(a_keywords.size()));

		for (auto* keyword : a_keywords) {
			if (!TESObjectREFR::ContainsKeyword(a_ref, keyword)) {
				extraKeywords.push_back(keyword);
			}
		}
	}

	auto TESObjectREFR::GetNthKeyword(const TESObjectREFR* a_ref, std::uint32_t a_index) noexcept -> BGSKeyword*
	{
		if (!a_ref) {
			return nullptr;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return nullptr;
		}

		const auto baseKeywordCount = TESForm::GetKeywordCount(baseObject).value_or(0);
		if (a_index < baseKeywordCount) {
			return TESForm::GetNthKeyword(baseObject, a_index).value_or(nullptr);
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return nullptr;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return nullptr;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);
		const auto& extraKeywords = extraData->extraKeywords;

		if (a_index >= extraKeywords.size()) {
			return nullptr;
		}

		return extraKeywords[a_index - baseKeywordCount];
	}

	auto TESObjectREFR::SetNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index, BGSKeyword* a_keyword) -> bool
	{
		if (!a_ref || !a_keyword || TESObjectREFR::ContainsKeyword(a_ref, a_keyword)) {
			return false;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return false;
		}

		const auto baseKeywordCount = TESForm::GetKeywordCount(baseObject).value_or(0);

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetOrCreateExtra<ExtraKeywords>();
		if (!extraData) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		auto& extraKeywords = extraData->extraKeywords;

		if (a_index >= extraKeywords.size()) {
			return false;
		}

		extraKeywords[a_index - baseKeywordCount] = a_keyword;
		return true;
	}

	auto TESObjectREFR::RemoveNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index) -> bool
	{
		if (!a_ref) {
			return false;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (!baseObject) {
			return false;
		}

		const auto baseKeywordCount = TESForm::GetKeywordCount(baseObject).value_or(0);

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		auto& extraKeywords = extraData->extraKeywords;

		if (a_index >= extraKeywords.size()) {
			return false;
		}

		extraKeywords.erase(extraKeywords.begin() + a_index - baseKeywordCount);
		return true;
	}

	auto TESObjectREFR::AddKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword) -> bool
	{
		if (!a_ref || !a_keyword || TESObjectREFR::ContainsKeyword(a_ref, a_keyword)) {
			return false;
		}

		const auto extraList = a_ref->GetOrCreateExtraList();

		auto* extraData = extraList->GetOrCreateExtra<ExtraKeywords>();
		if (!extraData) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		extraData->extraKeywords.push_back(a_keyword);
		return true;
	}

	auto TESObjectREFR::RemoveKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword) -> bool
	{
		if (!a_ref) {
			return false;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		auto& extraKeywords = extraData->extraKeywords;

		const auto* keywordIt = std::ranges::find(extraKeywords, a_keyword);
		if (keywordIt == extraKeywords.end()) {
			return false;
		}

		extraKeywords.erase(keywordIt);
		return true;
	}

	auto TESObjectREFR::ReplaceKeyword(TESObjectREFR* a_ref, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword) -> bool
	{
		if (!a_ref ||
			!a_newKeyword ||
			a_oldKeyword == a_newKeyword ||
			TESObjectREFR::ContainsKeyword(a_ref, a_newKeyword)) {
			return false;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		auto& extraKeywords = extraData->extraKeywords;

		auto* keywordIt = std::ranges::find(extraKeywords, a_oldKeyword);
		if (keywordIt == extraKeywords.end()) {
			return false;
		}

		const auto index = static_cast<std::uint32_t>(std::distance(extraKeywords.begin(), keywordIt));
		extraKeywords[index] = a_newKeyword;
		return true;
	}

	auto TESObjectREFR::AddKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords) -> bool
	{
		if (!a_ref || a_keywords.empty()) {
			return false;
		}

		const auto extraList = a_ref->GetOrCreateExtraList();

		auto* extraData = extraList->GetOrCreateExtra<ExtraKeywords>();
		if (!extraData) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);

		auto& extraKeywords = extraData->extraKeywords;
		extraKeywords.reserve(extraKeywords.size() + static_cast<std::uint32_t>(a_keywords.size()));

		for (auto* keyword : a_keywords) {
			if (keyword && !TESObjectREFR::ContainsKeyword(a_ref, keyword)) {
				extraKeywords.push_back(keyword);
			}
		}

		return true;
	}

	auto TESObjectREFR::RemoveKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords) -> bool
	{
		if (!a_ref || a_keywords.empty()) {
			return false;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		auto& extraKeywords = extraData->extraKeywords;

		for (auto* keyword : a_keywords) {
			const auto* keywordIt = std::ranges::find(extraKeywords, keyword);
			if (keywordIt != extraData->extraKeywords.end()) {
				extraKeywords.erase(keywordIt);
			}
		}

		return true;
	}

	auto TESObjectREFR::ClearKeywords(TESObjectREFR* a_ref) noexcept -> bool
	{
		if (!a_ref) {
			return false;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return false;
		}

		auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extraData->extraRWLock);
		extraData->extraKeywords.clear();
		return true;
	}

	auto TESObjectREFR::ForEachKeyword(
		const TESObjectREFR* a_ref,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate)
		-> BSContainer::ForEachResult
	{
		if (!a_ref) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto* baseObject = a_ref->GetBaseObject();
		if (baseObject && TESForm::ForEachKeyword(baseObject, a_predicate) == BSContainer::ForEachResult::Stop) {
			return BSContainer::ForEachResult::Stop;
		}

		const auto extraList = a_ref->extraList;
		if (!extraList) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto* extraData = extraList->GetExtra<ExtraKeywords>();
		if (!extraData) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto extraLock = BSAutoReadLock(extraData->extraRWLock);

		for (auto* keyword : extraData->extraKeywords) {
			if (std::invoke(a_predicate.get(), keyword) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
