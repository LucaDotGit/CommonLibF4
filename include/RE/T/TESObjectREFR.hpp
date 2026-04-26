#pragma once

#include "RE/A/ActorValueOwner.hpp"
#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BGSInventoryList.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSHandleRefObject.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IAnimationGraphManagerHolder.hpp"
#include "RE/I/IKeywordFormBase.hpp"
#include "RE/I/ITEM_REMOVE_REASON.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/O/OBJ_REFR.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESForm.hpp"

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::Impl
{
	template <class T>
	concept TESBoundObjectConstraint =
		std::derived_from<T, TESBoundObject> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;
}

namespace RE::MagicSystem
{
	enum class CastingSource : std::int32_t;
}

namespace RE
{
	enum class BIPED_OBJECT : std::int32_t;
	enum class IO_TASK_PRIORITY : std::int32_t;
	enum class RESET_3D_FLAGS : std::int32_t;

	class ActorCause;
	class BGSAnimationSequencer;
	class BGSBehaviorRootData;
	class BGSDecalGroup;
	class BipedAnim;
	class BSActiveGraphIfInactiveEvent;
	class BSAnimationGraphEvent;
	class BSAnimationUpdateData;
	class BSFaceGenNiNode;
	class DialogueResponse;
	class ExtraDataList;
	class hknpBodyId;
	class hkVector4f;
	class INSTANCE_FILTER;
	class LOADED_REF_DATA;
	class MagicCaster;
	class MagicTarget;
	class ModelReferenceEffect;
	class NiAVObject;
	class NiNode;
	class NiTransform;
	class REFR_LOCK;
	class ShaderReferenceEffect;
	class TargetEntry;
	class TESModel;
	class TrapData;
	class TrapEntry;

	class __declspec(novtable) TESObjectREFR
		: public TESForm,												  // 000
		  public BSHandleRefObject,										  // 020
		  public BSTEventSink<BSActiveGraphIfInactiveEvent>,			  // 030
		  public BSTEventSink<BSAnimationGraphEvent>,					  // 038
		  public BSTEventSink<BGSInventoryListEvent::Event>,			  // 040
		  public IAnimationGraphManagerHolder,							  // 048
		  public IKeywordFormBase,										  // 050
		  public ActorValueOwner,										  // 058
		  public BSTEventSource<ActorValueEvents::ActorValueChangedEvent> // 060
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectREFR };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectREFR };
		inline static constexpr auto FORM_TYPE{ FormType::kObjectReference };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kMove = 1 << 1,
				kHavokMove = 1 << 2,
				kCellChange = 1 << 3,
				kScale = 1 << 4,
				kInventory = 1 << 5,
				kExtraOwnership = 1 << 6,
				kBaseObject = 1 << 7,
				kExtraLinkRef = 1 << 8,
				kExtraWorkshop = 1 << 9,
				kExtraItemData = 1 << 10,
				kExtraAmmo = 1 << 11,
				kExtraLock = 1 << 12,
				kForceMove = 1 << 13,
				kExtraTeleport = 1 << 17,
				kEmpty = 1 << 21,
				kOpenDefaultState = 1 << 22,
				kOpenState = 1 << 23,
				kPromoted = 1 << 25,
				kExtraActivatingChildren = 1 << 26,
				kLeveledInventory = 1 << 27,
				kAnimation = 1 << 28,
				kExtraEncounterZone = 1 << 29,
				kExtraCreatedOnly = 1 << 30,
				kExtraGameOnly = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kIsGroundPiece = 1 << 4,
				kCollisionsDisabled = 1 << 4,
				kDeleted = 1 << 5,
				kHiddenFromLocalMap = 1 << 6,
				kTurnOffFire = 1 << 7,
				kInaccessible = 1 << 8,
				kLODRespectsEnableState = 1 << 8,
				kStartsDead = 1 << 8,
				kDoesNotLightWater = 1 << 8,
				kMotionBlur = 1 << 9,
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,
				kStartUnconscious = 1 << 13,
				kSkyMarker = 1 << 13,
				kHarvested = 1 << 13,
				kIsFullLOD = 1 << 16,
				kNeverFades = 1 << 16,
				kDoesNotLightLandscape = 1 << 17,
				kIgnoreFriendlyHits = 1 << 20,
				kNoAIAcquire = 1 << 25,
				kCollisionGeometry_Filter = 1 << 26,
				kCollisionGeometry_BoundingBox = 1 << 27,
				kReflectedByAutoWater = 1 << 28,
				kDoNotHavokSettle = 1 << 29,
				kGround = 1 << 30,
				kRespawns = 1 << 30,
				kMultibound = 1ui32 << 31
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class RemoveItemData
		{
		public:
			RemoveItemData(TESBoundObject* a_object, std::int32_t a_count)
				: object(a_object), count(a_count)
			{
			}

			// members
			BSTSmallArray<std::uint32_t, 4> stackDataArray;			// 00
			TESBoundObject* object{ nullptr };						// 20
			std::int32_t count{ 0 };								// 28
			ITEM_REMOVE_REASON reason{ ITEM_REMOVE_REASON::kNone }; // 2C
			TESObjectREFR* otherContainer{ nullptr };				// 30
			NiPoint3* dropLoc{ nullptr };							// 38
			NiPoint3* rotate{ nullptr };							// 40
		};
		static_assert(sizeof(RemoveItemData) == 0x48);

		GAME_HEAP_REDEFINE_NEW(TESObjectREFR);

		// add
		virtual void Predestroy();																																																			   // 4A
		virtual void PreModelLoaderQueueing();																																																   // 4B - { return; }
		virtual BGSLocation* GetEditorLocation() const;																																														   // 4C
		virtual bool GetEditorLocation(NiPoint3& a_originalLocation, NiPoint3& a_originalAngle, TESForm*& a_locationFormOut, TESForm* a_locationForm);																						   // 4D
		virtual bool IsTalking() const;																																																		   // 4E
		virtual void ForceEditorLocation(BGSLocation* a_location);																																											   // 4F
		virtual void Update3DPosition(bool a_warp);																																															   // 50
		virtual void UpdateSoundCallBack(bool a_endSceneAction);																																											   // 51
		virtual bool SetDialoguewithPlayer(bool a_set, bool a_forceGreet, TESTopicInfo* a_topicInfo);																																		   // 52
		virtual void AddDynamicIdleCRC(std::uint32_t a_crc);																																												   // 53 - { return; }
		virtual void GetPreviousDynamicIdleCRCS(std::uint32_t* a_crcs, std::uint32_t a_requestSize) const;																																	   // 54
		virtual bool GetFullLODRef() const;																																																	   // 55
		virtual void SetFullLODRef(bool a_val);																																																   // 56
		virtual BGSAnimationSequencer* GetSequencer() const;																																												   // 57
		virtual bool QCanUpdateSync() const;																																																   // 58 - { return true; }
		virtual bool GetAllowPromoteToPersistent() const;																																													   // 59 - { return true; }
		virtual bool DoesFloat() const;																																																		   // 5A - { return false; }
		virtual TESPackage* CheckForCurrentAliasPackage();																																													   // 5B - { return nullptr; }
		virtual BGSScene* GetCurrentScene() const;																																															   // 5C
		virtual void SetCurrentScene(BGSScene* a_scene);																																													   // 5D
		virtual bool UpdateInDialogue(DialogueResponse* a_response, bool);																																									   // 5E
		virtual BGSDialogueBranch* GetExclusiveBranch() const;																																												   // 5F
		virtual void SetExclusiveBranch(BGSDialogueBranch* a_exclusiveBranch);																																								   // 60
		virtual void StopCurrentDialogue(bool a_force);																																														   // 61
		virtual void FadeCurrentDialogue();																																																	   // 62
		virtual void PauseCurrentDialogue();																																																   // 63
		virtual void ResumeCurrentDialogue();																																																   // 64
		virtual void SetActorCause(ActorCause* a_actorCause);																																												   // 65
		virtual ActorCause* GetActorCause() const;																																															   // 66
		virtual REX::Float32 GetActorWidthOrRefDiameter() const;																																											   // 67
		virtual REX::Float32 GetActorHeightOrRefBound() const;																																												   // 68
		virtual NiPoint3 GetStartingAngle();																																																   // 69
		virtual NiPoint3 GetStartingLocation();																																																   // 6A
		virtual void SetStartingPosition(const NiPoint3& a_position);																																										   // 6B
		virtual void UpdateRefLight(REX::Float32 a_delta);																																													   // 6C
		virtual ObjectRefHandle RemoveItem(RemoveItemData& a_data);																																											   // 6D
		virtual void AddWornOutfitImpl(BGSOutfit* a_outfit, bool a_queueItem);																																								   // 6E - { return; }
		virtual bool AddWornItem(TESBoundObject* a_object, BSTSmartPointer<ExtraDataList> a_extra, std::int32_t a_number, bool a_forceEquip, BGSEquipIndex a_equipIndex);																	   // 6F
		virtual void DoTrap(TrapEntry* a_trap, TargetEntry* a_target);																																										   // 71 - { return; }
		virtual void DoTrap(TrapData& a_trapData);																																															   // 70 - { return; }
		virtual void SetEquipStateLocked(TESBoundObject* a_object, bool a_lock);																																							   // 72
		virtual void SendContainerChangedEvent(const TESObjectREFR* a_oldContainer, const TESObjectREFR* a_newContainer, const TESBoundObject* a_baseObject, std::int32_t a_count, TESFormID a_referenceFormID, ContainerID a_uniqueID) const; // 73
		virtual void UnequipArmorFromSlot(BIPED_OBJECT a_bipedObject, bool a_markAsReEquipable);																																			   // 74 - { return; }
		virtual void RemoveAllObjectsWorn();																																																   // 75
		virtual void PostRemoveWornObject(const BGSObjectInstance& a_object, const BGSEquipSlot* a_equipSlot);																																   // 76
		virtual void Set3DUpdateFlag(RESET_3D_FLAGS a_flags);																																												   // 77 - { return; }
		virtual void ClearAll3DUpdateFlags();																																																   // 78 - { return; }
		virtual REX::Float32 AdjustItemWeight(TESBoundObject& a_object, const BGSInventoryItem::Stack& a_stack, REX::Float32 a_weight, bool* a_shouldModifyWholeStackOut);																	   // 79 - { return a_weight; }
		virtual void AddObjectToContainer(TESBoundObject* a_obj, BSTSmartPointer<ExtraDataList> a_extra, std::int32_t a_count, TESObjectREFR* a_oldContainer, ITEM_REMOVE_REASON a_reason);													   // 7A
		virtual NiPoint3 GetLookingAtLocation() const;																																														   // 7B
		virtual MagicCaster* GetMagicCaster(MagicSystem::CastingSource a_source);																																							   // 7C
		virtual MagicTarget* GetMagicTarget();																																																   // 7D
		virtual bool IsChild() const;																																																		   // 7E - { return false; }
		virtual TESActorBase* GetTemplateActorBase();																																														   // 7F - { return nullptr; }
		virtual void SetTemplateActorBase(TESActorBase*);																																													   // 80 - { return; }
		virtual BSFaceGenNiNode* GetFaceNodeSkinned();																																														   // 81 - { return nullptr; }
		virtual BSFaceGenNiNode* GetFaceNode();																																																   // 82 - { return GetFaceNodeSkinned(); }
		virtual bool ClampToGround();																																																		   // 83
		virtual bool DetachHavok(NiAVObject* a_obj3D);																																														   // 84
		virtual void InitHavok();																																																			   // 85
		virtual NiAVObject* Load3D(bool a_backgroundLoading);																																												   // 86
		virtual void Release3DRelatedData();																																																   // 87
		virtual void Set3D(NiAVObject* a_object, bool a_queue3DTasks);																																										   // 88
		virtual bool ShouldBackgroundClone() const;																																															   // 89
		virtual bool IsReadyForAttach(const IO_TASK_PRIORITY& a_priority) const;																																							   // 8A - { return true; }
		virtual NiAVObject* Get3D() const;																																																	   // 8C
		virtual NiAVObject* Get3D(bool a_firstPerson) const;																																												   // 8B - { return Get3D(); }
		virtual NiAVObject* GetFullyLoaded3D() const;																																														   // 8D
		virtual bool Is3rdPersonVisible() const;																																															   // 8E - { return true; }
		virtual bool PopulateGraphProjectsToLoad(const NiAVObject* a_obj3D, BSScrapArray<BSStaticStringT<REX::W32::MAX_PATH>>& a_projectFilenames) const;																					   // 8F
		virtual TESModel* GetTESModel() const;																																																   // 90
		virtual TESRace* GetVisualsRace() const;																																															   // 91
		virtual void GetPhysicsTransform(NiTransform& a_outTransform) const;																																								   // 92
		virtual NiPoint3 GetBoundMin() const;																																																   // 93
		virtual NiPoint3 GetBoundMax() const;																																																   // 94
		virtual bool GetBehaviorRootNameOverrides(BSScrapArray<BSFixedString>& a_behaviorRoots) const;																																		   // 95 - { return false; }
		virtual bool GetBehaviorRootNameReplacement(BSFixedString& a_rootNameReplacement) const;																																			   // 96 - { return false; }
		virtual bool GetBehaviorRootData(bool a_onlyCollectActiveRoots, BSScrapArray<BGSBehaviorRootData>& a_behaviorRoots) const;																											   // 97
		virtual void OnHeadInitialized();																																																	   // 98 - { return; }
		virtual bool InitNonNPCAnimation(NiNode& a_nodeForAnim);																																											   // 99
		virtual bool CheckAndFixSkinAndBoneOrder(NiNode& a_nodeToTest);																																										   // 9A
		virtual void ModifyAnimationUpdateData(BSAnimationUpdateData& a_updateData);																																						   // 9B - { return; }
		virtual bool ShouldSaveAnimationOnUnloading() const;																																												   // 9C
		virtual bool ShouldSaveAnimationOnSaving() const;																																													   // 9D
		virtual bool ShouldPerformRevert() const;																																															   // 9E - { return true; }
		virtual void UpdateAnimation(REX::Float32 a_delta);																																													   // 9F
		virtual void CollectPickNodes();																																																	   // A0 - { return; }
		virtual const BSTSmartPointer<BipedAnim>& GetBiped() const;																																											   // A2
		virtual const BSTSmartPointer<BipedAnim>& GetBiped(bool a_firstPerson) const;																																						   // A1
		virtual const BSTSmartPointer<BipedAnim>& GetCurrentBiped() const;																																									   // A3 - { return GetBiped(); }
		virtual void SetBiped(const BSTSmartPointer<BipedAnim>& a_biped);																																									   // A4 - { return; }
		virtual void AttachWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex);																															   // A5
		virtual void RemoveWeapon(const BGSObjectInstanceT<TESObjectWEAP>& a_weapon, BGSEquipIndex a_equipIndex, bool a_queue3DTasks);																										   // A6 - { return; }
		virtual void CreateInventoryList(const TESContainer* a_container);																																									   // A7
		virtual void DestroyInventoryList();																																																   // A8
		virtual void SetRunsInLow(bool a_set);																																																   // A9 - { return; }
		virtual void SetObjectReference(TESBoundObject* a_object);																																											   // AA
		virtual void MoveHavok(bool a_forceRec);																																															   // AB
		virtual void GetLinearVelocity(NiPoint3& a_velocity) const;																																											   // AC
		virtual void ApplyMovementDelta(REX::Float32 a_timeDelta, const NiPoint3A& a_delta, const NiPoint3& a_angleDelta);																													   // AD
		virtual void SetActionComplete(bool a_value);																																														   // AE - { return; }
		virtual void SetMovementComplete(bool a_set);																																														   // AF - { return; }
		virtual void Disable();																																																				   // B0
		virtual void ResetInventory(bool a_leveledOnly);																																													   // B1
		virtual NiAVObject* GetCurrent3D() const;																																															   // B2 - { return Get3D(); }
		virtual Explosion* IsExplosion();																																																	   // B4 - { return nullptr; }
		virtual const Explosion* IsExplosion() const;																																														   // B3 - { return nullptr; }
		virtual Projectile* IsProjectile();																																																	   // B6 - { return nullptr; }
		virtual const Projectile* IsProjectile() const;																																														   // B5 - { return nullptr; }
		virtual bool OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const;																																							   // B7 - { return true; }
		virtual void DoMoveToHigh();																																																		   // B8 - { return; }
		virtual void TryMoveToMiddleLow();																																																	   // B9 - { return; }
		virtual bool TryChangeSkyCellActorsProcessLevel();																																													   // BA - { return false; }
		virtual void SetDisplayGeometry(bool);																																																   // BB - { return; }
		virtual void TryUpdateActorLastSeenTime();																																															   // BC - { return; }
		virtual void SaveGameTest();																																																		   // BD
		virtual TESObjectCELL* GetSaveParentCell() const;																																													   // BE
		virtual void SetParentCell(TESObjectCELL* a_cell);																																													   // BF
		virtual bool IsDead(bool a_notEssential) const;																																														   // C0
		virtual bool ProcessInWater(hknpBodyId a_bodyID, REX::Float32 a_waterHeight, REX::Float32 a_deltaTime);																																   // C1
		virtual bool ApplyCurrent(REX::Float32 a_deltaTime, const hkVector4f& a_linVel, const hkVector4f& a_unk01);																															   // C2 - { return false; }
		virtual BGSDecalGroup* GetDecalGroup() const;																																														   // C3
		virtual void InitDefaultWornImpl(bool a_weapon, bool a_allowChanges);																																								   // C4
		virtual bool HasKeywordHelper(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data) const;																																	   // C5

		bool ActivateRef(TESObjectREFR* a_actionRef, TESBoundObject* a_objectToGet, std::int32_t a_count, bool a_defaultProcessingOnly, bool a_fromScript, bool a_looping);
		void AddInventoryItem(TESBoundObject* a_object, BSTSmartPointer<ExtraDataList> a_extra, std::uint32_t a_count, TESObjectREFR* a_oldContainer, const INSTANCE_FILTER* a_filter, TESObjectREFR* a_overrideRef);
		void AddLockChange();
		ModelReferenceEffect* ApplyArtObject(BGSArtObject* a_art, REX::Float32 a_time = -1.0_f32, TESObjectREFR* a_facingRef = nullptr, bool a_attachToCamera = false, bool a_inheritRotation = false, NiAVObject* a_3D = nullptr, bool a_interfaceEffect = false);
		ShaderReferenceEffect* ApplyEffectShader(TESEffectShader* a_art, REX::Float32 a_time = -1.0_f32, TESObjectREFR* a_facingRef = nullptr, bool a_attachToCamera = false, bool a_inheritRotation = false, NiAVObject* a_3D = nullptr, bool a_interfaceEffect = false);
		[[nodiscard]] bool CanBeMoved() const;
		void Enable(bool a_resetInventory);
		void FindAndWriteStackDataForInventoryItem(TESBoundObject* a_object, BGSInventoryItem::StackDataCompareFunctor& a_compareFunc, BGSInventoryItem::StackDataWriteFunctor& a_writeFunc, bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = BGSInventoryList::StandardObjectCompareCallbackFn, bool a_alwaysContinue = false) const;
		[[nodiscard]] static TESObjectREFR* FindReferenceFor3D(NiAVObject* a_object3D);
		[[nodiscard]] NiPoint3A GetAngle() const noexcept;
		[[nodiscard]] REX::Float32 GetAngleX() const noexcept;
		[[nodiscard]] REX::Float32 GetAngleY() const noexcept;
		[[nodiscard]] REX::Float32 GetAngleZ() const noexcept;
		[[nodiscard]] TESBoundObject* GetBaseObject() const noexcept;
		[[nodiscard]] BGSLocation* GetCurrentLocation() const;
		[[nodiscard]] auto GetDisplayName() const -> std::optional<BGSLocalizedString>;
		[[nodiscard]] bool GetEditorDead() const;
		[[nodiscard]] std::int64_t GetGoldAmount() const;
		[[nodiscard]] ObjectRefHandle GetHandle() const;
		[[nodiscard]] bool GetHasOwner() const;
		[[nodiscard]] REX::Float32 GetHeadingAngle(const NiPoint3& a_position) const noexcept;
		[[nodiscard]] std::uint32_t GetInventoryObjectCount(const TESBoundObject* a_object) const;
		bool GetItemCount(std::uint32_t& a_count, TESForm* a_item, bool a_countComponent) const;
		[[nodiscard]] TESObjectREFR* GetLinkedRef(BGSKeyword* a_keyword) const;
		[[nodiscard]] REFR_LOCK* GetLock() const;
		void GetObjectCenter(NiPoint3& a_center) const;
		[[nodiscard]] BSTSmartPointer<ExtraDataList> GetOrCreateExtraList();
		[[nodiscard]] TESForm* GetOwner() const;
		[[nodiscard]] TESObjectCELL* GetParentCell() const noexcept;
		[[nodiscard]] NiPoint3A GetPosition() const noexcept;
		[[nodiscard]] REX::Float32 GetPositionX() const noexcept;
		[[nodiscard]] REX::Float32 GetPositionY() const noexcept;
		[[nodiscard]] REX::Float32 GetPositionZ() const noexcept;
		[[nodiscard]] REX::Float32 GetRelevantWaterHeight() const;
		[[nodiscard]] REX::Float32 GetWaterHeight() const;
		[[nodiscard]] REX::Float32 GetWeightInContainer() const;
		[[nodiscard]] BaseFormComponent* HasContainer() const;
		[[nodiscard]] bool Is3DLoaded() const noexcept;
		[[nodiscard]] bool IsAnOwner(Actor* a_testOwner, bool a_useFaction, bool a_requiresOwner) const;
		[[nodiscard]] bool IsCrimeToActivate() const;
		[[nodiscard]] bool IsDecalRef() const;
		[[nodiscard]] bool IsInWater() const;
		[[nodiscard]] bool IsLeveledCreature() const;
		[[nodiscard]] bool IsMarker() const;
		void MarkAsDeleted();
		void ModAngle(const NiPoint3A& a_delta) noexcept;
		void ModAngleX(REX::Float32 a_x) noexcept;
		void ModAngleY(REX::Float32 a_y) noexcept;
		void ModAngleZ(REX::Float32 a_z) noexcept;
		void ModPosition(const NiPoint3A& a_delta) noexcept;
		void ModPositionX(REX::Float32 a_x) noexcept;
		void ModPositionY(REX::Float32 a_y) noexcept;
		void ModPositionZ(REX::Float32 a_z) noexcept;
		void MoveRefToNewSpace(TESObjectCELL* a_interior, TESWorldSpace* a_world);
		void RebuildBendableSpline(bool a_rebuildCollision, NiAVObject* a_target);
		void SetAngle(const NiPoint3A& a_point) noexcept;
		void SetAngleX(REX::Float32 a_x) noexcept;
		void SetAngleY(REX::Float32 a_y) noexcept;
		void SetAngleZ(REX::Float32 a_z) noexcept;
		void SetAngleOnReference(const NiPoint3& a_point);
		void SetBaseObject(TESBoundObject* a_object);
		bool SetDisplayName(const BGSLocalizedString& a_name);
		void SetHeadingAngle(const NiPoint3& a_position, REX::Float32 a_angleOffset = 0.0_f32) noexcept;
		void SetLinkedRef(Actor* a_actor, BGSKeyword* a_keyword);
		void SetLocationOnReference(const NiPoint3& a_point);
		void SetPosition(const NiPoint3A& a_position) noexcept;
		void SetPositionX(REX::Float32 a_x) noexcept;
		void SetPositionY(REX::Float32 a_y) noexcept;
		void SetPositionZ(REX::Float32 a_z) noexcept;
		void SetScale(REX::Float32 a_scale);
		void SetWantsDelete(bool a_delete);
		void UpdateDynamicNavmesh(bool a_active);
		void UpdateReference3D();

		[[nodiscard]] static auto GetRefByNumericID(TESFormID a_formID) -> NiPointer<TESObjectREFR>;
		[[nodiscard]] static auto GetRefByEditorID(const BSFixedString& a_editorID) -> NiPointer<TESObjectREFR>;
		[[nodiscard]] static auto FindFormOrRefByNumericID(TESFormID a_formID) -> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;
		[[nodiscard]] static auto FindFormOrRefByEditorID(const BSFixedString& a_editorID) -> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;

		[[nodiscard]] static auto ContainsKeyword(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) -> std::optional<bool>;
		[[nodiscard]] static auto GetKeywordCount(const TESObjectREFR* a_ref) -> std::optional<std::uint32_t>;
		[[nodiscard]] static auto GetKeywordIndex(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) -> std::optional<std::uint32_t>;

		[[nodiscard]] static auto GetKeywords(const TESObjectREFR* a_ref) -> std::optional<std::vector<BGSKeyword*>>;
		static void SetKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords);

		[[nodiscard]] static BGSKeyword* GetNthKeyword(const TESObjectREFR* a_ref, std::uint32_t a_index);
		static bool SetNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index, BGSKeyword* a_keyword);
		static bool RemoveNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index);

		static bool AddKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword);
		static bool RemoveKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword);
		static bool ReplaceKeyword(TESObjectREFR* a_ref, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword);

		static bool AddKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords);
		static bool RemoveKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords);
		static bool ClearKeywords(TESObjectREFR* a_ref);

		static BSContainer::ForEachResult ForEachKeyword(const TESObjectREFR* a_ref,
			const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate);

		template <Impl::TESBoundObjectConstraint T>
		[[nodiscard]] T* GetBaseObject() noexcept
		{
			auto* baseObject = GetBaseObject();
			return baseObject ? baseObject->As<T>() : nullptr;
		}

		template <Impl::TESBoundObjectConstraint T>
		[[nodiscard]] const T* GetBaseObject() const noexcept
		{
			const auto* baseObject = GetBaseObject();
			return baseObject ? baseObject->As<T>() : nullptr;
		}

		// members
		TESObjectCELL* parentCell;				  // 0B8
		OBJ_REFR data;							  // 0C0
		LOADED_REF_DATA* loadedData;			  // 0F0
		BGSInventoryList* inventoryList;		  // 0F8
		BSTSmartPointer<ExtraDataList> extraList; // 100
		std::uint16_t refScale;					  // 018
		std::int8_t modelState;					  // 10A
		bool predestroyed;						  // 10B
	};
	static_assert(sizeof(TESObjectREFR) == 0x110);
}
