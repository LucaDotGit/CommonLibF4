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
	class NEW_REFR_DATA;
	class TESFile;
	class TESObjectList;
	class TESRegionDataManager;
	class TESRegionList;

	class TESDataHandler
		: public BSTEventSource<BGSHotloadCompletedEvent>, // 00
		  public BSTSingletonSDM<TESDataHandler>		   // 58
	{
	public:
		inline static constexpr auto FORM_INDEX_MASK = 0xFF000000ui32;
		inline static constexpr auto LIGHT_FORM_INDEX_MASK = 0x00FFF000ui32;

		inline static constexpr auto FORM_INDEX_SHIFT = 24ui32;
		inline static constexpr auto LIGHT_FORM_INDEX_SHIFT = 12ui32;

		inline static constexpr auto LOCAL_FORM_ID_MASK = 0x00FFFFFFui32;
		inline static constexpr auto LIGHT_LOCAL_FORM_ID_MASK = 0x00000FFFui32;

		inline static constexpr auto EMPTY_RUNTIME_FORM_ID = 0xFF000000ui32;
		inline static constexpr auto EMPTY_LIGHT_FORM_ID = 0xFE000000ui32;
		inline static constexpr auto EMPTY_FORM_ID = 0x00000000ui32;

#define RUNTIME_DATA_CONTENT                            \
	BSTArray<TESFormID> releasedFormIDArray; /* 0FF0 */ \
	bool masterSave;						 /* 1008 */ \
	bool blockSave;							 /* 1009 */ \
	bool saveLoadGame;						 /* 100A */ \
	bool autoSaving;						 /* 100B */ \
	bool exportingPlugin;					 /* 100C */ \
	bool clearingData;						 /* 100D */ \
	bool hasDesiredFiles;					 /* 100E */ \
	bool checkingModels;					 /* 100F */ \
	bool loadingFiles;						 /* 1010 */ \
	bool dontRemoveIDs;						 /* 1011 */ \
	std::int8_t gameSettingsLoadState;		 /* 1012 */

#define VR_MOD_DATA_CONTENT                           \
	std::uint32_t loadedModCount;		   /* 0FC0 */ \
	std::array<TESFile*, 0xFF> loadedMods; /* 0FC8 */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT;
		};

		class VRModData
		{
		public:
			// members
			VR_MOD_DATA_CONTENT;
		};

		[[nodiscard]] static TESDataHandler* GetSingleton();

		[[nodiscard]] bool AddFormToDataHandler(TESForm* a_form);
		[[nodiscard]] ObjectRefHandle CreateReferenceAtLocation(NEW_REFR_DATA& a_data);
		[[nodiscard]] TESWorldSpace* GetExtCellDataFromFileByEditorID(const char* a_cellEditorID, std::int32_t& a_outX, std::int32_t& a_outY);

		[[nodiscard]] bool IsFormIDInUse(TESFormID a_formID) const;
		[[nodiscard]] bool CheckModsLoaded(bool a_everModded) const;
		[[nodiscard]] bool IsFileLoaded(std::string_view a_fileName) const;

		[[nodiscard]] std::uint32_t GetFileCount() const;
		[[nodiscard]] std::uint32_t GetLoadedFileCount() const;

		[[nodiscard]] std::uint32_t GetTotalFormCount() const;
		[[nodiscard]] std::uint32_t GetTotalLoadedFormCount() const;

		[[nodiscard]] BSTArray<TESForm*>& GetFormArray(FormType a_formType) noexcept;
		[[nodiscard]] const BSTArray<TESForm*>& GetFormArray(FormType a_formType) const noexcept;

		[[nodiscard]] static TESFormID GetLocalFormID(TESFormID a_formID) noexcept;

		[[nodiscard]] auto FindFormID(TESFormID a_localFormID, std::string_view a_fileName) const
			-> std::optional<TESFormID>;
		[[nodiscard]] auto FindForm(TESFormID a_localFormID, std::string_view a_fileName) const
			-> TESForm*;
		[[nodiscard]] auto FindFormOrRef(TESFormID a_localFormID, std::string_view a_fileName) const
			-> std::optional<std::variant<TESForm*, NiPointer<TESObjectREFR>>>;

		[[nodiscard]] TESFile* FindFileByName(std::string_view a_fileName) const;
		[[nodiscard]] TESFile* FindFileByFormID(TESFormID a_formID) const;
		[[nodiscard]] TESFile* FindFileByIndex(std::uint16_t a_index) const;

		[[nodiscard]] TESFile* FindLoadedFileByName(std::string_view a_fileName) const;
		[[nodiscard]] TESFile* FindLoadedFileByFormID(TESFormID a_formID) const;
		[[nodiscard]] TESFile* FindLoadedFileByIndex(std::uint16_t a_index) const;

		[[nodiscard]] auto FindFileIndex(std::string_view a_fileName) const
			-> std::optional<std::uint16_t>;
		[[nodiscard]] auto FindLoadedFileIndex(std::string_view a_fileName) const
			-> std::optional<std::uint16_t>;

		[[nodiscard]] RuntimeData& GetRuntimeData() noexcept;
		[[nodiscard]] const RuntimeData& GetRuntimeData() const noexcept;

		[[nodiscard]] VRModData* GetVRModData() noexcept;
		[[nodiscard]] const VRModData* GetVRModData() const noexcept;

		[[nodiscard]] TESRegionDataManager* GetRegionDataManager() noexcept;
		[[nodiscard]] const TESRegionDataManager* GetRegionDataManager() const noexcept;

		template <Impl::TESFormConstraint T>
		[[nodiscard]] BSTArray<T*>& GetFormArray() noexcept
		{
			return reinterpret_cast<BSTArray<T*>&>(GetFormArray(T::FORM_TYPE));
		}

		template <Impl::TESFormConstraint T>
		[[nodiscard]] const BSTArray<T*>& GetFormArray() const noexcept
		{
			return reinterpret_cast<const BSTArray<T*>&>(GetFormArray(T::FORM_TYPE));
		}

		template <class T>
		[[nodiscard]] T* FindForm(TESFormID a_localFormID, std::string_view a_fileName) const
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			auto* form = FindForm(a_localFormID, a_fileName);
			return form ? form->As<T>() : nullptr;
		}

		BSContainer::ForEachResult ForEachFile(
			const REX::NotNull<std::function<BSContainer::ForEachResult(TESFile*)>>& a_predicate) const;

		// members
		TESObjectList* objectList;														 // 0060
		std::array<BSTArray<TESForm*>, std::to_underlying(FormType::kTotal)> formArrays; // 0068
		TESRegionList* regionList;														 // 0F50
		NiTPrimitiveArray<TESObjectCELL*> interiorCells;								 // 0F58
		NiTPrimitiveArray<BGSAddonNode*> addonNodes;									 // 0F70
		NiTList<TESForm*> badForms;														 // 0F88
		TESFormID nextID;																 // 0FA0
		TESFile* activeFile;															 // 0FA8
		BSSimpleList<TESFile*> files;													 // 0FB0
#if COMMONLIB_RUNTIME_VR == 0
		TESFileCollection compiledFileCollection; // 0FC0
		RUNTIME_DATA_CONTENT;					  // 0FF0
		TESRegionDataManager* regionDataManager;  // 1018
#elif COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
		VR_MOD_DATA_CONTENT;					 // 0FC0
		RUNTIME_DATA_CONTENT;					 // 17B8
		TESRegionDataManager* regionDataManager; // 17E8
#endif
	};
#if COMMONLIB_RUNTIME_VR == 0
	static_assert(sizeof(TESDataHandler) == 0x1020);
	static_assert(offsetof(TESDataHandler, regionDataManager) == 0x1018);
	static_assert(offsetof(TESDataHandler, compiledFileCollection) == 0xFC0);
#elif COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(TESDataHandler) == 0x17F0);
	static_assert(offsetof(TESDataHandler, regionDataManager) == 0x17E8);
	static_assert(offsetof(TESDataHandler, loadedModCount) == 0xFC0);
	static_assert(offsetof(TESDataHandler, loadedMods) == 0xFC8);
#else
	static_assert(sizeof(TESDataHandler) == 0xFC0);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef VR_MOD_DATA_CONTENT
