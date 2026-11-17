#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/P/PipboyInventoryData.hpp"
#include "RE/P/PipboyLogData.hpp"
#include "RE/P/PipboyMapData.hpp"
#include "RE/P/PipboyObject.hpp"
#include "RE/P/PipboyPerksData.hpp"
#include "RE/P/PipboyPlayerInfoData.hpp"
#include "RE/P/PipboyQuestData.hpp"
#include "RE/P/PipboyRadioData.hpp"
#include "RE/P/PipboySpecialData.hpp"
#include "RE/P/PipboyStatsData.hpp"
#include "RE/P/PipboyStatusData.hpp"
#include "RE/P/PipboyThrottleManager.hpp"
#include "RE/P/PipboyWorkshopData.hpp"

namespace RE
{
	class PipboyDataGroup;

	class _declspec(novtable) PipboyDataManager : public BSTSingletonSDM<PipboyDataManager> // 0x00
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() noexcept -> PipboyDataManager*
		{
			static const auto SINGLETON = REL::Relocation<PipboyDataManager**>(ID::PipboyDataManager::Singleton);
			return *SINGLETON;
		}

		// members
		PipboyObject rootObject;					 // 0x008
		PipboyStatsData statsData;					 // 0x0A0
		PipboySpecialData specialData;				 // 0x1D8
		PipboyPerksData perksData;					 // 0x280
		PipboyInventoryData inventoryData;			 // 0x358
		PipboyQuestData questData;					 // 0x4F0
		PipboyWorkshopData workshopData;			 // 0x5D8
		PipboyLogData logData;						 // 0x718
		PipboyMapData mapData;						 // 0x7F0
		PipboyRadioData radioData;					 // 0xA28
		PipboyPlayerInfoData playerInfoData;		 // 0xAD8
		PipboyStatusData statusData;				 // 0xBE0
		std::array<PipboyDataGroup*, 11> dataGroups; // 0xCC0
		PipboyThrottleManager throttleManager;		 // 0xD18
	};

	static_assert(sizeof(PipboyDataManager) == 0xD48);
}
