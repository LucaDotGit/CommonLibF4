#pragma once

#include "RE/B/BGSChangeFlags.hpp"
#include "RE/B/BGSReconstructFormsInAllFilesMap.hpp"
#include "RE/B/BGSSaveLoadFormIDMap.hpp"
#include "RE/B/BGSSaveLoadHistory.hpp"
#include "RE/B/BGSSaveLoadQueuedSubBufferMap.hpp"
#include "RE/B/BGSSaveLoadReferencesMap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESFileCollection.hpp"

namespace RE
{
	class BGSLoadFormData;
	class BGSSaveLoadChangesMap;

	class BGSSaveLoadGame
	{
	public:
		[[nodiscard]] static BGSSaveLoadGame* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSSaveLoadGame**>{ ID::BGSSaveLoadGame::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] bool HasChangeFlag(TESFormID a_formID, BGSChangeFlags a_flags) const;
		[[nodiscard]] auto GetChangeFlags(TESFormID a_formID) const
			-> std::optional<BGSChangeFlags>;
		bool SetChangeFlags(TESFormID a_formID, BGSChangeFlags a_flags) const;
		bool AddChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const;
		bool RemoveChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const;
		bool ClearChangeFlags(TESFormID a_formID) const;

		// members
		TESFileCollection savedFiles;											   // 000
		BGSSaveLoadFormIDMap worldspaceFormIDMap;								   // 030
		BSTHashMap<std::uint32_t, ActorHandle> queuedInitPackageLocationsActorMap; // 098
		BSTArray<ObjectRefHandle> queuedMoveToEditorLocationArray;				   // 0C8
		BGSSaveLoadReferencesMap referencesMap;									   // 0E0
		BSTHashMap<std::uint32_t, std::uint32_t> changedFormIDMap;				   // 178
		BGSReconstructFormsInAllFilesMap reconstructForms;						   // 1A8
		BGSSaveLoadQueuedSubBufferMap queuedSubBuffersMap;						   // 228
		BGSSaveLoadFormIDMap formIDMap;											   // 2B8
		BGSSaveLoadHistory history;												   // 320
		BSTArray<BGSLoadFormData*> formDataArray;								   // 338
		BGSSaveLoadChangesMap* changesMap;										   // 350
		BGSSaveLoadChangesMap* oldChangesMap;									   // 358
		std::uint32_t globalFlags;												   // 360
		std::uint8_t currentMinorVersion;										   // 364
		BSFixedString savedGameVersion;											   // 368
	};
	static_assert(sizeof(BGSSaveLoadGame) == 0x370);
}
