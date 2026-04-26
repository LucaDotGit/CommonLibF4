#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BSNavmeshObstacleCoverDataArray;

	class __declspec(novtable) NavMeshObstacleCoverManager
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NavMeshObstacleCoverManager };
		inline static constexpr auto VTABLE{ VTABLE::NavMeshObstacleCoverManager };
		inline static constexpr auto FORM_TYPE{ FormType::kNavMeshObstacleManager };

		// members
		BSTHashMap<BSFixedString, NiPointer<BSNavmeshObstacleCoverDataArray>> obstacleCoverMap; // 20
	};
	static_assert(sizeof(NavMeshObstacleCoverManager) == 0x50);
};
