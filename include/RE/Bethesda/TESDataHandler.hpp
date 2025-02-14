#pragma once

#include "RE/Bethesda/BSExtraData.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTList.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/TESFile.hpp"
#include "RE/Bethesda/TESForms.hpp"
#include "RE/NetImmerse/NiTArray.hpp"
#include "RE/NetImmerse/NiTList.hpp"

namespace RE
{
	struct BGSHotloadCompletedEvent;

	class BGSObjectInstanceExtra;
	class BGSPrimitive;
	class NiPoint3;
	class TESObjectList;
	class TESRegionDataManager;
	class TESRegionList;

	class __declspec(novtable) NEW_REFR_DATA
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NEW_REFR_DATA };
		inline static constexpr auto VTABLE{ VTABLE::NEW_REFR_DATA };

		NEW_REFR_DATA()
		{
			stl::emplace_vtable(this);
		}

		virtual void HandlePre3D(TESObjectREFR*) { return; }

		// members
		NiPoint3 location;								 // 08
		NiPoint3 direction;								 // 14
		TESBoundObject* object{ nullptr };				 // 20
		TESObjectCELL* interior{ nullptr };				 // 28
		TESWorldSpace* world{ nullptr };				 // 30
		TESObjectREFR* reference{ nullptr };			 // 38
		BGSPrimitive* addPrimitive{ nullptr };			 // 40
		void* additionalData{ nullptr };				 // 48
		BSTSmartPointer<ExtraDataList> extra{ nullptr }; // 50
		INSTANCE_FILTER* instanceFilter{ nullptr };		 // 58
		BGSObjectInstanceExtra* modExtra{ nullptr };	 // 60
		std::uint16_t maxLevel{ 0 };					 // 68
		bool forcePersist{ false };						 // 6A
		bool clearStillLoadingFlag{ false };			 // 6B
		bool initializeScripts{ true };					 // 6C
		bool initiallyDisabled{ false };				 // 6D
	};
	static_assert(sizeof(NEW_REFR_DATA) == 0x70);

	struct TESFileCollection
	{
	public:
		// members
		BSTArray<TESFile*> files;	   // 00
		BSTArray<TESFile*> smallFiles; // 18
	};
	static_assert(sizeof(TESFileCollection) == 0x30);

	class TESDataHandler
		: public BSTEventSource<BGSHotloadCompletedEvent>, // 0000
		  public BSTSingletonSDM<TESDataHandler>		   // 0058
	{
	public:
		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                \
	BSTArray<RE::TESFormID> releasedFormIDArray; /* 0FF0 */ \
	bool masterSave;							 /* 1008 */ \
	bool blockSave;								 /* 1009 */ \
	bool saveLoadGame;							 /* 100A */ \
	bool autoSaving;							 /* 100B */ \
	bool exportingPlugin;						 /* 100C */ \
	bool clearingData;							 /* 100D */ \
	bool hasDesiredFiles;						 /* 100E */ \
	bool checkingModels;						 /* 100F */ \
	bool loadingFiles;							 /* 1010 */ \
	bool dontRemoveIDs;							 /* 1011 */ \
	char gameSettingsLoadState;					 /* 1012*/
			RUNTIME_DATA_CONTENT
		};

		struct VR_MOD_DATA
		{
#define VR_MOD_DATA_CONTENT                  \
	std::uint32_t loadedModCount; /* 0FC0 */ \
	std::uint32_t pad14;		  /* 0FC4 */ \
	TESFile* loadedMods[0xFF];	  /* 0FC8 */
			VR_MOD_DATA_CONTENT
		};

		inline static RE::TESFileCollection* VRcompiledFileCollection = nullptr; // used by FalloutVRESL to store pointer to VR version

		[[nodiscard]] static TESDataHandler* GetSingleton(bool a_VRESL = true);

		[[nodiscard]] ObjectRefHandle CreateReferenceAtLocation(NEW_REFR_DATA& a_data);

		bool AddFormToDataHandler(TESForm* a_form);
		[[nodiscard]] bool CheckModsLoaded(bool a_everModded) const;
		[[nodiscard]] bool IsFormIDInUse(std::uint32_t a_formID) const;

		template <class T>
		[[nodiscard]] BSTArray<T*>& GetFormArray() //
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			assert(T::FORMTYPE < ENUM_FORMTYPE::kTotal);
			return reinterpret_cast<BSTArray<T*>&>(formArrays[std::to_underlying(T::FORMTYPE)]);
		}

		template <class T>
		[[nodiscard]] const BSTArray<T*>& GetFormArray() const //
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			assert(T::FORMTYPE < ENUM_FORMTYPE::kTotal);
			return reinterpret_cast<const BSTArray<T*>&>(formArrays[std::to_underlying(T::FORMTYPE)]);
		}

		[[nodiscard]] TESFormID LookupFormID(TESFormID a_rawFormID, std::string_view a_modName) const;
		[[nodiscard]] TESForm* LookupForm(TESFormID a_rawFormID, std::string_view a_modName) const;

		template <class T>
		[[nodiscard]] T* LookupForm(TESFormID a_rawFormID, std::string_view a_modName) const
		{
			auto form = LookupForm(a_rawFormID, a_modName);
			if (!form) {
				return nullptr;
			}

			return form->Is(T::FORMTYPE) ? form->As<T>() : nullptr;
		}

		[[nodiscard]] const std::pair<TESFile*, bool> LookupLoadedFile(std::string_view a_fileName) const;

		[[nodiscard]] const TESFile* LookupModByName(std::string_view a_modName) const;
		[[nodiscard]] const TESFile* LookupLoadedModByName(std::string_view a_modName) const;
		[[nodiscard]] const TESFile* LookupLoadedLightModByName(std::string_view a_modName) const;

		[[nodiscard]] const TESFile* LookupLoadedModByIndex(std::uint8_t a_index) const;
		[[nodiscard]] const TESFile* LookupLoadedLightModByIndex(std::uint16_t a_index) const;

		[[nodiscard]] std::optional<std::uint8_t> GetModIndex(std::string_view a_modName) const;
		[[nodiscard]] std::optional<std::uint8_t> GetLoadedModIndex(std::string_view a_modName) const;
		[[nodiscard]] std::optional<std::uint16_t> GetLoadedLightModIndex(std::string_view a_modName) const;

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x0FF0, 0x0FF0);
		}

		[[nodiscard]] inline const RUNTIME_DATA GetRuntimeData() const noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x0FF0, 0x0FF0);
		}

		[[nodiscard]] inline VR_MOD_DATA* GetVRModData() noexcept
		{
			if FALLOUT_REL_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_MOD_DATA>(this, 0, 0xFC0);
			}
			return nullptr;
		}

		[[nodiscard]] inline const VR_MOD_DATA* GetVRModData() const noexcept
		{
			if FALLOUT_REL_CONSTEXPR (REL::Module::IsVR()) {
				return &REL::RelocateMember<VR_MOD_DATA>(this, 0, 0xFC0);
			}
			return nullptr;
		}

		[[nodiscard]] inline TESFileCollection* GetCompiledFileCollection() noexcept
		{
			if FALLOUT_REL_CONSTEXPR (REL::Module::IsVR()) {
				return VRcompiledFileCollection;
			}
			else {
				return &REL::RelocateMember<TESFileCollection>(this, 0xFC0, 0);
			}
		}

		[[nodiscard]] inline const TESFileCollection* GetCompiledFileCollection() const noexcept
		{
			if FALLOUT_REL_CONSTEXPR (REL::Module::IsVR()) {
				return VRcompiledFileCollection;
			}
			else {
				return REL::RelocateMember<TESFileCollection*>(this, 0xFC0, 0);
			}
		}

		[[nodiscard]] inline TESRegionDataManager* GetRegionDataManager() noexcept
		{
			return REL::RelocateMember<TESRegionDataManager*>(this, 0x1018, 0x17E8);
		}

		[[nodiscard]] inline const TESRegionDataManager* GetRegionDataManager() const noexcept
		{
			return REL::RelocateMember<TESRegionDataManager*>(this, 0x1018, 0x17E8);
		}

		// members
		TESObjectList* objectList;												  // 0060
		BSTArray<TESForm*> formArrays[std::to_underlying(ENUM_FORMTYPE::kTotal)]; // 0068
		TESRegionList* regionList;												  // 0F50
		NiTPrimitiveArray<TESObjectCELL*> interiorCells;						  // 0F58
		NiTPrimitiveArray<BGSAddonNode*> addonNodes;							  // 0F70
		NiTList<TESForm*> badForms;												  // 0F88
		TESFormID nextID;														  // 0FA0
		TESFile* activeFile;													  // 0FA8
		BSSimpleList<TESFile*> files;											  // 0FB0
#if !defined(ENABLE_FALLOUT_VR)
		TESFileCollection compiledFileCollection; // 0FC0
		RUNTIME_DATA_CONTENT
		TESRegionDataManager* regionDataManager; // 1018, VR 17E8
#elif !defined(ENABLE_FALLOUT_NG) && !defined(ENABLE_FALLOUT_F4)
		VR_MOD_DATA_CONTENT
		RUNTIME_DATA_CONTENT
		TESRegionDataManager* regionDataManager; // 1018, VR 17E8
#endif
	};
#if !defined(ENABLE_FALLOUT_VR)
	static_assert(sizeof(TESDataHandler) == 0x1020);
	static_assert(offsetof(TESDataHandler, regionDataManager) == 0x1018);
	static_assert(offsetof(TESDataHandler, compiledFileCollection) == 0xFC0);
#elif !defined(ENABLE_FALLOUT_NG) && !defined(ENABLE_FALLOUT_F4)
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
