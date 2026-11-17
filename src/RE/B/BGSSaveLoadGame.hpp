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
		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSSaveLoadGame*
		{
			static const auto SINGLETON = REL::Relocation<BGSSaveLoadGame**>(ID::BGSSaveLoadGame::Singleton);
			return *SINGLETON;
		}

		[[nodiscard]]
		auto HasChangeFlag(TESFormID a_formID, BGSChangeFlags a_flags) const -> bool;
		[[nodiscard]]
		auto GetChangeFlags(TESFormID a_formID) const -> std::optional<BGSChangeFlags>;
		auto SetChangeFlags(TESFormID a_formID, BGSChangeFlags a_flags) const -> bool;
		auto AddChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const -> bool;
		auto RemoveChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const -> bool;
		auto ClearChangeFlags(TESFormID a_formID) const -> bool;

		// members
		TESFileCollection savedFiles;											   // 0x000
		BGSSaveLoadFormIDMap worldspaceFormIDMap;								   // 0x030
		BSTHashMap<std::uint32_t, ActorHandle> queuedInitPackageLocationsActorMap; // 0x098
		BSTArray<ObjectRefHandle> queuedMoveToEditorLocationArray;				   // 0x0C8
		BGSSaveLoadReferencesMap referencesMap;									   // 0x0E0
		BSTHashMap<std::uint32_t, std::uint32_t> changedFormIDMap;				   // 0x178
		BGSReconstructFormsInAllFilesMap reconstructForms;						   // 0x1A8
		BGSSaveLoadQueuedSubBufferMap queuedSubBuffersMap;						   // 0x228
		BGSSaveLoadFormIDMap formIDMap;											   // 0x2B8
		BGSSaveLoadHistory history;												   // 0x320
		BSTArray<BGSLoadFormData*> formDataArray;								   // 0x338
		BGSSaveLoadChangesMap* changesMap;										   // 0x350
		BGSSaveLoadChangesMap* oldChangesMap;									   // 0x358
		std::uint32_t globalFlags;												   // 0x360
		std::uint8_t currentMinorVersion;										   // 0x364
		BSFixedString savedGameVersion;											   // 0x368
	};

	static_assert(sizeof(BGSSaveLoadGame) == 0x370);
}
