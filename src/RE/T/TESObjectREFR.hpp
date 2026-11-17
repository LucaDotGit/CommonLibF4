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
#include "RE/B/BSString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IAnimationGraphManagerHolder.hpp"
#include "RE/I/IKeywordFormBase.hpp"
#include "RE/I/ITEM_REMOVE_REASON.hpp"
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
	concept TESBoundObjectConstraint = std::derived_from<T, TESBoundObject> &&
									   !REX::pointer<T> &&
									   !REX::reference<T> &&
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
	class hkVector4;
	class INSTANCE_FILTER;
	class LOADED_REF_DATA;
	class MagicCaster;
	class MagicTarget;
	class ModelReferenceEffect;
	class NiAVObject;
	class NiNode;
	class NiPoint3;
	class NiPoint3A;
	class NiTransform;
	class REFR_LOCK;
	class ShaderReferenceEffect;
	class TargetEntry;
	class TESModel;
	class TrapData;
	class TrapEntry;

	class __declspec(novtable) TESObjectREFR :
		public TESForm,													// 0x000
		public BSHandleRefObject,										// 0x020
		public BSTEventSink<BSActiveGraphIfInactiveEvent>,				// 0x030
		public BSTEventSink<BSAnimationGraphEvent>,						// 0x038
		public BSTEventSink<BGSInventoryListEvent::Event>,				// 0x040
		public IAnimationGraphManagerHolder,							// 0x048
		public IKeywordFormBase,										// 0x050
		public ActorValueOwner,											// 0x058
		public BSTEventSource<ActorValueEvents::ActorValueChangedEvent> // 0x060
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectREFR;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectREFR;
		inline static constexpr auto FORM_TYPE = FormType::ObjectReference;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Move = 1 << 1,
				HavokMove = 1 << 2,
				CellChange = 1 << 3,
				Scale = 1 << 4,
				Inventory = 1 << 5,
				ExtraOwnership = 1 << 6,
				BaseObject = 1 << 7,
				ExtraLinkRef = 1 << 8,
				ExtraWorkshop = 1 << 9,
				ExtraItemData = 1 << 10,
				ExtraAmmo = 1 << 11,
				ExtraLock = 1 << 12,
				ForceMove = 1 << 13,
				ExtraTeleport = 1 << 17,
				Empty = 1 << 21,
				OpenDefaultState = 1 << 22,
				OpenState = 1 << 23,
				Promoted = 1 << 25,
				ExtraActivatingChildren = 1 << 26,
				LeveledInventory = 1 << 27,
				Animation = 1 << 28,
				ExtraEncounterZone = 1 << 29,
				ExtraCreatedOnly = 1 << 30,
				ExtraGameOnly = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				IsGroundPiece = 1 << 4,
				CollisionsDisabled = 1 << 4,
				Deleted = 1 << 5,
				HiddenFromLocalMap = 1 << 6,
				TurnOffFire = 1 << 7,
				Inaccessible = 1 << 8,
				LODRespectsEnableState = 1 << 8,
				StartsDead = 1 << 8,
				DoesNotLightWater = 1 << 8,
				MotionBlur = 1 << 9,
				Persistent = 1 << 10,
				InitiallyDisabled = 1 << 11,
				Ignored = 1 << 12,
				StartUnconscious = 1 << 13,
				SkyMarker = 1 << 13,
				Harvested = 1 << 13,
				IsFullLOD = 1 << 16,
				NeverFades = 1 << 16,
				DoesNotLightLandscape = 1 << 17,
				IgnoreFriendlyHits = 1 << 20,
				NoAIAcquire = 1 << 25,
				CollisionGeometry_Filter = 1 << 26,
				CollisionGeometry_BoundingBox = 1 << 27,
				ReflectedByAutoWater = 1 << 28,
				DoNotHavokSettle = 1 << 29,
				Ground = 1 << 30,
				Respawns = 1 << 30,
				Multibound = static_cast<std::uint32_t>(1) << 31
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class RemoveItemData
		{
		public:
			RemoveItemData(TESBoundObject* a_object, std::int32_t a_count) :
				object(a_object),
				count(a_count)
			{
			}

			// members
			BSTSmallArray<std::uint32_t, 4> stackDataArray;		 // 0x00
			TESBoundObject* object{nullptr};					 // 0x20
			std::int32_t count{0};								 // 0x28
			ITEM_REMOVE_REASON reason{ITEM_REMOVE_REASON::None}; // 0x2C
			TESObjectREFR* otherContainer{nullptr};				 // 0x30
			NiPoint3* dropLoc{nullptr};							 // 0x38
			NiPoint3* rotate{nullptr};							 // 0x40
		};

		static_assert(sizeof(RemoveItemData) == 0x48);

		GAME_HEAP_REDEFINE_NEW(TESObjectREFR);

		~TESObjectREFR() override; // 0x00

		// add
		virtual void Predestroy();								// 0x4A
		virtual void PreModelLoaderQueueing();					// 0x4B - { return; }
		virtual auto GetEditorLocation() const -> BGSLocation*; // 0x4C
		virtual auto GetEditorLocation(
			NiPoint3& a_originalLocation,
			NiPoint3& a_originalAngle,
			TESForm*& a_locationFormOut,
			TESForm* a_locationForm) -> bool;																  // 0x4D
		virtual auto IsTalking() const -> bool;																  // 0x4E
		virtual void ForceEditorLocation(BGSLocation* a_location);											  // 0x4F
		virtual void Update3DPosition(bool a_warp);															  // 0x50
		virtual void UpdateSoundCallBack(bool a_endSceneAction);											  // 0x51
		virtual auto SetDialoguewithPlayer(bool a_set, bool a_forceGreet, TESTopicInfo* a_topicInfo) -> bool; // 0x52
		virtual void AddDynamicIdleCRC(std::uint32_t a_crc); // 0x53 - { return; }
		virtual void GetPreviousDynamicIdleCRCS(std::uint32_t* a_crcs, std::uint32_t a_requestSize) const; // 0x54
		virtual auto GetFullLODRef() const -> bool;														   // 0x55
		virtual void SetFullLODRef(bool a_val);															   // 0x56
		virtual auto GetSequencer() const -> BGSAnimationSequencer*;									   // 0x57
		virtual auto QCanUpdateSync() const -> bool;							   // 0x58 - { return true; }
		virtual auto GetAllowPromoteToPersistent() const -> bool;				   // 0x59 - { return true; }
		virtual auto DoesFloat() const -> bool;									   // 0x5A - { return false; }
		virtual auto CheckForCurrentAliasPackage() -> TESPackage*;				   // 0x5B - { return nullptr; }
		virtual auto GetCurrentScene() const -> BGSScene*;						   // 0x5C
		virtual void SetCurrentScene(BGSScene* a_scene);						   // 0x5D
		virtual auto UpdateInDialogue(DialogueResponse* a_response, bool) -> bool; // 0x5E
		virtual auto GetExclusiveBranch() const -> BGSDialogueBranch*;			   // 0x5F
		virtual void SetExclusiveBranch(BGSDialogueBranch* a_exclusiveBranch);	   // 0x60
		virtual void StopCurrentDialogue(bool a_force);							   // 0x61
		virtual void FadeCurrentDialogue();										   // 0x62
		virtual void PauseCurrentDialogue();									   // 0x63
		virtual void ResumeCurrentDialogue();									   // 0x64
		virtual void SetActorCause(ActorCause* a_actorCause);					   // 0x65
		virtual auto GetActorCause() const -> ActorCause*;						   // 0x66
		virtual auto GetActorWidthOrRefDiameter() const -> REX::Float32;		   // 0x67
		virtual auto GetActorHeightOrRefBound() const -> REX::Float32;			   // 0x68
		virtual auto GetStartingAngle() -> NiPoint3;							   // 0x69
		virtual auto GetStartingLocation() -> NiPoint3;							   // 0x6A
		virtual void SetStartingPosition(const NiPoint3& a_position);			   // 0x6B
		virtual void UpdateRefLight(REX::Float32 a_deltaTime);					   // 0x6C
		virtual auto RemoveItem(RemoveItemData& a_data) -> ObjectRefHandle;		   // 0x6D
		virtual void AddWornOutfitImpl(BGSOutfit* a_outfit, bool a_queueItem);	   // 0x6E - { return; }
		virtual auto AddWornItem(
			TESBoundObject* a_object,
			BSTSmartPointer<ExtraDataList> a_extra,
			std::int32_t a_number,
			bool a_forceEquip,
			BGSEquipIndex a_equipIndex) -> bool;								 // 0x6F
		virtual void DoTrap(TrapEntry* a_trap, TargetEntry* a_target);			 // 0x71 - { return; }
		virtual void DoTrap(TrapData& a_trapData);								 // 0x70 - { return; }
		virtual void SetEquipStateLocked(TESBoundObject* a_object, bool a_lock); // 0x72
		virtual void SendContainerChangedEvent(
			const TESObjectREFR* a_oldContainer,
			const TESObjectREFR* a_newContainer,
			const TESBoundObject* a_baseObject,
			std::int32_t a_count,
			TESFormID a_referenceFormID,
			ContainerID a_uniqueID) const;														 // 0x73
		virtual void UnequipArmorFromSlot(BIPED_OBJECT a_bipedObject, bool a_markAsReEquipable); // 0x74 - { return; }
		virtual void RemoveAllObjectsWorn();													 // 0x75
		virtual void PostRemoveWornObject(const BGSObjectInstance& a_object, const BGSEquipSlot* a_equipSlot); // 0x76
		virtual void Set3DUpdateFlag(RESET_3D_FLAGS a_flags); // 0x77 - { return; }
		virtual void ClearAll3DUpdateFlags();				  // 0x78 - { return; }
		virtual auto AdjustItemWeight(
			TESBoundObject& a_object,
			const BGSInventoryItem::Stack& a_stack,
			REX::Float32 a_weight,
			bool* a_shouldModifyWholeStackOut) -> REX::Float32; // 0x79 - { return a_weight; }
		virtual void AddObjectToContainer(
			TESBoundObject* a_obj,
			BSTSmartPointer<ExtraDataList> a_extra,
			std::int32_t a_count,
			TESObjectREFR* a_oldContainer,
			ITEM_REMOVE_REASON a_reason);												  // 0x7A
		virtual auto GetLookingAtLocation() const -> NiPoint3;							  // 0x7B
		virtual auto GetMagicCaster(MagicSystem::CastingSource a_source) -> MagicCaster*; // 0x7C
		virtual auto GetMagicTarget() -> MagicTarget*;									  // 0x7D
		virtual auto IsChild() const -> bool;											  // 0x7E - { return false; }
		virtual auto GetTemplateActorBase() -> TESActorBase*;							  // 0x7F - { return nullptr; }
		virtual void SetTemplateActorBase(TESActorBase*);								  // 0x80 - { return; }
		virtual auto GetFaceNodeSkinned() -> BSFaceGenNiNode*;							  // 0x81 - { return nullptr; }
		virtual auto GetFaceNode() -> BSFaceGenNiNode*;				   // 0x82 - { return GetFaceNodeSkinned(); }
		virtual auto ClampToGround() -> bool;						   // 0x83
		virtual auto DetachHavok(NiAVObject* a_obj3D) -> bool;		   // 0x84
		virtual void InitHavok();									   // 0x85
		virtual auto Load3D(bool a_backgroundLoading) -> NiAVObject*;  // 0x86
		virtual void Release3DRelatedData();						   // 0x87
		virtual void Set3D(NiAVObject* a_object, bool a_queue3DTasks); // 0x88
		virtual auto ShouldBackgroundClone() const -> bool;			   // 0x89
		virtual auto IsReadyForAttach(const IO_TASK_PRIORITY& a_priority) const -> bool; // 0x8A - { return true; }
		virtual auto Get3D() const -> NiAVObject*;										 // 0x8C
		virtual auto Get3D(bool a_firstPerson) const -> NiAVObject*;					 // 0x8B - { return Get3D(); }
		virtual auto GetFullyLoaded3D() const -> NiAVObject*;							 // 0x8D
		virtual auto Is3rdPersonVisible() const -> bool;								 // 0x8E - { return true; }
		virtual auto PopulateGraphProjectsToLoad(
			const NiAVObject* a_obj3D,
			BSScrapArray<BSStaticString<REX::W32::MAX_PATH>>& a_projectFilenames) const -> bool; // 0x8F
		virtual auto GetTESModel() const -> TESModel*;											 // 0x90
		virtual auto GetVisualsRace() const -> TESRace*;										 // 0x91
		virtual void GetPhysicsTransform(NiTransform& a_outTransform) const;					 // 0x92
		virtual auto GetBoundMin() const -> NiPoint3;											 // 0x93
		virtual auto GetBoundMax() const -> NiPoint3;											 // 0x94
		virtual auto GetBehaviorRootNameOverrides(BSScrapArray<BSFixedString>& a_behaviorRoots) const
			-> bool; // 0x95 - { return false; }
		virtual auto GetBehaviorRootNameReplacement(BSFixedString& a_rootNameReplacement) const
			-> bool; // 0x96 - { return false; }
		virtual auto GetBehaviorRootData(
			bool a_onlyCollectActiveRoots,
			BSScrapArray<BGSBehaviorRootData>& a_behaviorRoots) const -> bool;				  // 0x97
		virtual void OnHeadInitialized();													  // 0x98 - { return; }
		virtual auto InitNonNPCAnimation(NiNode& a_nodeForAnim) -> bool;					  // 0x99
		virtual auto CheckAndFixSkinAndBoneOrder(NiNode& a_nodeToTest) -> bool;				  // 0x9A
		virtual void ModifyAnimationUpdateData(BSAnimationUpdateData& a_updateData);		  // 0x9B - { return; }
		virtual auto ShouldSaveAnimationOnUnloading() const -> bool;						  // 0x9C
		virtual auto ShouldSaveAnimationOnSaving() const -> bool;							  // 0x9D
		virtual auto ShouldPerformRevert() const -> bool;									  // 0x9E - { return true; }
		virtual void UpdateAnimation(REX::Float32 a_deltaTime);								  // 0x9F
		virtual void CollectPickNodes();													  // 0xA0 - { return; }
		virtual auto GetBiped() const -> const BSTSmartPointer<BipedAnim>&;					  // 0xA2
		virtual auto GetBiped(bool a_firstPerson) const -> const BSTSmartPointer<BipedAnim>&; // 0xA1
		virtual auto GetCurrentBiped() const -> const BSTSmartPointer<BipedAnim>&; // 0xA3 - { return GetBiped(); }
		virtual void SetBiped(const BSTSmartPointer<BipedAnim>& a_biped);		   // 0xA4 - { return; }
		virtual void AttachWeapon(
			const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
			BGSEquipIndex a_equipIndex); // 0xA5
		virtual void RemoveWeapon(
			const BGSObjectInstanceT<TESObjectWEAP>& a_weapon,
			BGSEquipIndex a_equipIndex,
			bool a_queue3DTasks);										   // 0xA6 - { return; }
		virtual void CreateInventoryList(const TESContainer* a_container); // 0xA7
		virtual void DestroyInventoryList();							   // 0xA8
		virtual void SetRunsInLow(bool a_set);							   // 0xA9 - { return; }
		virtual void SetObjectReference(TESBoundObject* a_object);		   // 0xAA
		virtual void MoveHavok(bool a_forceRec);						   // 0xAB
		virtual void GetLinearVelocity(NiPoint3& a_velocity) const;		   // 0xAC
		virtual void ApplyMovementDelta(
			REX::Float32 a_deltaTime,
			const NiPoint3A& a_delta,
			const NiPoint3& a_angleDelta);												  // 0xAD
		virtual void SetActionComplete(bool a_value);									  // 0xAE - { return; }
		virtual void SetMovementComplete(bool a_set);									  // 0xAF - { return; }
		virtual void Disable();															  // 0xB0
		virtual void ResetInventory(bool a_leveledOnly);								  // 0xB1
		virtual auto GetCurrent3D() const -> NiAVObject*;								  // 0xB2 - { return Get3D(); }
		virtual auto IsExplosion() -> Explosion*;										  // 0xB4 - { return nullptr; }
		virtual auto IsExplosion() const -> const Explosion*;							  // 0xB3 - { return nullptr; }
		virtual auto IsProjectile() -> Projectile*;										  // 0xB6 - { return nullptr; }
		virtual auto IsProjectile() const -> const Projectile*;							  // 0xB5 - { return nullptr; }
		virtual auto OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const -> bool; // 0xB7 - { return true; }
		virtual void DoMoveToHigh();													  // 0xB8 - { return; }
		virtual void TryMoveToMiddleLow();												  // 0xB9 - { return; }
		virtual auto TryChangeSkyCellActorsProcessLevel() -> bool;						  // 0xBA - { return false; }
		virtual void SetDisplayGeometry(bool);											  // 0xBB - { return; }
		virtual void TryUpdateActorLastSeenTime();										  // 0xBC - { return; }
		virtual void SaveGameTest();													  // 0xBD
		virtual auto GetSaveParentCell() const -> TESObjectCELL*;						  // 0xBE
		virtual void SetParentCell(TESObjectCELL* a_cell);								  // 0xBF
		virtual auto IsDead(bool a_notEssential) const -> bool;							  // 0xC0
		virtual auto ProcessInWater(hknpBodyId a_bodyID, REX::Float32 a_waterHeight, REX::Float32 a_deltaTime)
			-> bool; // 0xC1
		virtual auto ApplyCurrent(
			REX::Float32 a_deltaTime,
			const hkVector4& a_linVel,
			const hkVector4& a_unk01) -> bool;								  // 0xC2 - { return false; }
		virtual auto GetDecalGroup() const -> BGSDecalGroup*;				  // 0xC3
		virtual void InitDefaultWornImpl(bool a_weapon, bool a_allowChanges); // 0xC4
		virtual auto HasKeywordHelper(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data) const
			-> bool; // 0xC5

		auto ActivateRef(
			TESObjectREFR* a_actionRef,
			TESBoundObject* a_objectToGet,
			std::int32_t a_count,
			bool a_defaultProcessingOnly,
			bool a_fromScript,
			bool a_looping) -> bool;
		void AddInventoryItem(
			TESBoundObject* a_object,
			BSTSmartPointer<ExtraDataList> a_extra,
			std::uint32_t a_count,
			TESObjectREFR* a_oldContainer,
			const INSTANCE_FILTER* a_filter,
			TESObjectREFR* a_overrideRef);
		void AddLockChange();
		auto ApplyArtObject(
			BGSArtObject* a_art,
			REX::Float32 a_time = static_cast<REX::Float32>(-1.0),
			TESObjectREFR* a_facingRef = nullptr,
			bool a_attachToCamera = false,
			bool a_inheritRotation = false,
			NiAVObject* a_3D = nullptr,
			bool a_interfaceEffect = false) -> ModelReferenceEffect*;
		auto ApplyEffectShader(
			TESEffectShader* a_art,
			REX::Float32 a_time = static_cast<REX::Float32>(-1.0),
			TESObjectREFR* a_facingRef = nullptr,
			bool a_attachToCamera = false,
			bool a_inheritRotation = false,
			NiAVObject* a_3D = nullptr,
			bool a_interfaceEffect = false) -> ShaderReferenceEffect*;
		[[nodiscard]]
		auto CanBeMoved() const -> bool;
		void Enable(bool a_resetInventory);
		void FindAndWriteStackDataForInventoryItem(
			TESBoundObject* a_object,
			BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
			BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
			bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = BGSInventoryList::StandardObjectCompareCallbackFn,
			bool a_alwaysContinue = false) const;
		[[nodiscard]]
		static auto FindReferenceFor3D(NiAVObject* a_object3D) -> TESObjectREFR*;
		[[nodiscard]]
		auto GetAngle() const noexcept -> NiPoint3A;
		[[nodiscard]]
		auto GetAngleX() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetAngleY() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetAngleZ() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetBaseObject() const noexcept -> TESBoundObject*;
		[[nodiscard]]
		auto GetCurrentLocation() const -> BGSLocation*;
		[[nodiscard]]
		auto GetDisplayName() const -> std::optional<BGSLocalizedString>;
		[[nodiscard]]
		auto GetEditorDead() const -> bool;
		[[nodiscard]]
		auto GetGoldAmount() const -> std::int64_t;
		[[nodiscard]]
		auto GetHandle() const -> ObjectRefHandle;
		[[nodiscard]]
		auto GetHasOwner() const -> bool;
		[[nodiscard]]
		auto GetHeadingAngle(const NiPoint3& a_position) const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetInventoryObjectCount(const TESBoundObject* a_object) const -> std::uint32_t;
		auto GetItemCount(std::uint32_t& a_count, TESForm* a_item, bool a_countComponent) const -> bool;
		[[nodiscard]]
		auto GetLinkedRef(BGSKeyword* a_keyword) const -> TESObjectREFR*;
		[[nodiscard]]
		auto GetLock() const noexcept -> REFR_LOCK*;
		void GetObjectCenter(NiPoint3& a_center) const;
		[[nodiscard]]
		auto GetOrCreateExtraList() -> BSTSmartPointer<ExtraDataList>;
		[[nodiscard]]
		auto GetOwner() const -> TESForm*;
		[[nodiscard]]
		auto GetParentCell() const noexcept -> TESObjectCELL*;
		[[nodiscard]]
		auto GetPosition() const noexcept -> NiPoint3A;
		[[nodiscard]]
		auto GetPositionX() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetPositionY() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetPositionZ() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetRelevantWaterHeight() const -> REX::Float32;
		[[nodiscard]]
		auto GetWaterHeight() const -> REX::Float32;
		[[nodiscard]]
		auto GetWeightInContainer() const -> REX::Float32;
		[[nodiscard]]
		auto HasContainer() const -> BaseFormComponent*;
		[[nodiscard]]
		auto HasLocationRefType(BGSLocationRefType* a_locationRefType) const noexcept -> bool;
		[[nodiscard]]
		auto Is3DLoaded() const noexcept -> bool;
		[[nodiscard]]
		auto IsAnOwner(Actor* a_testOwner, bool a_useFaction, bool a_requiresOwner) const -> bool;
		[[nodiscard]]
		auto IsCrimeToActivate() const -> bool;
		[[nodiscard]]
		auto IsDecalRef() const -> bool;
		[[nodiscard]]
		auto IsInWater() const -> bool;
		[[nodiscard]]
		auto IsLeveledCreature() const -> bool;
		[[nodiscard]]
		auto IsMarker() const -> bool;
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
		auto SetDisplayName(const BGSLocalizedString& a_name) -> bool;
		void SetHeadingAngle(const NiPoint3& a_position, REX::Float32 a_angleOffset = static_cast<REX::Float32>(0.0))
			noexcept;
		void SetLinkedRef(TESObjectREFR* a_actor, BGSKeyword* a_keyword);
		void SetLocationOnReference(const NiPoint3& a_point);
		void SetPosition(const NiPoint3A& a_position) noexcept;
		void SetPositionX(REX::Float32 a_x) noexcept;
		void SetPositionY(REX::Float32 a_y) noexcept;
		void SetPositionZ(REX::Float32 a_z) noexcept;
		void SetScale(REX::Float32 a_scale);
		void SetWantsDelete(bool a_delete);
		void UpdateDynamicNavmesh(bool a_active);
		void UpdateReference3D();

		[[nodiscard]]
		static auto GetRefByNumericID(TESFormID a_formID) noexcept -> NiPointer<TESObjectREFR>;
		[[nodiscard]]
		static auto GetRefByEditorID(const BSFixedString& a_editorID) noexcept -> NiPointer<TESObjectREFR>;
		[[nodiscard]]
		static auto FindFormOrRefByNumericID(TESFormID a_formID) noexcept
			-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;
		[[nodiscard]]
		static auto FindFormOrRefByEditorID(const BSFixedString& a_editorID) noexcept
			-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;

		[[nodiscard]]
		static auto ContainsKeyword(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) noexcept
			-> std::optional<bool>;
		[[nodiscard]]
		static auto GetKeywordCount(const TESObjectREFR* a_ref) noexcept -> std::optional<std::uint32_t>;
		[[nodiscard]]
		static auto GetKeywordIndex(const TESObjectREFR* a_ref, const BGSKeyword* a_keyword) noexcept
			-> std::optional<std::uint32_t>;

		[[nodiscard]]
		static auto GetKeywords(const TESObjectREFR* a_ref) -> std::optional<BSTArray<BGSKeyword*>>;
		static void SetKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords);

		[[nodiscard]]
		static auto GetNthKeyword(const TESObjectREFR* a_ref, std::uint32_t a_index) noexcept -> BGSKeyword*;
		static auto SetNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index, BGSKeyword* a_keyword) -> bool;
		static auto RemoveNthKeyword(TESObjectREFR* a_ref, std::uint32_t a_index) -> bool;

		static auto AddKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword) -> bool;
		static auto RemoveKeyword(TESObjectREFR* a_ref, BGSKeyword* a_keyword) -> bool;
		static auto ReplaceKeyword(TESObjectREFR* a_ref, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword) -> bool;

		static auto AddKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords) -> bool;
		static auto RemoveKeywords(TESObjectREFR* a_ref, std::span<BGSKeyword*> a_keywords) -> bool;
		static auto ClearKeywords(TESObjectREFR* a_ref) noexcept -> bool;

		static auto ForEachKeyword(
			const TESObjectREFR* a_ref,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate)
			-> BSContainer::ForEachResult;

		template <Impl::TESBoundObjectConstraint T>
		[[nodiscard]]
		auto GetBaseObject() noexcept -> T*
		{
			// NOLINTNEXTLINE(misc-const-correctness)
			auto* baseObject = GetBaseObject();
			return baseObject ? baseObject->As<T>() : nullptr;
		}

		template <Impl::TESBoundObjectConstraint T>
		[[nodiscard]]
		auto GetBaseObject() const noexcept -> const T*
		{
			const auto* baseObject = GetBaseObject();
			return baseObject ? baseObject->As<T>() : nullptr;
		}

		// members
		TESObjectCELL* parentCell;				  // 0x0B8
		OBJ_REFR data;							  // 0x0C0
		LOADED_REF_DATA* loadedData;			  // 0x0F0
		BGSInventoryList* inventoryList;		  // 0x0F8
		BSTSmartPointer<ExtraDataList> extraList; // 0x100
		std::uint16_t refScale;					  // 0x018
		std::int8_t modelState;					  // 0x10A
		bool predestroyed;						  // 0x10B
	};

	static_assert(sizeof(TESObjectREFR) == 0x110);
}
