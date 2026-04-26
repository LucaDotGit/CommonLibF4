#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/F/FormType.hpp"
#include "RE/T/TESFile.hpp"
#include "RE/T/TESFileContainer.hpp"

namespace RE
{
	class TESForm;
}

namespace RE::BGSMod::Template
{
	class Items;
}

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::Impl
{
	template <class T>
	concept TESFormConstraint =
		std::derived_from<T, TESForm> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;
}

namespace RE
{
	enum class FormFlags : std::int32_t;

	class BGSLoadFormBuffer;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BGSSoundTagComponent;
	class TBO_InstanceData;

	class __declspec(novtable) TESForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESForm };
		inline static constexpr auto VTABLE{ VTABLE::TESForm };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		inline static constexpr auto PLAYER_BASE_FORM_ID = static_cast<TESFormID>(0x000007);
		inline static constexpr auto PLAYER_REF_FORM_ID = static_cast<TESFormID>(0x000014);

		inline static constexpr auto PLAYER_BASE_EDITOR_ID = "Player"sv;
		inline static constexpr auto PLAYER_REF_EDITOR_ID = "PlayerRef"sv;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kCreated = 0,
				kFlags = 1 << 0
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class InGameFormFlags : std::uint16_t
		{
			kNone = 0,
			kWantsDelete = 1 << 0,
			kForcedPersistent = 1 << 1,
			kNoFavorAllowed = 1 << 4,
			kIsSkyObject = 1 << 5,
			kRefOriginalPersistent = 1 << 6,
			kRefPermanentlyDeleted = 1 << 7
		};

		class FormSortFunc
		{
		public:
			[[nodiscard]] std::int32_t operator()(const TESForm* a_lhs, const TESForm* a_rhs) const noexcept;
		};
		static_assert(std::is_empty_v<FormSortFunc>);

		~TESForm() override; // 00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;				// 02 - { return; }
		void ClearDataComponent() override;						// 03 - { SetFormEditorID(""); }
		void CopyComponent(BaseFormComponent* a_copy) override; // 06 - { return; }

		// add
		virtual void InitializeData();																											// 07 - { return; }
		virtual void ClearData();																												// 08 - { return; }
		virtual bool Load(TESFile* a_file);																										// 09 - { return true; }
		virtual bool LoadPartial(TESFile* a_file);																								// 0A - { return true; }
		virtual bool LoadEdit(TESFile* a_file);																									// 0B - { return Load(a_file); }
		virtual TESForm* CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap);									// 0C
		virtual bool AddChange(std::uint32_t a_changeFlags);																					// 0D
		virtual void RemoveChange(std::uint32_t a_changeFlags);																					// 0E
		virtual bool FindInFileFast(TESFile* a_file);																							// 0F - { return false; }
		virtual bool CheckSaveGame(BGSSaveFormBuffer* a_saveGameBuffer) const;																	// 10 - { return true; }
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);																				// 11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																				// 12
		virtual void InitLoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																			// 13 - { return; }
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																		// 14 - { return; }
		virtual void Revert(BGSLoadFormBuffer* a_loadGameBuffer);																				// 15 - { return; }
		virtual void InitItemImpl();																											// 16 - { return; }
		virtual TESFile* GetRevertFile() const;																									// 17
		virtual TESFile* GetDescriptionOwnerFile() const;																						// 18
		virtual FormType GetSavedFormType() const;																								// 19 - { return *formType; }
		virtual void GetFormDetailedString(char* a_dest, std::uint32_t a_size) const;															// 1A
		virtual bool GetKnown() const;																											// 1B - { return formFlags.any(RecordFlags::kKnown); }
		virtual bool GetRandomAnim() const;																										// 1C - { return formFlags.any(RecordFlags::kRandomAnim); }
		virtual bool GetPlayable(const TBO_InstanceData* a_data) const;																			// 1D - { return formFlags.any(RecordFlags::kPlayable); }
		virtual bool IsHeadingMarker() const;																									// 1E - { return false; }
		virtual bool IsHeadtrackMarker() const;																									// 1F - { return false; }
		virtual bool GetDangerous() const;																										// 20 - { return formFlags.any(RecordFlags::kDangerous); }
		virtual bool QHasCurrents() const;																										// 21 - { return formFlags.any(RecordFlags::kHasCurrents); }
		virtual bool GetObstacle() const;																										// 22 - { return formFlags.any(RecordFlags::kObstacle); }
		virtual bool QIsLODLandObject() const;																									// 23 - { return false; }
		virtual bool GetOnLocalMap() const;																										// 24 - { return formFlags.any(RecordFlags::kOnLocalMap); }
		virtual bool GetMustUpdate() const;																										// 25 - { return formFlags.any(RecordFlags::kMustUpdate); }
		virtual void SetOnLocalMap(bool a_val);																									// 26
		virtual bool GetIgnoredBySandbox() const;																								// 27 - { return false; }
		virtual void SetDelete(bool a_deleted);																									// 28
		virtual void SetAltered(bool a_altered);																								// 29
		virtual void SaveObjectBound();																											// 2A - { return; }
		virtual void LoadObjectBound(TESFile* a_file);																							// 2B - { return; }
		virtual void SavePreviewTransform(CHUNK_ID a_chunkID);																					// 2C - { return; }
		virtual void LoadPreviewTransform(TESFile* a_file);																						// 2D - { return; }
		virtual bool IsBoundObject() const;																										// 2E - { return false; }
		virtual bool IsObject() const;																											// 2F - { return false; }
		virtual bool IsMagicItem() const;																										// 30 - { return false; }
		virtual bool IsWater() const;																											// 31 - { return false; }
		virtual TESObjectREFR* IsReference();																									// 33 - { return nullptr; }
		virtual const TESObjectREFR* IsReference() const;																						// 32 - { return nullptr; }
		virtual std::uint32_t GetRefCount() const;																								// 34 - { return 0; }
		virtual const char* GetTextForParsedSubTag(const BSFixedString& a_subTag) const;														// 35
		virtual void Copy(TESForm* a_copy);																										// 36 - { return; }
		virtual bool BelongsInGroup(FORM* a_groupFORM, bool a_allowParentGroups, bool a_currentOnly);											// 37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);															// 38
		virtual std::uint32_t GetFormEditorIDLength() const;																					// 39
		virtual const char* GetFormEditorID() const;																							// 3A - { return ""; }
		virtual bool SetFormEditorID(const char* a_editorID);																					// 3B - { return true; }
		virtual bool IsParentForm();																											// 3C - { return false; }
		virtual bool IsParentFormTree();																										// 3D - { return false; }
		virtual bool IsFormTypeChild(std::uint8_t a_type);																						// 3E - { return false; }
		virtual bool LoopingActivate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef);												// 3F - { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }
		virtual bool Activate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef, TESBoundObject* a_objectToGet, std::int32_t a_count); // 40 - { return false; }
		virtual void SetFormID(TESFormID a_formID, bool a_updateFile);																			// 41
		virtual const char* GetObjectTypeName() const;																							// 42 - { return ""; }
		virtual bool QAvailableInGame() const;																									// 43 - { return true; }
		virtual BGSMod::Template::Items* GetObjectTemplate();																					// 44 - { return nullptr; }
		virtual BGSPreviewTransform* GetPreviewTransform();																						// 45 - { return nullptr; }
		virtual BGSSoundTagComponent* GetSoundTagComponent();																					// 46 - { return nullptr; }
		virtual std::uint32_t GetFilledSlots() const;																							// 47
		virtual std::uint32_t GetFilledSlotsImpl() const;																						// 48 - { return std::numeric_limits<std::uint32_t>::max(); }
		virtual REX::Float32 GetDesirability(TBO_InstanceData* a_instanceData, const TESForm* a_user) const;									// 49 - { return 0.0_f32; }

		static void AddCompileIndex(std::uint32_t& a_id, TESFile* a_file);
		[[nodiscard]] static std::uint32_t& GetTotalFormCount();
		[[nodiscard]] static auto GetAllFormsByEditorID() -> std::pair<BSTHashMap<BSFixedString, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]] static auto GetAllFormsByID() -> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]] static auto GetAllFormsByNumericID() -> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]] TESFile* GetFile(std::int32_t a_index = -1) const;
		[[nodiscard]] static TESForm* FindFormByEditorID(const BSFixedString& a_editorID);
		[[nodiscard]] static TESForm* FindFormByID(TESFormID a_formID);
		[[nodiscard]] static TESForm* FindFormByNumericID(TESFormID a_formID);
		[[nodiscard]] static auto GetEditorIDByForm(const TESForm* a_form) -> std::optional<BSFixedString>;
		[[nodiscard]] std::string_view GetFormTypeString() const;
		[[nodiscard]] FormFlags GetFormFlags() const noexcept;
		[[nodiscard]] TESFormID GetFormID() const noexcept;
		[[nodiscard]] FormType GetFormType() const noexcept;
		[[nodiscard]] TESFormID GetLocalFormID() const;
		[[nodiscard]] bool IsAlchemyItem() const noexcept;
		[[nodiscard]] bool IsCreated() const noexcept;
		[[nodiscard]] bool IsDeleted() const noexcept;
		[[nodiscard]] bool IsDisabled() const noexcept;
		[[nodiscard]] bool IsInitialized() const noexcept;
		[[nodiscard]] bool IsPlayer() const noexcept;
		[[nodiscard]] bool IsPlayerRef() const noexcept;
		[[nodiscard]] bool IsWeapon() const noexcept;
		void SetInGameFormFlags(InGameFormFlags a_flags, bool a_value);
		void SetTemporary();

		[[nodiscard]] static bool CanHoldKeywords(const TESForm* a_form);
		[[nodiscard]] static auto ContainsKeyword(const TESForm* a_form, const BGSKeyword* a_keyword) -> std::optional<bool>;
		[[nodiscard]] static auto GetKeywordCount(const TESForm* a_form) -> std::optional<std::uint32_t>;
		[[nodiscard]] static auto GetKeywordIndex(const TESForm* a_form, const BGSKeyword* a_keyword) -> std::optional<std::uint32_t>;

		[[nodiscard]] static auto GetKeywords(const TESForm* a_form) -> std::optional<std::vector<BGSKeyword*>>;
		static auto SetKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords) -> std::optional<bool>;

		[[nodiscard]] static auto GetNthKeyword(const TESForm* a_form, std::uint32_t a_index) -> std::optional<BGSKeyword*>;
		static auto SetNthKeyword(TESForm* a_form, std::uint32_t a_index, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto RemoveNthKeyword(TESForm* a_form, std::uint32_t a_index) -> std::optional<bool>;

		static auto AddKeyword(TESForm* a_form, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto RemoveKeyword(TESForm* a_form, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto ReplaceKeyword(TESForm* a_form, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword) -> std::optional<bool>;

		static bool AddKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords);
		static bool RemoveKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords);
		static bool ClearKeywords(TESForm* a_form);

		static BSContainer::ForEachResult ForEachKeyword(const TESForm* a_form,
			const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate);

		[[nodiscard]] bool Is(FormType a_type) const noexcept
		{
			return GetFormType() == a_type;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires((std::same_as<Args, FormType> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return DynamicCast<const T*>(this) != nullptr;
		}

		[[nodiscard]] bool IsNot(FormType a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires((std::same_as<Args, FormType> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return DynamicCast<const T*>(this) == nullptr;
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is(T::FORM_TYPE) ? static_cast<T*>(this) : DynamicCast<T*>(this);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is(T::FORM_TYPE) ? static_cast<const T*>(this) : DynamicCast<const T*>(this);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] static T* FindFormByEditorID(const BSFixedString& a_editorID)
		{
			auto* form = FindFormByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] static T* FindFormByID(TESFormID a_formID)
		{
			return FindFormByNumericID<T>(a_formID);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] static T* FindFormByNumericID(TESFormID a_formID)
		{
			auto* form = FindFormByNumericID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		// members
		TESFileContainer sourceFiles;								  // 08
		REX::EnumSet<FormFlags, std::uint32_t> formFlags;			  // 10
		TESFormID formID;											  // 14
		REX::EnumSet<InGameFormFlags, std::uint16_t> inGameFormFlags; // 18
		REX::Enum<FormType, std::uint8_t> formType;					  // 1A
	};
	static_assert(sizeof(TESForm) == 0x20);
}
