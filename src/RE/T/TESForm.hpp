#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
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
	concept TESFormConstraint = std::derived_from<T, TESForm> &&
								!REX::pointer<T> &&
								!REX::reference<T> &&
								std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;
}

namespace RE
{
	enum class FormFlags : std::int32_t;

	class BGSLoadFormBuffer;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BGSSoundTagComponent;
	class BSReadWriteLock;
	class TBO_InstanceData;

	class __declspec(novtable) TESForm : public BaseFormComponent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESForm;
		inline static constexpr auto FORM_TYPE = FormType::None;

		inline static constexpr auto PLAYER_BASE_FORM_ID = static_cast<TESFormID>(0x07);
		inline static constexpr auto PLAYER_REF_FORM_ID = static_cast<TESFormID>(0x14);

		inline static constexpr auto PLAYER_BASE_EDITOR_ID = "Player"sv;
		inline static constexpr auto PLAYER_REF_EDITOR_ID = "PlayerRef"sv;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Created = 0,
				Flags = 1 << 0
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		enum class InGameFormFlags : std::uint16_t
		{
			None = 0,
			WantsDelete = 1 << 0,
			ForcedPersistent = 1 << 1,
			NoFavorAllowed = 1 << 4,
			IsSkyObject = 1 << 5,
			RefOriginalPersistent = 1 << 6,
			RefPermanentlyDeleted = 1 << 7
		};

		class FormSortFunc
		{
		public:
			[[nodiscard]]
			auto operator()(const TESForm* a_lhs, const TESForm* a_rhs) const noexcept -> std::int32_t;
		};

		static_assert(std::is_empty_v<FormSortFunc>);

		~TESForm() override; // 0x00

		// override (BaseFormComponent)
		void InitializeDataComponent() override;				// 0x02 - { return; }
		void ClearDataComponent() override;						// 0x03 - { SetFormEditorID(""); }
		void CopyComponent(BaseFormComponent* a_copy) override; // 0x06 - { return; }

		// add
		virtual void InitializeData();					   // 0x07 - { return; }
		virtual void ClearData();						   // 0x08 - { return; }
		virtual auto Load(TESFile* a_file) -> bool;		   // 0x09 - { return true; }
		virtual auto LoadPartial(TESFile* a_file) -> bool; // 0x0A - { return true; }
		virtual auto LoadEdit(TESFile* a_file) -> bool;	   // 0x0B - { return Load(a_file); }
		virtual auto CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap)
			-> TESForm*;																// 0x0C
		virtual auto AddChange(std::uint32_t a_changeFlags) -> bool;					// 0x0D
		virtual void RemoveChange(std::uint32_t a_changeFlags);							// 0x0E
		virtual auto FindInFileFast(TESFile* a_file) -> bool;							// 0x0F - { return false; }
		virtual auto CheckSaveGame(BGSSaveFormBuffer* a_saveGameBuffer) const -> bool;	// 0x10 - { return true; }
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);						// 0x11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);						// 0x12
		virtual void InitLoadGame(BGSLoadFormBuffer* a_loadGameBuffer);					// 0x13 - { return; }
		virtual void FinishLoadGame(BGSLoadFormBuffer* a_loadGameBuffer);				// 0x14 - { return; }
		virtual void Revert(BGSLoadFormBuffer* a_loadGameBuffer);						// 0x15 - { return; }
		virtual void InitItemImpl();													// 0x16 - { return; }
		virtual auto GetRevertFile() const -> TESFile*;									// 0x17
		virtual auto GetDescriptionOwnerFile() const -> TESFile*;						// 0x18
		virtual auto GetSavedFormType() const -> FormType;								// 0x19 - { return *formType; }
		virtual void GetFormDetailedString(char* a_target, std::uint32_t a_size) const; // 0x1A
		virtual auto GetKnown() const -> bool;		// 0x1B - { return formFlags.any(RecordFlags::Known); }
		virtual auto GetRandomAnim() const -> bool; // 0x1C - { return formFlags.any(RecordFlags::RandomAnim); }
		virtual auto GetPlayable(const TBO_InstanceData* a_data) const
			-> bool;									  // 0x1D - { return formFlags.any(RecordFlags::Playable); }
		virtual auto IsHeadingMarker() const -> bool;	  // 0x1E - { return false; }
		virtual auto IsHeadtrackMarker() const -> bool;	  // 0x1F - { return false; }
		virtual auto GetDangerous() const -> bool;		  // 0x20 - { return formFlags.any(RecordFlags::Dangerous); }
		virtual auto QHasCurrents() const -> bool;		  // 0x21 - { return formFlags.any(RecordFlags::HasCurrents); }
		virtual auto GetObstacle() const -> bool;		  // 0x22 - { return formFlags.any(RecordFlags::Obstacle); }
		virtual auto QIsLODLandObject() const -> bool;	  // 0x23 - { return false; }
		virtual auto GetOnLocalMap() const -> bool;		  // 0x24 - { return formFlags.any(RecordFlags::OnLocalMap); }
		virtual auto GetMustUpdate() const -> bool;		  // 0x25 - { return formFlags.any(RecordFlags::MustUpdate); }
		virtual void SetOnLocalMap(bool a_val);			  // 0x26
		virtual auto GetIgnoredBySandbox() const -> bool; // 0x27 - { return false; }
		virtual void SetDelete(bool a_deleted);			  // 0x28
		virtual void SetAltered(bool a_altered);		  // 0x29
		virtual void SaveObjectBound();					  // 0x2A - { return; }
		virtual void LoadObjectBound(TESFile* a_file);	  // 0x2B - { return; }
		virtual void SavePreviewTransform(CHUNK_ID a_chunkID);	  // 0x2C - { return; }
		virtual void LoadPreviewTransform(TESFile* a_file);		  // 0x2D - { return; }
		virtual auto IsBoundObject() const -> bool;				  // 0x2E - { return false; }
		virtual auto IsObject() const -> bool;					  // 0x2F - { return false; }
		virtual auto IsMagicItem() const -> bool;				  // 0x30 - { return false; }
		virtual auto IsWater() const -> bool;					  // 0x31 - { return false; }
		virtual auto IsReference() -> TESObjectREFR*;			  // 0x33 - { return nullptr; }
		virtual auto IsReference() const -> const TESObjectREFR*; // 0x32 - { return nullptr; }
		virtual auto GetRefCount() const -> std::uint32_t;		  // 0x34 - { return 0; }
		virtual auto GetTextForParsedSubTag(const BSFixedString& a_subTag) const -> const char*; // 0x35
		virtual void Copy(TESForm* a_copy);														 // 0x36 - { return; }
		virtual auto BelongsInGroup(FORM* a_groupFORM, bool a_allowParentGroups, bool a_currentOnly) -> bool; // 0x37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);						  // 0x38
		virtual auto GetFormEditorIDLength() const -> std::uint32_t;										  // 0x39
		virtual auto GetFormEditorID() const -> const char*;		  // 0x3A - { return ""; }
		virtual auto SetFormEditorID(const char* a_editorID) -> bool; // 0x3B - { return true; }
		virtual auto IsParentForm() -> bool;						  // 0x3C - { return false; }
		virtual auto IsParentFormTree() -> bool;					  // 0x3D - { return false; }
		virtual auto IsFormTypeChild(std::uint8_t a_type) -> bool;	  // 0x3E - { return false; }
		virtual auto LoopingActivate(
			TESObjectREFR* a_itemActivated,
			TESObjectREFR* a_actionRef)
			-> bool; // 0x3F - { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }
		virtual auto Activate(
			TESObjectREFR* a_itemActivated,
			TESObjectREFR* a_actionRef,
			TESBoundObject* a_objectToGet,
			std::int32_t a_count) -> bool;							   // 0x40 - { return false; }
		virtual void SetFormID(TESFormID a_formID, bool a_updateFile); // 0x41
		virtual auto GetObjectTypeName() const -> const char*;		   // 0x42 - { return ""; }
		virtual auto QAvailableInGame() const -> bool;				   // 0x43 - { return true; }
		virtual auto GetObjectTemplate() -> BGSMod::Template::Items*;  // 0x44 - { return nullptr; }
		virtual auto GetPreviewTransform() -> BGSPreviewTransform*;	   // 0x45 - { return nullptr; }
		virtual auto GetSoundTagComponent() -> BGSSoundTagComponent*;  // 0x46 - { return nullptr; }
		virtual auto GetFilledSlots() const -> std::uint32_t;		   // 0x47
		virtual auto GetFilledSlotsImpl() const
			-> std::uint32_t; // 0x48 - { return std::numeric_limits<std::uint32_t>::max(); }
		virtual auto GetDesirability(TBO_InstanceData* a_instanceData, const TESForm* a_user) const
			-> REX::Float32; // 0x49 - { return static_cast<REX::Float32>(0.0); }

		static void AddCompileIndex(std::uint32_t& a_id, TESFile* a_file);
		[[nodiscard]]
		static auto GetTotalFormCount() noexcept -> std::uint32_t&;
		[[nodiscard]]
		static auto GetAllFormsByEditorID() noexcept
			-> std::pair<BSTHashMap<BSFixedString, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]]
		static auto GetAllFormsByID() noexcept
			-> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]]
		static auto GetAllFormsByNumericID() noexcept
			-> std::pair<BSTHashMap<TESFormID, TESForm*>*, std::reference_wrapper<BSReadWriteLock>>;
		[[nodiscard]]
		auto GetFile(std::int32_t a_index = -1) const -> TESFile*;
		[[nodiscard]]
		static auto FindFormByEditorID(const BSFixedString& a_editorID) noexcept -> TESForm*;
		[[nodiscard]]
		static auto FindFormByID(TESFormID a_formID) noexcept -> TESForm*;
		[[nodiscard]]
		static auto FindFormByNumericID(TESFormID a_formID) noexcept -> TESForm*;
		[[nodiscard]]
		static auto GetEditorIDByForm(const TESForm* a_form) noexcept -> std::optional<BSFixedString>;
		[[nodiscard]]
		auto GetFormTypeString() const -> std::string_view;
		[[nodiscard]]
		auto GetFormFlags() const noexcept -> FormFlags;
		[[nodiscard]]
		auto GetFormID() const noexcept -> TESFormID;
		[[nodiscard]]
		auto GetFormType() const noexcept -> FormType;
		[[nodiscard]]
		auto GetLocalFormID() const -> TESFormID;
		[[nodiscard]]
		auto IsAlchemyItem() const noexcept -> bool;
		[[nodiscard]]
		auto IsCreated() const noexcept -> bool;
		[[nodiscard]]
		auto IsDeleted() const noexcept -> bool;
		[[nodiscard]]
		auto IsDisabled() const noexcept -> bool;
		[[nodiscard]]
		auto IsInitialized() const noexcept -> bool;
		[[nodiscard]]
		auto IsPlayer() const noexcept -> bool;
		[[nodiscard]]
		auto IsPlayerRef() const noexcept -> bool;
		[[nodiscard]]
		auto IsWeapon() const noexcept -> bool;
		void SetInGameFormFlags(InGameFormFlags a_flags, bool a_value);
		void SetTemporary();

		[[nodiscard]]
		static auto CanHoldKeywords(const TESForm* a_form) noexcept -> bool;
		[[nodiscard]]
		static auto ContainsKeyword(const TESForm* a_form, const BGSKeyword* a_keyword) noexcept -> std::optional<bool>;
		[[nodiscard]]
		static auto GetKeywordCount(const TESForm* a_form) noexcept -> std::optional<std::uint32_t>;
		[[nodiscard]]
		static auto GetKeywordIndex(const TESForm* a_form, const BGSKeyword* a_keyword) noexcept
			-> std::optional<std::uint32_t>;

		[[nodiscard]]
		static auto GetKeywords(const TESForm* a_form) -> std::optional<BSTArray<BGSKeyword*>>;
		static auto SetKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords) -> std::optional<bool>;

		[[nodiscard]]
		static auto GetNthKeyword(const TESForm* a_form, std::uint32_t a_index) noexcept -> std::optional<BGSKeyword*>;
		static auto SetNthKeyword(TESForm* a_form, std::uint32_t a_index, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto RemoveNthKeyword(TESForm* a_form, std::uint32_t a_index) -> std::optional<bool>;

		static auto AddKeyword(TESForm* a_form, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto RemoveKeyword(TESForm* a_form, BGSKeyword* a_keyword) -> std::optional<bool>;
		static auto ReplaceKeyword(TESForm* a_form, BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword)
			-> std::optional<bool>;

		static auto AddKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords) -> bool;
		static auto RemoveKeywords(TESForm* a_form, std::span<BGSKeyword*> a_keywords) -> bool;
		static auto ClearKeywords(TESForm* a_form) noexcept -> bool;

		static auto ForEachKeyword(
			const TESForm* a_form,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate)
			-> BSContainer::ForEachResult;

		[[nodiscard]]
		auto Is(FormType a_type) const noexcept -> bool
		{
			return GetFormType() == a_type;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, FormType> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return DynamicCast<const T*>(this) != nullptr;
		}

		[[nodiscard]]
		auto IsNot(FormType a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, FormType> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return DynamicCast<const T*>(this) == nullptr;
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is(T::FORM_TYPE) ? static_cast<T*>(this) : DynamicCast<T*>(this);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is(T::FORM_TYPE) ? static_cast<const T*>(this) : DynamicCast<const T*>(this);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		static auto FindFormByEditorID(const BSFixedString& a_editorID) noexcept -> T*
		{
			// NOLINTNEXTLINE(misc-const-correctness)
			auto* form = FindFormByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		static auto FindFormByID(TESFormID a_formID) noexcept -> T*
		{
			return FindFormByNumericID<T>(a_formID);
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		static auto FindFormByNumericID(TESFormID a_formID) noexcept -> T*
		{
			// NOLINTNEXTLINE(misc-const-correctness)
			auto* form = FindFormByNumericID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		// members
		TESFileContainer sourceFiles;								  // 0x08
		REX::EnumSet<FormFlags, std::uint32_t> formFlags;			  // 0x10
		TESFormID formID;											  // 0x14
		REX::EnumSet<InGameFormFlags, std::uint16_t> inGameFormFlags; // 0x18
		REX::Enum<FormType, std::uint8_t> formType;					  // 0x1A
	};

	static_assert(sizeof(TESForm) == 0x20);
}
