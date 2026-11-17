#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/F/FormType.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTArray.hpp"
#include "RE/N/NiTList.hpp"
#include "RE/T/TESFileCollection.hpp"
#include "RE/T/TESForm.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class BGSHotloadCompletedEvent;
	class LoadingMenu;
	class NEW_REFR_DATA;
	class TESFile;
	class TESObjectList;
	class TESRegionDataManager;
	class TESRegionList;

	class TESDataHandler :
		public BSTEventSource<BGSHotloadCompletedEvent>, // 0x00
		public BSTSingletonSDM<TESDataHandler>			 // 0x58
	{
	public:
		inline static constexpr auto FORM_INDEX_MASK = static_cast<TESFormID>(0xFF00'0000);
		inline static constexpr auto LIGHT_FORM_INDEX_MASK = static_cast<TESFormID>(0x00FF'F000);

		inline static constexpr auto FORM_INDEX_SHIFT = static_cast<std::uint32_t>(24);
		inline static constexpr auto LIGHT_FORM_INDEX_SHIFT = static_cast<std::uint32_t>(12);

		inline static constexpr auto LOCAL_FORM_ID_MASK = static_cast<TESFormID>(0x00FF'FFFF);
		inline static constexpr auto LIGHT_LOCAL_FORM_ID_MASK = static_cast<TESFormID>(0x0000'0FFF);

		inline static constexpr auto EMPTY_RUNTIME_FORM_ID = static_cast<TESFormID>(0xFF00'0000);
		inline static constexpr auto EMPTY_LIGHT_FORM_ID = static_cast<TESFormID>(0xFE00'0000);
		inline static constexpr auto EMPTY_FORM_ID = static_cast<TESFormID>(0x0000'0000);

		class CollectGoodLoadingScreensFunctor
		{
		public:
			// members
			LoadingMenu* loadingMenu;									   // 0x00
			std::uint32_t* numNonDefaultScreens;						   // 0x08
			BSScrapArray<TESLoadScreen*>* artScreensA;					   // 0x10
			BSTArray<TESLoadScreen*, BSTArrayHeapAllocator>* validScreens; // 0x18
			std::uint32_t artNonDefault;								   // 0x20
		};

#define RUNTIME_DATA_CONTENT                          \
	BSTArray<TESFormID> releasedFormIDArray; /* 00 */ \
	bool masterSave;						 /* 18 */ \
	bool blockSave;							 /* 19 */ \
	bool saveLoadGame;						 /* 1A */ \
	bool autoSaving;						 /* 1B */ \
	bool exportingPlugin;					 /* 1C */ \
	bool clearingData;						 /* 1D */ \
	bool hasDesiredFiles;					 /* 1E */ \
	bool checkingModels;					 /* 1F */ \
	bool loadingFiles;						 /* 20 */ \
	bool dontRemoveIDs;						 /* 21 */ \
	std::int8_t gameSettingsLoadState;		 /* 22 */

#define VR_MOD_DATA_CONTENT                          \
	std::uint32_t loadedModCount;		   /* FC0 */ \
	std::array<TESFile*, 0xFF> loadedMods; /* FC8 */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x00
		};

		static_assert(sizeof(RuntimeData) == 0x28);

		class VRModData
		{
		public:
			// members
			VR_MOD_DATA_CONTENT; // 0x000
		};

		static_assert(sizeof(VRModData) == 0x800);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> TESDataHandler*;

		[[nodiscard]]
		auto AddFormToDataHandler(TESForm* a_form) -> bool;
		[[nodiscard]]
		auto CreateReferenceAtLocation(NEW_REFR_DATA& a_data) -> ObjectRefHandle;
		[[nodiscard]]
		auto GetExtCellDataFromFileByEditorID(const char* a_cellEditorID, std::int32_t& a_outX, std::int32_t& a_outY)
			-> TESWorldSpace*;

		void CollectGoodLoadingScreensFunctor(FormType a_formType, CollectGoodLoadingScreensFunctor& a_functor);

		[[nodiscard]]
		auto IsFormIDInUse(TESFormID a_formID) const -> bool;
		[[nodiscard]]
		auto CheckModsLoaded(bool a_everModded) const -> bool;
		[[nodiscard]]
		auto IsFileLoaded(std::string_view a_fileName) const -> bool;

		[[nodiscard]]
		auto GetFileCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetLoadedFileCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetTotalFormCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetTotalLoadedFormCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetFormArray(FormType a_formType) noexcept -> BSTArray<TESForm*>&;
		[[nodiscard]]
		auto GetFormArray(FormType a_formType) const noexcept -> const BSTArray<TESForm*>&;

		[[nodiscard]]
		static auto GetLocalFormID(TESFormID a_formID) noexcept -> TESFormID;

		[[nodiscard]]
		auto FindFormID(TESFormID a_localFormID, std::string_view a_fileName) const noexcept
			-> std::optional<TESFormID>;
		[[nodiscard]]
		auto FindForm(TESFormID a_localFormID, std::string_view a_fileName) const noexcept -> TESForm*;
		[[nodiscard]]
		auto FindFormOrRef(TESFormID a_localFormID, std::string_view a_fileName) const noexcept
			-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;

		[[nodiscard]]
		auto FindFileByName(std::string_view a_fileName) const noexcept -> TESFile*;
		[[nodiscard]]
		auto FindFileByFormID(TESFormID a_formID) const noexcept -> TESFile*;
		[[nodiscard]]
		auto FindFileByIndex(std::uint16_t a_index) const noexcept -> TESFile*;

		[[nodiscard]]
		auto FindLoadedFileByName(std::string_view a_fileName) const noexcept -> TESFile*;
		[[nodiscard]]
		auto FindLoadedFileByFormID(TESFormID a_formID) const noexcept -> TESFile*;
		[[nodiscard]]
		auto FindLoadedFileByIndex(std::uint16_t a_index) const noexcept -> TESFile*;

		[[nodiscard]]
		auto FindFileIndex(std::string_view a_fileName) const noexcept -> std::optional<std::uint16_t>;
		[[nodiscard]]
		auto FindLoadedFileIndex(std::string_view a_fileName) const noexcept -> std::optional<std::uint16_t>;

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		[[nodiscard]]
		auto GetVRModData() noexcept -> VRModData*;
		[[nodiscard]]
		auto GetVRModData() const noexcept -> const VRModData*;

		[[nodiscard]]
		auto GetRegionDataManager() noexcept -> TESRegionDataManager*;
		[[nodiscard]]
		auto GetRegionDataManager() const noexcept -> const TESRegionDataManager*;

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto GetFormArray() noexcept -> BSTArray<T*>&
		{
			return REX::CheckedReinterpretCast<BSTArray<T*>&>(GetFormArray(T::FORM_TYPE));
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]]
		auto GetFormArray() const noexcept -> const BSTArray<T*>&
		{
			return REX::CheckedReinterpretCast<const BSTArray<T*>&>(GetFormArray(T::FORM_TYPE));
		}

		template <class T>
		[[nodiscard]]
		auto FindForm(TESFormID a_localFormID, std::string_view a_fileName) const noexcept -> T*
			requires(std::derived_from<T, TESForm> && !REX::pointer<T> && !REX::reference<T>)
		{
			// NOLINTNEXTLINE(misc-const-correctness)
			auto* form = FindForm(a_localFormID, a_fileName);
			return form ? form->As<T>() : nullptr;
		}

		auto ForEachFile(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESFile*) const>>& a_predicate) const
			-> BSContainer::ForEachResult;

		// members
		TESObjectList* objectList;														 // 0x0060
		std::array<BSTArray<TESForm*>, std::to_underlying(FormType::_Count)> formArrays; // 0x0068
		TESRegionList* regionList;														 // 0x0F50
		NiTPrimitiveArray<TESObjectCELL*> interiorCells;								 // 0x0F58
		NiTPrimitiveArray<BGSAddonNode*> addonNodes;									 // 0x0F70
		NiTList<TESForm*> badForms;														 // 0x0F88
		TESFormID nextID;																 // 0x0FA0
		TESFile* activeFile;															 // 0x0FA8
		BSSimpleList<TESFile*> files;													 // 0x0FB0
#if (COMMONLIB_RUNTIME_VR == 0)
		TESFileCollection compiledFileCollection; // 0x0FC0
		RUNTIME_DATA_CONTENT;					  // 0x0FF0
		TESRegionDataManager* regionDataManager;  // 0x1018
#elif (COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
		VR_MOD_DATA_CONTENT;					 // 0x0FC0
		RUNTIME_DATA_CONTENT;					 // 0x17B8
		TESRegionDataManager* regionDataManager; // 0x17E8
#endif
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(TESDataHandler) == 0x1020);
#elif (COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(TESDataHandler) == 0x17F0);
#else
	static_assert(sizeof(TESDataHandler) == 0x0FC0);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef VR_MOD_DATA_CONTENT
